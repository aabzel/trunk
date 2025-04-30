#include "sd_card_drv.h"

#include <stdint.h>
#include <string.h>

#include "array.h"
#include "byte_utils.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "fat_fs_diag.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "sd_card_config.h"
#include "sd_card_crc.h"
#include "sd_card_crc16.h"
#include "time_mcal.h"
#include "utils_math.h"

#ifdef HAS_FAT_FS
#include "diskio.h"
#endif

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif

#ifdef HAS_SD_CARD_DIAG
#include "sd_card_diag.h"
#endif

#ifdef HAS_SPI
#ifdef HAS_SPI_DIAG
#include "spi_diag.h"
#endif
#include "spi_drv.h"
#endif

const SdCommandInfo_t SdSpiCmdLut[] = {
    {
        .cmd = CMD0,
        .ret_len = 1,
        .name = "GO_IDLE_STATE",
        .resp_type = SD_SPI_RES_R1,
    }, // GO_IDLE_STATE
    {
        .cmd = CMD8,
        .ret_len = 4,
        .name = "SEND_IF_COND",
        .resp_type = SD_SPI_RES_R7,
    }, // SEND_IF_COND
    {
        .cmd = CMD9,
        .ret_len = 19,
        .name = "SEND_CSD",
        .resp_type = SD_SPI_RES_R1,
    }, // SEND_CSD
    {
        .cmd = CMD10,
        .ret_len = 19,
        .name = "SEND_CID",
        .resp_type = SD_SPI_RES_R1,
    }, // SEND_CID
    {
        .cmd = CMD13,
        .ret_len = 64 + 4,
        .name = "SEND_STATUS",
        .resp_type = SD_SPI_RES_R2,
    }, // SEND_STATUS SD_STATUS
    {
        .cmd = CMD24,
        .ret_len = 0,
        .name = "WRITE_BLOCK",
        .resp_type = SD_SPI_RES_R1,
    },
    {
        .cmd = CMD17,
        .ret_len = 512 + 4,
        .name = "READ_SINGLE_BLOCK",
        .resp_type = SD_SPI_RES_R1,
    }, // READ_SINGLE_BLOCK
    {
        .cmd = CMD16,
        .ret_len = 1,
        .name = "SET_BLOCKLEN",
        .resp_type = SD_SPI_RES_R1,
    },
    {
        .cmd = CMD41,
        .ret_len = 1,
        .name = "SD_SEND_OP_COND",
        .resp_type = SD_SPI_RES_R1,
    }, // APP_CMD
    {
        .cmd = CMD42,
        .ret_len = 1,
        .name = "LOCK_UNLOCK",
        .resp_type = SD_SPI_RES_R1,
    }, // APP_CMD
    {
        .cmd = CMD55,
        .ret_len = 1,
        .name = "APP_CMD",
        .resp_type = SD_SPI_RES_R1,
    }, // APP_CMD
    {
        .cmd = CMD58,
        .ret_len = 4,
        .name = "READ_OCR",
        .resp_type = SD_SPI_RES_R3,
    }, // READ_OCR
    {
        .cmd = CMD59,
        .ret_len = 1,
        .name = "CRC_ON_OFF",
        .resp_type = SD_SPI_RES_R1,
    }, // page 240
};

/*TODO: Move to SPI driver*/
static bool spi_read_until_pat(uint8_t pattern, uint8_t* const resp) {
    bool res = false;
    uint8_t rx_byte = 0;
    uint32_t try_cnt = 0;

    bool loop = true;
    while(loop) {
        try_cnt++;
        if((512 * 2) < try_cnt) {
            loop = false;
            res = false;
            LOG_ERROR(SD_CARD, "LackOfAntiPattern 0x%x After %u try", pattern, try_cnt);
            break;
        } else {
            rx_byte = spi_read_byte(SdCardConfig.spi_num);
            if(pattern == rx_byte) {
                loop = true;
            } else {
                loop = false;
                break;
            }
        }
    }

    if(pattern != rx_byte) {
        (*resp) = rx_byte;
        res = true;
        SdCardInstance.read_pat_try_cnt = try_cnt;
        LOG_PARN(SD_CARD, "Read: 0x%x after %u try", rx_byte, try_cnt); /*HardFaul here*/
    } else {
        LOG_INFO(SD_CARD, "Read: only 0x%x", rx_byte);
        res = false;
    }

    return res;
}

bool chip_sel(ChipSelectSignal_t state) {
    bool res = false;
    LOG_PARN(SD_CARD, "ChipSelect state: %s Nest %d", ChipSelectSignal2Str(state), SdCardInstance.chip_enable_cnt);
    switch((uint8_t)state) {
    case SPI_CHIP_ENABLE:
        SdCardInstance.chip_enable_cnt++;
        res = gpio_set_logic_level(SdCardConfig.chip_sel.byte, GPIO_LVL_LOW);
        wait_ms(2); /*TODO figure out the minimum pause*/
        break;
    case SPI_CHIP_DISABLE:
        SdCardInstance.chip_enable_cnt--;
        res = gpio_set_logic_level(SdCardConfig.chip_sel.byte, GPIO_LVL_HI);
        // if(0 == SdCardInstance.chip_enable_cnt) {
        //    LOG_DEBUG(SD_CARD, "CS=0 Allowers");
        //} else {
        //    LOG_DEBUG(SD_CARD, "CS=1 Prohibited");
        //}
        break;
    }
    return res;
}

bool send_sd_write(uint8_t const* const buff, uint32_t size) {
    bool res = false;
    LOG_DEBUG(SD_CARD, "Write %u Byte", size);
    if(buff) {
        if(size) {
            chip_sel(SPI_CHIP_ENABLE);
            res = spi_api_write(SdCardConfig.spi_num, buff, size);
            chip_sel(SPI_CHIP_DISABLE);
        } else {
            LOG_ERROR(SD_CARD, "LenErr");
        }
    } else {
        LOG_ERROR(SD_CARD, "BuffErr");
    }
    return res;
}

bool sd_read(uint8_t* buff, uint32_t size) {
    bool res = false;
    chip_sel(SPI_CHIP_ENABLE);
    res = spi_read_safe(SdCardConfig.spi_num, buff, size);
    chip_sel(SPI_CHIP_DISABLE);
    return res;
}

bool sd_fetch_resp(uint8_t* const response) {
    bool res = false;
    if(response) {
        chip_sel(SPI_CHIP_ENABLE);
        uint8_t data = 0;
        res = spi_read_until_pat(0xFF, &data);
        chip_sel(SPI_CHIP_DISABLE);
        if(res) {
            *response = data;
            LOG_DEBUG(SD_CARD, "SpotNotFF: 0x%x", data);
        } else {
            LOG_ERROR(SD_CARD, "NoResp");
        }
    }
    return res;
}

static uint8_t sd_wait_ready(void) {
    LOG_DEBUG(SD_CARD, "WaitReady..");
    uint8_t rx_byte = 0;
    uint32_t start_ms = time_get_ms32();
    uint32_t cur_ms = start_ms;
    uint32_t diff_ms = 0;
    uint32_t zero_cnt = 0;
    uint32_t junk_data_cnt = 0;
    chip_sel(SPI_CHIP_ENABLE);
    bool loop = true;
    while(loop) {
        rx_byte = spi_read_byte(SdCardConfig.spi_num);
        if(0xFF == rx_byte) {
            LOG_DEBUG(SD_CARD, "BusSpareAfter %u ByteOfJunk, %u Zeros", junk_data_cnt, zero_cnt);
            loop = false;
            break;
        } else {
            junk_data_cnt++;
            cli_printf(".");
            if(rx_byte) {
            } else {
                zero_cnt++;
            }
        }
        cur_ms = time_get_ms32();
        diff_ms = cur_ms - start_ms;
        if(4000 < diff_ms) {
            LOG_ERROR(SD_CARD, "RdJunkData,Cnt %u,Zero %u", junk_data_cnt, zero_cnt);
            loop = false;
            break;
        }
    }

    // if(0xFF == rx_byte) {
    //   LOG_DEBUG(SD_CARD, "ready After %u ms JunkData: %u byte", diff_ms, junk_data_cnt);
    // }
    chip_sel(SPI_CHIP_DISABLE);

    return rx_byte;
}

bool is_card_connected(void) {
    bool res = false;
    res = true;

    return res;
}

#if 0
uint8_t calculate_crc(uint8_t cmd, uint32_t arg) {
    uint8_t calc_crc = 0;
    uint8_t frame[5];
    frame[0] = cmd;
    uint32_t be_arg = reverse_byte_order_uint32(arg);
    memcpy(&frame[1], &be_arg, 4);
    calc_crc = calc_crc7(&frame[0], 5);
    calc_crc = calc_crc << 1;
    calc_crc |= 0x01;
    return calc_crc;
}
#endif

bool send_sd_frame(uint8_t cmd, uint32_t arg) {
#ifdef HAS_SD_CARD_DIAG
    LOG_DEBUG(SD_CARD, "SendFrame CMD%u=0x%02x=[%s] Arg:0x%08x", cmd, cmd, Cmd2Str(cmd), arg);
#endif
    bool res = false;

    uint8_t buff[6];
    buff[0] = BIT_6 | cmd;
    uint32_t arg_be = reverse_byte_order_uint32(arg);
    memcpy(&buff[1], &arg_be, 4);
    uint8_t crc7 = calc_crc7(buff, 5);
    buff[5] = BIT_0 | (crc7 << 1);

    LOG_DEBUG(SD_CARD, "CRC7 0x%x", crc7);
    res = send_sd_write(buff, 6);
    return res;
}

bool SD_sendCommand(uint8_t cmd, uint32_t arg) {
#ifdef HAS_SD_CARD_DIAG
    LOG_DEBUG(SD_CARD, "Send CMD%u=0x%02x=[%s] Arg: 0x%08x", cmd, cmd, Cmd2Str(cmd), arg);
#endif
    bool res = false;
    uint8_t last_rx_byte = 0xFF;
    last_rx_byte = sd_wait_ready();
    if(0xFF == last_rx_byte) {
        // res = spi_write_byte(SdCardConfig.spi_num, DUMMY_BYTE);
        res = send_sd_frame(cmd, arg);
        if(res) {
            LOG_DEBUG(SD_CARD, "SendFrameOk");
        } else {
            LOG_ERROR(SD_CARD, "SendFrameErr");
        }
        // res= spi_write_byte(SdCardConfig.spi_num, DUMMY_BYTE);
    } else {
        LOG_ERROR(SD_CARD, "CardSendsFlude");
        res = false;
    }

    return res;
}

bool sd_send_r7_cmd(uint8_t cmd, uint32_t arg, R7_t* pR7, uint8_t exp_resp) {
    bool res = false;
    LOG_DEBUG(SD_CARD, "SendR7 CMD%u Arg:0x%x", cmd, arg);
    res = SD_sendCommand(cmd, arg);
    if(res) {
        res = sd_fetch_resp(&(pR7->R1.byte));
        if(res) {
#ifdef HAS_SD_CARD_DIAG
            sd_parse_r1(pR7->R1.byte);
#endif
            if(exp_resp == pR7->R1.byte) {
                res = sd_read(pR7->buff, 4);
                if(res) {
                    res = reverse_byte_order_array(pR7->buff, 4);
#ifdef HAS_SD_CARD_DIAG
                    sd_parse_r7(pR7);
#endif
                } else {
                    res = false;
                }
            } else {
                res = false;
                LOG_ERROR(SD_CARD, "WronfRespErr R1:0x%x Exp:0x%x", pR7->R1.byte, exp_resp);
            }
        } else {
            res = false;
            LOG_ERROR(SD_CARD, "FetchR1Err");
        }
    } else {
        res = false;
        LOG_ERROR(SD_CARD, "Send R7");
    }
    return res;
}

bool sent_74_ones(void) {
    LOG_INFO(SD_CARD, "Send74Ticks");
    chip_sel(SPI_CHIP_DISABLE);
    bool res = true;
    uint8_t tx_ff[10];
    memset(tx_ff, 0xFF, sizeof(tx_ff));
    res = spi_api_write(SdCardConfig.spi_num, tx_ff, sizeof(tx_ff));
    if(res) {
        LOG_INFO(SD_CARD, "Send74TicksOk");
    } else {
        LOG_ERROR(SD_CARD, "Send74TicksErr");
    }
    return res;
}

#define GO_TO_IDLE_TRY_CNT 3
bool sd_card_power_on(void) {
    LOG_INFO(SD_CARD, "PowerOn");
    bool res = true;

    wait_ms(50);
    sent_74_ones();

    R1_t R1;
    R1.byte = SD_R1_ERROR_BYTE;
    uint32_t i = 0;
    uint32_t busy_cnt = 0;
    for(i = 0; i < GO_TO_IDLE_TRY_CNT; i++) {
        cli_printf(CRLF);
        R1.byte = sd_send_r1_cmd(CMD0, 0);
#ifdef HAS_SD_CARD_DIAG
        sd_parse_r1(R1.byte);
#endif
        if(SD_SPI_R1_IN_IDLE_STATE == R1.byte) {
            break;
        }

        if((0 == R1.msb_zero)) {
            if(0 == R1.idle) {
                busy_cnt++;
                wait_ms(100);
            }
        }
    }

    if(GO_TO_IDLE_TRY_CNT == busy_cnt) {
        res = false;
        LOG_ERROR(SD_CARD, "CardBusyAfter %u try", busy_cnt);
    }

    if(SD_SPI_R1_IN_IDLE_STATE == R1.byte) {
        LOG_INFO(SD_CARD, "SpotCard");
        res = true;
    } else {
        res = false;
        LOG_ERROR(SD_CARD, "UnknownCard");
    }

    // if(R1.idle) {
    //    res = true;
    //    LOG_INFO(SD_CARD, "CMD0 fine resp! After %u try", retry);
    //}

    // uint8_t buff_ff[2] = {0xff, 0xff};
    // send_sd_write(buff_ff, 2);
    if(res) {
        LOG_INFO(SD_CARD, "PowerOnDone!");
    } else {
        LOG_ERROR(SD_CARD, "PowerErr!");
    }
    return res;
}

bool sd_is_normal_r1(uint8_t r1) {
    bool res = false;
    R1_t R1;
    R1.byte = r1;
    if(0 == R1.msb_zero) {
        res = true;
        if(R1.com_crc_err) {
            res = false;
        }
        if(R1.param_err) {
            res = false;
        }
        if(R1.illegal_cmd) {
            res = false;
        }
        if(R1.com_crc_err) {
            res = false;
        }
        if(R1.errase_sec_err) {
            res = false;
        }
        if(R1.addr_err) {
            res = false;
        }
    }
    return res;
}

#define CMD8_CHECK_PATTERN 0x55
static bool sd_set_voltage(void) {
    bool res = false;
    LOG_WARNING(SD_CARD, CRLF CRLF "AdjustVoltage");

    Cmd8Arg_t Cmd8arg;
    Cmd8arg.check_pattern = CMD8_CHECK_PATTERN;
    Cmd8arg.supply_voltage = VOLT_ACCEP_2_7_3_6;
    Cmd8arg.reserved = 0;

    R7_t R7;
    res = sd_send_r7_cmd(CMD8, Cmd8arg.arg, &R7, SD_SPI_R1_IN_IDLE_STATE);
    if(res) {
        if(VOLT_ACCEP_2_7_3_6 == R7.voltage_accepted) {
            if(CMD8_CHECK_PATTERN == R7.echo_back) {
                res = true;
                LOG_INFO(SD_CARD, "PatternMatch!");
            } else {
                res = false;
                LOG_ERROR(SD_CARD, "PatternErr Unknown Card");
            }
        } else {
            res = false;
            LOG_ERROR(SD_CARD, "CMD8Resp Volt:%u Err", R7.voltage_accepted);
        }
    }
    if(res) {
        LOG_WARNING(SD_CARD, CRLF CRLF "AdjustVoltageDone!");
    } else {
        LOG_ERROR(SD_CARD, CRLF CRLF "AdjustVoltageError!");
    }
    return res;
}

uint8_t sd_send_r1_cmd(uint8_t cmd, uint32_t arg) {
    bool res = false;
    LOG_DEBUG(SD_CARD, "Send R1 CMD%u Arg:0x%08x", cmd, arg);
    R1_t R1;
    R1.byte = SD_R1_ERROR_BYTE;
    res = SD_sendCommand(cmd, arg);
    if(res) {
        res = sd_fetch_resp(&R1.byte);
        if(res) {
#ifdef HAS_SD_CARD_DIAG
            res = sd_parse_r1(R1.byte);
#endif
        } else {
            LOG_ERROR(SD_CARD, "FetchR1Err");
        }
    } else {
        LOG_ERROR(SD_CARD, "Send CMD%u Arg:0x%x Err", cmd, arg);
    }
    // sd_wait_ready(); //error
    return R1.byte;
}

/*see page 240*/
static bool send_app_spec_cmd_switch(uint8_t exp_resp) {
    bool res = false;
    LOG_INFO(SD_CARD, CRLF CRLF "TryToSwToAppSpecificCmd");
    R1_t R1;
    R1.byte = sd_send_r1_cmd(CMD55, 0);
#ifdef HAS_SD_CARD_DIAG
    sd_parse_r1(R1.byte);
#endif
    if(exp_resp == R1.byte) {
        LOG_INFO(SD_CARD, "AppSpecificSwitchOk");
        res = true;
    } else {
        res = false;
        LOG_ERROR(SD_CARD, "R1Err 0%x", R1.byte);
    }

    return res;
}

bool sd_send_r3_cmd(uint8_t cmd, uint32_t arg, R3_t* R3) {
    bool res = false;
    memset(R3->byte, 0, sizeof(R3_t));
    LOG_DEBUG(SD_CARD, "SendR3 CMD%u Arg:0x%x", cmd, arg);
    res = SD_sendCommand(cmd, arg);
    if(res) {
        res = sd_fetch_resp(&R3->R1.byte);
        if(res) {
#ifdef HAS_SD_CARD_DIAG
            res = sd_parse_r1(R3->R1.byte);
#endif
            res = sd_read(R3->byte, sizeof(OCR_t));
            if(res) {
                // res = sd_parse_ocr(&(R3->ocr));
            }
        }
    } else {
        LOG_ERROR(SD_CARD, "R3Err");
    }
    return res;
}

bool sd_send_r2_cmd(uint8_t cmd, uint32_t arg, R2_t* R2) {
    bool res = false;
    LOG_DEBUG(SD_CARD, "SendR2 CMD%u Arg:0x%x", cmd, arg);
    R2->word = 0;
    res = SD_sendCommand(cmd, arg);
    if(res) {
        res = sd_fetch_resp(&R2->R1.byte);
        if(res) {
#ifdef HAS_SD_CARD_DIAG
            res = sd_parse_r1(R2->R1.byte);
#endif
            res = sd_read(R2->byte, 1);
            if(res) {
#ifdef HAS_SD_CARD_DIAG
                res = sd_parse_r2(R2->word);
#endif
            }
        }
    } else {
        LOG_ERROR(SD_CARD, "R2Err");
    }
    return res;
}

/*See page 228 229*/
static SdErrCode_t sd_init_cmd(void) {

    uint8_t ret = SD_ERR_CODE_UNDEF;
    LOG_WARNING(SD_CARD, "CardInitStart");
    R1_t R1;
    R1.byte = 0;
    ACmd41Arg_t ACmd41Arg;
    ACmd41Arg.arg = 0;
    ACmd41Arg.hcs = HCS_SDHC_SDXC_YES;

    R1.byte = sd_send_r1_cmd(ACMD41, ACmd41Arg.arg);
#ifdef HAS_SD_CARD_DIAG
    sd_parse_r1(R1.byte);
#endif
    if(0x00 == R1.byte) {
        ret = SD_ERR_CODE_OK;
        LOG_INFO(SD_CARD, "CardReady");
    } else if(SD_SPI_R1_IN_IDLE_STATE == R1.byte) {
        ret = SD_ERR_CODE_IDLE;
        LOG_WARNING(SD_CARD, "CardInIdleTry Try ACMD41 again");
    } else {
        ret = SD_ERR_CODE_17;
        LOG_ERROR(SD_CARD, "ACMD41RespErr R1 0x%x Exp 0x00", R1.byte);
    }

    return ret;
}

bool sd_disk_initialize(void) {
    LOG_INFO(SD_CARD, "%s()", __FUNCTION__);
    bool res = false;

    res = sd_card_power_on();
    if(res) {
        LOG_INFO(SD_CARD, "PowerOnOk");
    } else {
        LOG_ERROR(SD_CARD, "PowerOnErr");
        res = false;
    }

    if(res) {
        res = sd_set_voltage();
    } else {
        LOG_ERROR(SD_CARD, "SetVoltageErr");
    }

    if(res) {
        LOG_INFO(SD_CARD, "SetVoltageOk");
        uint32_t i = 0;
        for(i = 1; i <= 7; i++) {
            res = send_app_spec_cmd_switch(0x01);
            if(res) {
                LOG_INFO(SD_CARD, "NoneStdCmd try N:%u", i);
                SdErrCode_t ret = sd_init_cmd();
                if(SD_ERR_CODE_OK == ret) {
                    LOG_INFO(SD_CARD, "InitOk After N:%u try!", i);
                    break;
                } else {
                    LOG_ERROR(SD_CARD, "UnableToSwToAppSpecCmd  %u try", i);
                    res = false;
                }
            }
        } // for ( i = 1

        if(false == res) {
            LOG_ERROR(SD_CARD, "InitTimeOut After %u try", 7);
        }
    }

    SdSpiAddressMethod_t addr_type = SD_SPI_ADDR_UNDEF;
    if(res) {
        res = sd_card_read_ocr(&SdCardInstance.OCR);
        if(res) {
            LOG_INFO(SD_CARD, "ReadOCROk");
            if(1 == SdCardInstance.OCR.card_capacity_status) {
                LOG_INFO(SD_CARD, "SD Ver2 (Block Address)");
                addr_type = SD_SPI_ADDR_BLOCK;
            } else {
                LOG_INFO(SD_CARD, "SD Ver2 (Byte Address)");
                addr_type = SD_SPI_ADDR_BYTE;
            }
        } else {
            LOG_ERROR(SD_CARD, "ReadOCRErr");
        }
    }

    switch(addr_type) {
    case SD_SPI_ADDR_BYTE: {
        /*UNLOCK_CARD CMD42 LOCK_UNLOCK*/
#if 0
            bool res_lock = sd_card_toggle_lock();
            if(res_lock){
                LOG_INFO(SD_CARD, "ToggleLockOk");
            }else{
                LOG_WARNING(SD_CARD, "ToggleLockErr");
            }
#endif
        res = sd_card_block_len_set(SdCardConfig.block_len);
        if(res) {
            LOG_INFO(SD_CARD, "SetBlockLen %u Ok", SdCardConfig.block_len);
        } else {
            LOG_WARNING(SD_CARD, "SetBlockLen %u Err", SdCardConfig.block_len);
        }

    } break;
    case SD_SPI_ADDR_BLOCK: {
        res = true;
    } break;
    default:
        res = false;
        break;
    }

    if(res) {
    }

    return res;
}

bool sd_rx_data_array(uint8_t* out_buff, uint32_t len) {
    uint8_t rx_byte = 0;
    bool res = false;
    uint16_t i = 0;
    LOG_DEBUG(SD_CARD, "ReadData %u", len);
    bool loop = true;
    chip_sel(SPI_CHIP_ENABLE);
    uint32_t start_ms = time_get_ms32();
    uint32_t up_time_ms = start_ms;
    uint32_t diff_ms = start_ms;
    while(loop) {
        i++;
        rx_byte = spi_read_byte(SdCardConfig.spi_num);
        LOG_DEBUG(SD_CARD, "ReadByte Rx[%u]=0x%x", i, rx_byte);
        switch(rx_byte) {
        case TOKEN_START_BLOCK: // 0xFE
            loop = false;
            LOG_DEBUG(SD_CARD, "SpotStartBlockToken 0x%x After %u try", rx_byte, i);
            res = true;
            break;
        case 0:
        case 0xFF:
            break;
        default:
            // loop = false;
            break;
        }
        up_time_ms = time_get_ms32();
        diff_ms = up_time_ms - start_ms;
        if(2000 < diff_ms) {
            LOG_ERROR(SD_CARD, "NoStartBlockToken!");
            chip_sel(SPI_CHIP_DISABLE);
            loop = false;
            res = false;
        }
    }

    if(res) {
        res = spi_read_safe(SdCardConfig.spi_num, out_buff, len);
        /* 2bytes dummy CRC */
        res = spi_read_safe(SdCardConfig.spi_num, (uint8_t*)&SdCardInstance.read_crc16, 2);
        if(res) {
            SdCardInstance.read_crc16 = reverse_byte_order_uint16(SdCardInstance.read_crc16);
            LOG_DEBUG(SD_CARD, "CRC16Read 0x%04x", SdCardInstance.read_crc16);
            uint16_t crc16_calc = calc_crc16(out_buff, len);

            LOG_DEBUG(SD_CARD, "CRC16Calc 0x%04x", crc16_calc);
            if(crc16_calc != SdCardInstance.read_crc16) {
                LOG_ERROR(SD_CARD, "CRC16Err");
                res = false;
            }
        } else {
            LOG_ERROR(SD_CARD, "ReadCRC16Err");
        }
    }
    chip_sel(SPI_CHIP_DISABLE);
    return res;
}

/*512 byte each*/
bool sd_read_sector(uint32_t block_num, uint8_t* const out_buff) {
    bool res = false;
    if(out_buff) {
        log_level_t ll = log_level_get(SD_CARD);
        if(LOG_LEVEL_DEBUG == ll) {
            cli_printf(CRLF);
            LOG_DEBUG(SD_CARD, "ReadBlock %u", block_num);
        }
        R1_t R1;
        R1.byte = sd_send_r1_cmd(CMD17, block_num * BLOCK_SIZE_BYTE);
        if(TOKEN_BUSY == R1.byte) {
            res = true;
        } else {
            LOG_ERROR(SD_CARD, "ReadBlockErr, R1 0x%x", R1.byte);
#ifdef HAS_SD_CARD_DIAG
            sd_parse_r1(R1.byte);
#endif
            res = false;
        }

        if(res) {
            res = sd_rx_data_array(out_buff, BLOCK_SIZE_BYTE);
        }
    }

    return res;
}

bool sd_read_multiple_sector(uint32_t block_num, uint8_t* out_buff, uint32_t sectors) {
    uint16_t i = 0;
    uint32_t res_sectors = 0;
    uint8_t ret = 0;
    bool res = false;

    res = SD_sendCommand(CMD18, block_num);
    if(0x00 != ret) {
        LOG_ERROR(SD_CARD, "CMD18 read error");
        return false;
    }

    for(i = 0; i < sectors; i++) {
        res = sd_rx_data_array(out_buff, 512);
        if(true == res) {
            out_buff += 512;
            res_sectors++;
        } else {
            break;
        }
    }
    res = SD_sendCommand(CMD12, 0);

    chip_sel(SPI_CHIP_DISABLE);
    ret = spi_read_byte(SdCardConfig.spi_num);
    ret = spi_read_byte(SdCardConfig.spi_num);
    if(res_sectors == sectors) {
        res = true;
    }
    return res;
}
static bool sd_data_resp_token_parse_status(DataRespTokenStatus_t val) {
    bool res = false;
    switch((uint8_t)val) {
    case DAT_RESP_TOKEN_DATA_ACCEPTED:
        LOG_DEBUG(SD_CARD, "data accepted");
        res = true;
        break;
    case DAT_RESP_TOKEN_DATA_REJECTED_DUE_TO_CRC:
        LOG_ERROR(SD_CARD, "data discarded CRC error");
        res = false;
        break;
    case DAT_RESP_TOKEN_DATA_REJECTED_DUE_TO_WR_ERR:
        LOG_ERROR(SD_CARD, "data discarded write error");
        res = false;
        break;
    }
    return res;
}

static bool parse_data_response(uint8_t value) {
    bool res = false;
    DataResponseToken_t Token;
    Token.byte = value;
    if(1 == Token.one) {
        if(0 == Token.zero) {
            res = sd_data_resp_token_parse_status(Token.status);
        } else {
            LOG_ERROR(SD_CARD, "FormatZeroErr");
        }
    } else {
        LOG_ERROR(SD_CARD, "FormatOneErr");
    }

    return res;
}

static bool sd_tx_data_block(const uint8_t* const in_buff, uint8_t token) {
    bool res = false;

    uint8_t rx_byte = 0;

    rx_byte = sd_wait_ready();
    if(0xFF == rx_byte) {
        LOG_DEBUG(SD_CARD, "SpiBusIdle");

        chip_sel(SPI_CHIP_ENABLE);
        spi_write_byte(SdCardConfig.spi_num, token);

        if(TOKEN_STOP != token) {

            res = spi_api_write(SdCardConfig.spi_num, in_buff, BLOCK_SIZE_BYTE);

            /* 2Bytes dummy CRC */
            spi_write_byte(SdCardConfig.spi_num, 0xff); // CRC
            spi_write_byte(SdCardConfig.spi_num, 0xff); // CRC

            /*data-response token*/
            uint8_t data_response_token = 0;
            data_response_token = spi_read_byte(SdCardConfig.spi_num);
            res = parse_data_response(data_response_token);
            if(res) {
                // wait end of write block.  recv buffer clear
                uint32_t start_ms = time_get_ms32();
                uint32_t cur_ms = start_ms;
                uint32_t diff_ms = 0;
                do {
                    rx_byte = spi_read_byte(SdCardConfig.spi_num);
                    if(TOKEN_BUSY == rx_byte) {
                        LOG_DEBUG(SD_CARD, "BusyInTx");
                    }
                    cur_ms = time_get_ms32();
                    diff_ms = cur_ms - start_ms;
                    /*busy token*/
                    if(4000 < diff_ms) {
                        LOG_ERROR(SD_CARD, "EndOfWriteTimeOut");
                        res = false;
                        break;
                    }
                } while(0xFF != rx_byte);

                if(0xFF == rx_byte) {
                    LOG_DEBUG(SD_CARD, "EndOfBusyStateWriteBlock");
                }
            }
        }

        chip_sel(SPI_CHIP_DISABLE);
    }
    return true;
}

uint16_t get_status_reg(void) {
    R2_t R2;
    R2.word = 0;
    bool res = sd_send_r2_cmd(CMD13, 0, &R2);
    if(res) {
        LOG_DEBUG(SD_CARD, "GetStatusOk");
    } else {
        LOG_ERROR(SD_CARD, "GetStatusErr");
    }
    return R2.word;
}

const SdCommandInfo_t* SdCmdGetNode(uint8_t cmd) {
    const SdCommandInfo_t* Node = NULL;
    uint16_t cmd_cnt = ARRAY_SIZE(SdSpiCmdLut);
    for(uint16_t i = 0; i < cmd_cnt; i++) {
        if(cmd == SdSpiCmdLut[i].cmd) {
            Node = &SdSpiCmdLut[i];
            break;
        }
    }
    return Node;
}

bool sd_card_read_ocr(OCR_t* pOCR) {
    bool res = false;
    if(pOCR) {
        R3_t R3;
        res = sd_send_r3_cmd(CMD58, 0, &R3);
        if(res) {
            memcpy(pOCR->byte, R3.ocr.byte, sizeof(OCR_t));
        }
    }
    return res;
}

bool sd_card_read_csd(CSD_t* const pCSD) {
    bool res = false;
    LOG_INFO(SD_CARD, "ReadCSD..");
    R1_t R1;
    R1.byte = sd_send_r1_cmd(CMD9, 0);
    if(0 == R1.byte) {
        wait_ms(50);
        res = sd_rx_data_array(pCSD->byte, sizeof(CSD_t));
        if(res) {
            res = reverse_byte_order_array(pCSD->byte, sizeof(CSD_t));
            LOG_INFO(SD_CARD, "ReadCSDok");
            // print_hex(pCSD->byte, sizeof(CSD_t));
            // res = sd_parse_csd(pCSD);
        } else {
            LOG_ERROR(SD_CARD, "ReadCSDerr");
        }
    } else {
        LOG_ERROR(SD_CARD, "R1respErr 0x%02x", R1.byte);
    }
    return res;
}

bool sd_card_read_cid(CID_t* pCID) {
    bool res = false;
    LOG_INFO(SD_CARD, "ReadCID..");
    if(pCID) {
        R1_t R1;
        R1.byte = sd_send_r1_cmd(CMD10, 0);
        if(0x00 == R1.byte) {
            res = sd_rx_data_array(pCID->byte, sizeof(CID_t));
            if(res) {
                res = reverse_byte_order_array(pCID->byte, sizeof(CID_t));
                LOG_INFO(SD_CARD, "ReadCIDok");
            } else {
                LOG_ERROR(SD_CARD, "ReadCIDerr");
            }
        } else {
            LOG_ERROR(SD_CARD, "R1respErr 0x%02x", R1.byte);
        }
    }
    return res;
}

bool sd_card_ssr_get(void) {
    bool res = send_app_spec_cmd_switch(0x00);
    if(res) {
        R2_t R2;
        res = sd_send_r2_cmd(CMD13, 0, &R2);
        if(res) {
            res = sd_rx_data_array(SdCardInstance.SSR.byte, sizeof(SSR_t));
            if(res) {
                print_hex(SdCardInstance.SSR.byte, sizeof(SSR_t));
            }
        }
    } else {
        LOG_ERROR(SD_CARD, "GoSpetialErr");
    }
    return res;
}

bool sd_read_registers(void) {
    bool res = false;
    res = sd_card_ssr_get();

    R2_t R2;
    R2.word = 0;
    res = sd_send_r2_cmd(CMD13, 0, &R2);
    if(res) {
        SdCardInstance.locked = R2.card_is_locked;
        LOG_INFO(SD_CARD, "StatusRegister: 0x%04x", R2.word);
    }

    res = sd_card_read_csd(&SdCardInstance.CSD);
    res = sd_card_read_ocr(&SdCardInstance.OCR);
    res = sd_card_read_cid(&SdCardInstance.CID);

#if 0
    sd_status = get_status_reg();
    bool res = false;
    uint8_t real_arr[260];
    memset(real_arr, 0xFF, sizeof(real_arr));
    const SdCommand_t* item = NULL;

    res = SD_sendCommand(CMD58, 0);
    if(0 == ret) {
        res = true;
        LOG_INFO(SD_CARD, "Read OCR R1 %02x", ret);
        item = get_reg_inst(CMD58);
        if(item) {
            spi_read_safe(SdCardConfig.spi_num, real_arr, item->resp_len_byte);
            print_hex_buf(real_arr, item->resp_len_byte);
        }
    }
    memset(real_arr, 0xFF, sizeof(real_arr));
    res = SD_sendCommand(CMD9, 0);
    if(0 == ret) {
        res = true;
        LOG_INFO(SD_CARD, "Read CSD R1 %02x ", ret);
        item = get_reg_inst(CMD9);
        if(item) {
            sd_rx_data_array(real_arr, item->resp_len_byte);
            print_hex_buf(real_arr, item->resp_len_byte);
        }
    }
    memset(real_arr, 0xFF, sizeof(real_arr));
    res = SD_sendCommand(CMD10, 0);
    if(0 == ret) {
        res = true;
        item = get_reg_inst(CMD10);
        if(item) {
            LOG_INFO(SD_CARD, "Read CID R1 %02x ", ret);
            sd_rx_data_array(real_arr, item->resp_len_byte);
            print_hex_buf(real_arr, item->resp_len_byte);
        }
    }
    memset(real_arr, 0xFF, sizeof(real_arr));
    // sdc 0x77 0
    res = SD_sendCommand(CMD55, 0);
    if(0 == ret) {
        memset(real_arr, 0xFF, sizeof(real_arr));
        res = SD_sendCommand(CMD13, 0);
        if(0 == ret) {
            item = get_reg_inst(CMD13);
            if(item) {
                LOG_INFO(SD_CARD, "Read SD Status R2 %02x ", ret);
                sd_rx_data_array(real_arr, item->resp_len_byte);
                print_hex_buf(real_arr, item->resp_len_byte);
            }
        }
    }
#endif

    return res;
}

uint8_t calc_cmd_num(uint8_t cmd) { return (cmd & (~((uint8_t)(1 << 6)))); }

bool sd_control(void) { return false; }

/* power off */
static void SD_PowerOff(void) { SdCardInstance.power_flag = 0; }

/* check power flag */
static uint8_t SD_CheckPower(void) { return SdCardInstance.power_flag; }

uint8_t sd_card_status(void) {
    /* return disk status */
    return 1;
}

/* read sector */
DRESULT SD_disk_read(uint8_t pdrv, uint8_t* buff, uint32_t sector, uint32_t count) {
    DRESULT ret = RES_ERROR;
    /* pdrv should be 0 */
    if(pdrv || !count)
        return RES_PARERR;

    chip_sel(SPI_CHIP_ENABLE);
    bool res = false;
    if(1 == count) {
        /* READ_SINGLE_BLOCK */
        res = sd_read_sector(sector, buff);
        if(true == res) {
            count = 0;
            ret = RES_OK;
        }
    } else {
        LOG_ERROR(SD_CARD, "Not supported read multiple blocks");
        res = sd_read_multiple_sector(sector, buff, count);
        if(res) {
            ret = RES_OK;
        }
    }

    /* Idle */
    chip_sel(SPI_CHIP_DISABLE);
    // spi_read_byte(SdCardConfig.spi_num);

    return ret;
}

/* write sector */
#if 0
DRESULT SD_disk_write(uint8_t pdrv, const uint8_t* buff, uint32_t sector, uint32_t count) {
    bool res = false;
    DRESULT ret = RES_ERROR;
    /* pdrv should be 0 */
    if(pdrv || !count)
        return RES_PARERR;



    chip_sel(SPI_CHIP_ENABLE);
    if(1 == count) {
        res = sd_write_sector(sector, buff);
        if(true == res) {
            ret = RES_OK;
        }
    } else {
        /* WRITE_MULTIPLE_BLOCK */
        if(card_type & CT_SD1) {
            res = SD_sendCommand(CMD55, 0);
            res = SD_sendCommand(CMD23, count); /* ACMD23 */
        }
        res = SD_sendCommand(CMD25, sector);
        if(ret == 0) {
            do {
                if(false == sd_tx_data_block(buff, TOKEN_MULT_BLK_WR)) {
                    break;
                }
                buff += 512;
            } while(--count);

            /* STOP_TRAN token */
            if(false == sd_tx_data_block(0, TOKEN_STOP)) {
                count = 1;
            }
        }
        if(0 == count) {
            ret = RES_OK;
        }
    }

    /* Idle */
    chip_sel(SPI_CHIP_DISABLE);

    ret = spi_read_byte(SdCardConfig.spi_num);

    return ret;
}
#endif /* _USE_WRITE */

uint32_t sd_sector_count_csd_v1_calc(CSD_t* pCSD) {
    uint32_t sector_count = 0;
    SdCardInstance.mult = ipow(2, pCSD->V1.c_size_mult + 2);
    sector_count = (pCSD->V1.c_size + 1) * SdCardInstance.mult;
    return sector_count;
}

uint32_t sd_sector_count_csd_v2_calc(CSD_t* pCSD) {
    uint32_t sector_count = 0;
    sector_count = (pCSD->V2.c_size + 1);
    return sector_count;
}

static uint32_t sd_card_sector_count_get(CSD_t* const pCSD) {
    uint32_t sector_count = 0;
    if(pCSD) {
        if(pCSD->V1.csd_structure == pCSD->V2.csd_structure) {
            switch(pCSD->V1.csd_structure) {
            case CSD_VERSION_1_0:
                sector_count = sd_sector_count_csd_v1_calc(pCSD);
                break;
            case CSD_VERSION_2_0:
                sector_count = sd_sector_count_csd_v2_calc(pCSD);
                break;
            default:
                LOG_ERROR(SD_CARD, "UndefStructure %u", pCSD->V1.csd_structure);
                break;
            }
        } else {
            LOG_ERROR(SD_CARD, "StructureErr");
        }
    }
    LOG_DEBUG(SD_CARD, "sector_count %u", sector_count);
    return sector_count;
}

uint32_t sd_sector_size_csd_v1_calc(CSD_t* pCSD) {
    uint32_t sector_size = 0;
    sector_size = ipow(2, pCSD->V1.c_size_mult);
    return sector_size;
}

uint32_t sd_sector_size_csd_v2_calc(CSD_t* pCSD) {
    uint32_t sector_size = 0;
    sector_size = 512;
    return sector_size;
}

uint32_t sd_card_sector_size_get(CSD_t* pCSD) {
    uint32_t sector_size = 0;
    if(pCSD) {
        if(pCSD->V1.csd_structure == pCSD->V2.csd_structure) {
            switch(pCSD->V1.csd_structure) {
            case CSD_VERSION_1_0:
                sector_size = sd_sector_size_csd_v1_calc(pCSD);
                break;
            case CSD_VERSION_2_0:
                sector_size = sd_sector_size_csd_v2_calc(pCSD);
                break;
            }
        }
    }
    LOG_DEBUG(SD_CARD, "SectorSize %u", sector_size);
    return sector_size;
}

DRESULT sd_card_ctrl_power(uint8_t command, uint8_t* const status) {
    DRESULT ret = RES_ERROR;
    bool res = false;
    switch(command) {
    case 0:
        SD_PowerOff(); /* Power Off */
        ret = RES_OK;
        break;
    case 1:
        res = sd_card_power_on(); /* Power On */
        if(res) {
            ret = RES_OK;
        }
        break;
    case 2:
        *status = SD_CheckPower();
        ret = RES_OK; /* Power Check */
        break;
    default:
        ret = RES_PARERR;
    }
    return ret;
}

DRESULT sd_disk_ioctl(uint8_t drv, uint8_t ctrl, uint8_t* const buff) {
    LOG_PARN(SD_CARD, "IoCtl Drv:%u Ctrl:%u=%s", drv, ctrl, DiskIoCtlCmd2Str(ctrl));
    DRESULT ret = RES_ERROR;
    bool res = false;
    ret = RES_ERROR;
    chip_sel(SPI_CHIP_ENABLE);

    switch(ctrl) {
    case CTRL_SYNC: {
        uint8_t rx_byte = 0;
        rx_byte = sd_wait_ready();
        if(0xFF == rx_byte) {
            LOG_DEBUG(SD_CARD, "SyncOk");
            ret = RES_OK;
        } else {
            LOG_ERROR(SD_CARD, "SyncErrRead%x", rx_byte);
            ret = RES_ERROR;
        }
    } break;

    case CTRL_POWER:
        res = sd_card_ctrl_power(buff[0], &buff[1]);
        break;

    case GET_SECTOR_COUNT:
        res = sd_card_read_csd(&SdCardInstance.CSD);
        if(res) {
            uint32_t sector_count = sd_card_sector_count_get(&SdCardInstance.CSD);
            memcpy(buff, &sector_count, 4);
            ret = RES_OK;
        } else {
            LOG_ERROR(SD_CARD, "GetSectorCntError");
        }
        break;

    case GET_SECTOR_SIZE:
        res = sd_card_read_csd(&SdCardInstance.CSD);
        if(res) {
            uint32_t sector_size32b = sd_card_sector_size_get(&SdCardInstance.CSD);
            uint16_t sector_size16b = sector_size32b;
            memcpy(buff, &sector_size16b, 2);
            ret = RES_OK;
        }
        break;

    case GET_BLOCK_SIZE: {
        uint32_t block_size = 512;
        memcpy(buff, &block_size, 4);
        //*((uint16_t*)buff) = 512;
        ret = RES_OK;
    } break;
    case MMC_GET_CSD:
        res = sd_card_read_csd(&SdCardInstance.CSD);
        if(res) {
            memcpy(buff, SdCardInstance.CSD.byte, sizeof(CSD_t));
            ret = RES_OK;
        }

        break;
    case MMC_GET_CID:
        res = sd_card_read_cid(&SdCardInstance.CID);
        if(res) {
            memcpy(buff, SdCardInstance.CID.byte, sizeof(CID_t));
            ret = RES_OK;
        }
        break;
    case CTRL_FORMAT:
        ret = RES_ERROR;
        break;
    case CTRL_LOCK:
        ret = RES_ERROR;
        break;
    case CTRL_EJECT:
        ret = RES_ERROR;
        break;
    case ATA_GET_SN:
        ret = RES_ERROR;
        break;
    case CTRL_TRIM:
        ret = RES_ERROR;
        break;
    case MMC_GET_SDSTAT:
        ret = RES_ERROR;
        break;
    case ATA_GET_MODEL:
        ret = RES_ERROR;
        break;
    case ATA_GET_REV:
        ret = RES_ERROR;
        break;
    case MMC_GET_TYPE:
        ret = RES_ERROR;
        break;

    case MMC_GET_OCR:
        res = sd_card_read_ocr(&SdCardInstance.OCR);
        if(res) {
            memcpy(buff, SdCardInstance.OCR.byte, sizeof(OCR_t));
            ret = RES_OK;
        }

        break;
    default:
        LOG_ERROR(SD_CARD, "UndefIoCtrlCmd %u", ctrl);
        ret = RES_PARERR;
        break;
    }
    chip_sel(SPI_CHIP_DISABLE);

    spi_read_byte(SdCardConfig.spi_num);

    return ret;
}

/*See page 239*/
bool sd_card_toggle_lock(void) {
    bool res = false;
    LOG_INFO(SD_CARD, "LockUnLock");
    uint8_t r1 = sd_send_r1_cmd(CMD42, 0);
    (void)r1;
#ifdef HAS_SD_CARD_DIAG
    res = sd_parse_r1(r1);
#endif
    return res;
}

/*See 7.2.4 Data Write*/
bool sd_write_sector(uint32_t block_num, uint8_t const* const in_buff) {
    bool res = false;
    LOG_DEBUG(SD_CARD, "WriteSingleBlock %u", block_num);
    if(in_buff) {
        R1_t R1;
        R1.byte = sd_send_r1_cmd(CMD24, block_num * BLOCK_SIZE_BYTE);
#ifdef HAS_SD_CARD_DIAG
        sd_parse_r1(R1.byte);
#endif
        if(0 == R1.byte) {
            res = true;
        } else {
            LOG_ERROR(SD_CARD, "Set WRIRE_BLOCK RespErr 0x%x", R1.byte);
        }

        if(res) {
            res = sd_tx_data_block(in_buff, TOKEN_START_BLOCK);
        }
    }

    return res;
}

/*see page 238*/
bool sd_card_block_len_set(uint32_t block_len) {
    bool res = false;
    LOG_WARNING(SD_CARD, "SetBlockLen %u byte", block_len);
    if(0 < block_len) {
        R1_t R1;
        R1.byte = sd_send_r1_cmd(CMD16, block_len);
#ifdef HAS_SD_CARD_DIAG
        sd_parse_r1(R1.byte);
#endif
        if(0x00 == R1.byte) {
            res = true;
        } else {
            res = false;
            LOG_ERROR(SD_CARD, "SetBlockLen %u Err", block_len);
        }
    } else {
        LOG_ERROR(SD_CARD, "BlockLenErr %u byte", block_len);
    }

    return res;
}

bool sd_card_spi_gpio_init(void) {
    bool res = false;
    LOG_WARNING(SD_CARD, "InitGpioPullUps");
    const SpiConfig_t* SpiConfig = SpiGetConfig(SdCardConfig.spi_num);
    if(SpiConfig) {
        LOG_INFO(SD_CARD, "SPI%u SpotConfig", SdCardConfig.spi_num);
        // res= gpio_set_pull( SdCardConfig.chip_sel.byte,   GPIO__PULL_UP);
        res = gpio_set_pull(SpiConfig->PadMosi.byte, GPIO__PULL_UP);
        res = gpio_set_pull(SpiConfig->PadMiso.byte, GPIO__PULL_UP);
        res = gpio_set_pull(SpiConfig->PadSck.byte, GPIO__PULL_AIR);
        wait_ms(50);
    }
    return res;
}

bool sd_card_init(void) {
    bool res = false;
    set_log_level(SD_CARD, LOG_LEVEL_DEBUG);
    LOG_WARNING(SD_CARD, "Init..");

    SdCardInstance.chip_enable_cnt = 0;
    // set_log_level(GPIO, LOG_LEVEL_DEBUG);
    set_log_level(SPI, LOG_LEVEL_DEBUG); /*Works only when SPI, LOG_LEVEL_DEBUG*/

    res = sd_card_spi_gpio_init();

    res = sd_disk_initialize();
    if(res) {
        LOG_INFO(SD_CARD, "InitOk");
    } else {
        LOG_ERROR(SD_CARD, "InitErr");
    }
    set_log_level(GPIO, LOG_LEVEL_INFO);
    set_log_level(SPI, LOG_LEVEL_INFO);
    set_log_level(SD_CARD, LOG_LEVEL_NOTICE);
    return res;
}

bool sd_wait_miso_one(void) {
    bool res = false;
    uint32_t diff_ms = 0;
    uint32_t start_ms = time_get_ms32();
    uint32_t cur_ms = start_ms;
    GpioLogicLevel_t logic_level = GPIO_LVL_UNDEF;
    const SpiConfig_t* SpiConfig = SpiGetConfig(SdCardConfig.spi_num);
    if(SpiConfig) {
        while(1) {
            res = gpio_get_state(SpiConfig->PadMiso.byte, &logic_level);
            if(GPIO_LVL_HI == logic_level) {
                res = true;
                break;
            }
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(SD_ERASE_DONE_TIME_OUT_MS < diff_ms) {
                res = false;
                LOG_ERROR(SD_CARD, "%u EraseTimeOut");
                break;
            }
        }
    }
    return res;
}

bool sd_erase_sector(uint32_t start_block_num, uint32_t end_block_num) {
    bool res = false;
    if(start_block_num <= end_block_num) {
        R1_t R1;
        LOG_DEBUG(SD_CARD, "Errase %u %u", start_block_num, end_block_num);
        res = SD_sendCommand(CMD32, start_block_num);
        if(res) {
            res = false;
            R1.byte = 0;
            res = sd_fetch_resp(&R1.byte);
            if(res) {
                res = false;
#ifdef HAS_SD_CARD_DIAG
                sd_parse_r1(R1.byte);
#endif
                if(0 == R1.byte) {
                    res = true;
                } else {
                    LOG_ERROR(SD_CARD, "SetErraseStartBlockErr");
                }
            }
        }

        if(res) {
            res = SD_sendCommand(CMD33, end_block_num);
            if(res) {
                res = false;
                R1_t R1;
                R1.byte = 0;
                res = sd_fetch_resp(&R1.byte);
                if(res) {
                    res = false;
#ifdef HAS_SD_CARD_DIAG
                    sd_parse_r1(R1.byte);
#endif
                    if(0 == R1.byte) {
                        res = true;
                    } else {
                        LOG_ERROR(SD_CARD, "SetErraseEndBlockErr");
                    }
                }
            }
        }

        if(res) {
            res = SD_sendCommand(CMD38, 0);
            if(res) {
                R1.byte = 0;
                res = sd_fetch_resp(&R1.byte);
                if(res) {
#ifdef HAS_SD_CARD_DIAG
                    sd_parse_r1(R1.byte);
#endif
                    if(0 == R1.byte) {
                        res = true;
                        res = sd_wait_miso_one();
                    } else {
                        LOG_ERROR(SD_CARD, "ErraseBlockErr");
                    }
                }
            }
        }
    }
    return res;
}
