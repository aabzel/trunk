#include "sdio_mcal.h"

#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "code_generator.h"
#include "data_utils.h"
#include "debug_info.h"
#include "disk_const.h"
#include "hal_diag.h"
#include "sdio_register_types.h"
#include "interrupt_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "sdio_int.h"
#include "sdio_poll.h"
#include "time_mcal.h"

#ifdef HAS_SDIO_DMA
#include "sdio_dma.h"
#endif

static SdioInfo_t SdioInfo[] = {
    {
        .num = 1,
        .valid = true,
        .irq_n = SDIO_IRQn,
        .SDIOx = SDIO,
    },
};

COMPONENT_GET_INFO(Sdio)

uint8_t SdioInstance2num(const SD_TypeDef* const SDIOx) {
    uint8_t num = 1;
    if(SDIO == SDIOx) {
        num = 1;
    }
    return num;
}

bool SdioWaitTxDoneLl(SdioHandle_t* Node, uint32_t time_out, uint8_t num, uint32_t block_num) {
    bool res = true;
    uint32_t cur_ms = 0;
    uint32_t diff_ms = 0;
    uint32_t start_ms = time_get_ms32();
    while(false == Node->tx_done) {
        cur_ms = time_get_ms32();
        diff_ms = cur_ms - start_ms;
        if(time_out < diff_ms) {
            LOG_ERROR(LG_SDIO, "SDIO%u,WriteBlock:%u,TimeOut", num, block_num);
            break;
            res = false;
        }

        if(HAL_SD_STATE_READY == Node->Handle.State) {
            res = true;
            break;
        }
    }
    return res;
}

bool SdioWaitRxDoneLl(SdioHandle_t* const Node, uint32_t time_out_ms, uint8_t num, uint32_t block_num) {
    bool res = true;
    uint32_t cur_ms = 0;
    uint32_t diff_ms = 0;
    uint32_t start_ms = time_get_ms32();
    while(false == Node->rx_done) {
        cur_ms = time_get_ms32();
        diff_ms = cur_ms - start_ms;
        if(time_out_ms < diff_ms) {
            LOG_ERROR(LG_SDIO, "SDIO%u ReadBlock %u TimeOut", num, block_num);
            res = false;
            break;
        }

        if(HAL_SD_STATE_READY == Node->Handle.State) {
            res = true;
            break;
        }
    }
    return res;
}

#ifdef HAS_SDIO_DMA

#endif

void HAL_SD_MspInit(SD_HandleTypeDef* sdHandle) {
    if(SDIO == sdHandle->Instance) {
        __HAL_RCC_SDIO_CLK_ENABLE();
        HAL_NVIC_SetPriority(SDIO_IRQn, 2, 2); /*Crusial*/
        HAL_NVIC_EnableIRQ(SDIO_IRQn);
#ifdef HAS_SDIO_DMA
        sdio_dma_init(sdHandle);
#endif /*HAS_SDIO_DMA*/
    }
}

void HAL_SD_MspDeInit(SD_HandleTypeDef* sdHandle) {
    if(SDIO == sdHandle->Instance) {
        __HAL_RCC_SDIO_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(SDIO_IRQn);
    }
}

bool sdio_read_sector(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData) {
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
#ifdef HAS_SDIO_DEBUG
        LOG_DEBUG(LG_SDIO, "ReadBlock Num:%u BlkNum:%u BlkCnt:%u", num, block_num, block_cnt);
#endif
        uint32_t try = 0;
        bool read_ok = false;
        for(try = 0; try <= SDIO_READ_TRY_CNT; try ++) {
            res = false;
            switch(Node->move_mode) {
            case MOVE_MODE_POLLING: {
#ifdef HAS_SDIO_POLL
                res = sdio_read_sector_time_out(num, block_num, block_cnt, RxData);
#endif

            } break;
            case MOVE_MODE_INTERRUPT: {
#ifdef HAS_SDIO_INTERRUPT
                res = sdio_read_sector_it(num, block_num, block_cnt, RxData);
#endif

            } break;
            case MOVE_MODE_DMA: {
#ifdef HAS_SDIO_DMA
                res = sdio_read_sector_dma(num, block_num, block_cnt, RxData);
#endif

            } break;
            default: {
#ifdef HAS_SDIO_POLL
                res = sdio_read_sector_time_out(num, block_num, block_cnt, RxData);
#endif
            } break;
            }

            Node->read_cnt++;
            if(res) {
                read_ok = true;
                Node->read_ok_cnt++;
#ifdef HAS_SDIO_DEBUG
                LOG_DEBUG(LG_SDIO, "ReadBlockOk Num:%u BlkNum:%u try:%u", num, block_num, try);
#endif
                Node->try_read_cnt++;
                break;
            } else {
                Node->read_err_cnt++;
            }
        } // for (try = 0; try
        if(false == read_ok) {
            LOG_ERROR(LG_SDIO, "ReadBlock Num:%u BlkNum:%u BlkCnt:%u err", num, block_num, block_cnt);
        }
    }

    return res;
}

bool sdio_write_sector(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const TxData) {
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
#ifdef HAS_SDIO_DEBUG
        LOG_DEBUG(LG_SDIO, "WriteBlock,Num:%u,BlkNum:%u,BlkCnt:%u", num, block_num, block_cnt);
#endif
        uint32_t try_cnt = 0;
        for(try_cnt = 0; try_cnt < SDIO_WRITE_TRY_CNT; try_cnt++) {
            res = false;
            switch(Node->move_mode) {
            case MOVE_MODE_DMA: {
#ifdef HAS_SDIO_DMA
                res = sdio_write_sector_dma(num, block_num, block_cnt, TxData);
#endif
            } break;
            case MOVE_MODE_POLLING: {
#ifdef HAS_SDIO_POLL
                res = sdio_write_sector_time_out(num, block_num, block_cnt, TxData);
#endif
            } break;
            case MOVE_MODE_INTERRUPT: {
#ifdef HAS_SDIO_INTERRUPT
                res = sdio_write_sector_it(num, block_num, block_cnt, TxData);
#endif
            } break;
            default: {
#ifdef HAS_SDIO_POLL
                res = sdio_write_sector_time_out(num, block_num, block_cnt, TxData);
#endif
            } break;
            }

          //  wait_ms(SDIO_TIME_OUT_MS); /*TODO: minimize that time*/
            if(res) {
#ifdef HAS_SDIO_DEBUG
                LOG_DEBUG(LG_SDIO, "WriteBlockOk,Num:%u,BlkNum:%u,try:%u", num, block_num, try_cnt);
#endif
                Node->try_write_cnt++;
                break;
            }
        }
    }
    return res;
}

/* 0-84MHz */
/* 1-48MHz */
/* 2-28MHz */
/* 3-21MHz */
/* 4-16MHz */
/* 5-14MHz */
static uint32_t SdioCalcClockDiv(uint32_t apb2_clk2, uint32_t bit_rate_hz) {
    uint32_t clock_div = 0;
    LOG_INFO(LG_SDIO, "APB2 Clock %u Hz(Max: 84 MHz) DesClk %u Hz", apb2_clk2, bit_rate_hz);
    double tapb2 = 1.0 / ((double)apb2_clk2);
    double tclk = 1.0 / ((double)bit_rate_hz);
    LOG_INFO(LG_SDIO, "tapb2 %f", tapb2);
    LOG_INFO(LG_SDIO, "tclk %f", tclk);
    double needed_div = tclk / tapb2;
    LOG_INFO(LG_SDIO, "CalcDiv %f", needed_div);
    clock_div = (uint32_t)needed_div;
    LOG_INFO(LG_SDIO, "CalcDiv %f =%u", needed_div, clock_div);
    double read_clock = 1.0 / ((tapb2) * ((double)clock_div));

    LOG_INFO(LG_SDIO, "RealSDIOclock %f Hz", read_clock);
    return clock_div - 1;
}

static bool sdio_init_handle(SdioHandle_t* const Node, const SdioConfig_t* Config) {
    bool res = false;
    if(Node) {
        Node->Handle.Instance = SDIO;
        Node->Handle.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
        Node->Handle.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
        Node->Handle.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
        Node->Handle.Init.BusWide = SDIO_BUS_WIDE_1B;
        Node->Handle.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
        uint32_t pclk2 = HAL_RCC_GetPCLK2Freq();
        if(pclk2) {
            LOG_INFO(LG_SDIO, "PCLK2:%u Hz", pclk2);
            uint32_t clock_div = SdioCalcClockDiv(pclk2, Config->bit_rate_hz);
            clock_div = uint32_limiter(clock_div, 254);
            LOG_INFO(LG_SDIO, "FinalClockDiv:%u", clock_div);
            Node->Handle.Init.ClockDiv = clock_div;
            res = true;
        }
        Node->Handle.Init.ClockDiv =3;
    }
    return res;
}

bool sdio_init_4bit_mode(SdioHandle_t* Node) {
    bool res = false;
    HAL_StatusTypeDef ret = HAL_ERROR;
    ret = HAL_SD_ConfigWideBusOperation(&Node->Handle, SDIO_BUS_WIDE_4B);
    if(HAL_OK == ret) {
        LOG_INFO(LG_SDIO, "4BitInitOk", Node->num);
        res = true;
    } else {
        res = false;
        LOG_ERROR(LG_SDIO, "4BitInitErr", Node->num);
#ifdef HAS_SDIO_DIAG
        LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->Handle.ErrorCode, HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
    }
    return res;
}

bool sdio_init_test(SdioHandle_t* Node) {
    bool res = false;
    res = sdio_read_sector(Node->num, 2, 1, Node->RxData);
    if(res) {
        LOG_INFO(LG_SDIO, "TestReadOk", Node->num);
    } else {
        LOG_ERROR(LG_SDIO, "TestReadErr", Node->num);
    }
    return res;
}

static bool sdio_init_card(SdioHandle_t* Node) {
    bool res = false;
    HAL_StatusTypeDef ret = HAL_ERROR;
    ret = HAL_SD_InitCard(&Node->Handle);
    if(HAL_OK == ret) {
        LOG_INFO(LG_SDIO, "CardInitOk", Node->num);
        res = true;
    } else {
        LOG_ERROR(LG_SDIO, "CardInitErr %s", HalStatusToStr(ret));
#ifdef HAS_SDIO_DIAG
        LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->Handle.ErrorCode, HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
        res = false;
    }
    return res;
}

bool sdio_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LG_SDIO, "SDIO%u,Init", num);
    SdioHandle_t* Node = SdioGetNode(num);
    const SdioConfig_t* Config = SdioGetConfig(num);
    if(Config) {
        res = SdioIsValidConfig(Config);
        if(res) {
            SdioInfo_t* Info = SdioGetInfo(num);
            if(Info) {
                if(Node) {
                    Node->SDIOx = Info->SDIOx;
                    res = sdio_init_common(Config, Node);
                    __HAL_RCC_SDIO_CLK_ENABLE();
                    res = sdio_init_handle(Node, Config);
                    HAL_StatusTypeDef ret = HAL_ERROR;
                    ret = HAL_SD_Init(&Node->Handle);
                    if(HAL_OK == ret) {
                        res = interrupt_control(Info->irq_n, Config->interrupt_on);
#ifdef HAS_SDIO_DMA
                        res = sdio_dma_init(&Node->Handle);
#endif

#ifdef HAS_SDIO_4BIT
                        res = sdio_init_4bit_mode(Node);
#endif

#ifdef HAS_SDIO_INIT_TEST
                        res = sdio_init_test(Node);
#endif
                    } else {
                        LOG_ERROR(LG_SDIO, "InitErr %s", HalStatusToStr(ret));
#ifdef HAS_SDIO_DIAG
                        LOG_ERROR(LG_SDIO, "ErrorCode 0x%x=%s", Node->Handle.ErrorCode,
                                  HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
                        res = false;
                    }
#ifdef HAS_SD_CARD_INIT
                    res = sdio_init_card(Node);
#endif
                }
            }
        }
    }
    log_level_set(LG_SDIO, LOG_LEVEL_INFO);
    return res;
}

#if 0
bool sdio_mcal_init(void) {
    bool res = false;
    uint32_t num = 0;
    uint32_t ok_cnt = 0;
    uint32_t sdio_cnt = 0;

    log_level_set(LG_SDIO, LOG_LEVEL_INFO);

    sdio_cnt = sdio_get_cnt();
    LOG_INFO(LG_SDIO, "Total:%u", sdio_cnt);
    for(num = 0; num <= sdio_cnt; num++) {
        res = sdio_init_one(num);
        if(res) {
            ok_cnt++;
        }
    }

    if(ok_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

#endif

uint32_t sdio_get_block_num(uint32_t num) {
    uint32_t block_num = 0;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_SD_GetCardInfo(&Node->Handle, &Node->CardInfo);
        if(HAL_OK == ret) {
            block_num = Node->CardInfo.LogBlockNbr;
        }
    }
    return block_num;
}

uint16_t sdio_get_block_size(uint32_t num) {
    uint16_t block_size = 0;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_SD_GetCardInfo(&Node->Handle, &Node->CardInfo);
        if(HAL_OK == ret) {
            block_size = Node->CardInfo.LogBlockSize;
        }
    }
    return block_size;
}

bool sdio_card_info_get(uint32_t num) {
    bool res = true;
    uint32_t ok_cnt = 0;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_SD_GetCardStatus(&Node->Handle, &Node->status);
        if(HAL_OK != ret) {
            LOG_DEBUG(LG_SDIO, "GetStatusErr %u=%s", ret, HalStatusToStr(ret));
            memset(&Node->status, 0, sizeof(HAL_SD_CardStatusTypeDef));
            res = false;
        } else {
            ok_cnt++;
        }
        ret = HAL_SD_GetCardCID(&Node->Handle, &Node->CID);
        if(HAL_OK != ret) {
            LOG_ERROR(LG_SDIO, "GetCIDErr %s", HalStatusToStr(ret));
            res = false;
        } else {
            ok_cnt++;
        }
        ret = HAL_SD_GetCardCSD(&Node->Handle, &Node->CSD);
        if(HAL_OK != ret) {
            LOG_ERROR(LG_SDIO, "GetCSDErr %s", HalStatusToStr(ret));
            res = false;
        } else {
            ok_cnt++;
        }
        ret = HAL_SD_GetCardInfo(&Node->Handle, &Node->CardInfo);
        if(HAL_OK != ret) {
            LOG_ERROR(LG_SDIO, "GetCardInfoErr %s", HalStatusToStr(ret));
            res = false;
        } else {
            ok_cnt++;
        }
    } else {
        res = false;
    }

    if(ok_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

#if 0
bool sdio_is_connected(uint32_t num) {
    bool res = true;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret = HAL_SD_GetCardStatus(&Node->Handle, &Node->status);
        if(HAL_OK != ret) {
            LOG_DEBUG(LG_SDIO, "GetCardStatusErr");
            if(Node->Handle.ErrorCode) {
#ifdef HAS_SDIO_DIAG
                LOG_DEBUG(LG_SDIO, "ErrorCode 0x%x=%s", Node->Handle.ErrorCode,
                        HalSdioErrCode2Str(Node->Handle.ErrorCode));
#endif
                // res=sdio_init();
            }
        }

        Node->SD_CardState = HAL_SD_GetCardState(&Node->Handle);
        switch(Node->SD_CardState) {
            case 0: {
                res = true;
            }break;
            case HAL_SD_CARD_READY: {
                res = true;
            }break;
            case HAL_SD_CARD_IDENTIFICATION: {
                res = true;
            }break;
            case HAL_SD_CARD_STANDBY: {
                res = true;
            }break;
            case HAL_SD_CARD_TRANSFER: {
                res = true;
            }break;
            case HAL_SD_CARD_SENDING: {
                res = true;
            }break;
            case HAL_SD_CARD_RECEIVING: {
                res = true;
            }break;
            case HAL_SD_CARD_PROGRAMMING: {
                res = true;
            }break;
            case HAL_SD_CARD_ERROR: {
                LOG_DEBUG(LG_SDIO, "CardErr");
                res = false;
            }break;
            case HAL_SD_CARD_DISCONNECTED: {
                LOG_ERROR(LG_SDIO, "CardDisconnected");
                res = false;
            }break;
            default: {
                LOG_ERROR(LG_SDIO, "Card %u-%s", Node->SD_CardState, CardState2Str(Node->SD_CardState));
            }break;
        }
        res = sdio_read_sector(num, 2, 1, Node->RxData);
        if(res) {
            LOG_DEBUG(LG_SDIO, "CardConnected");
        } else {
            LOG_ERROR(LG_SDIO, "CardDisconnected");
        }
    }

    return res;
}
#endif

/*
  pdrv,  Physical drive nmuber (0..)
  cmd,  Control code
  buff  Buffer to send/receive control data
  */
uint8_t sdio_ioctl(uint8_t num, uint8_t cmd, void* buff) {
    uint8_t ret = RES_ERROR;
    // bool res = false;
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef err;
        err = HAL_SD_GetCardInfo(&Node->Handle, &Node->CardInfo);
        if(HAL_OK == err) {
            switch(cmd) {
            case CTRL_SYNC: {
                ret = RES_OK;
            } break;
            case GET_SECTOR_COUNT: {
                LOG_DEBUG(DISK, "BlockNbr %u", Node->CardInfo.BlockNbr);
                *((uint32_t*)buff) = Node->CardInfo.BlockNbr;
                ret = RES_OK;
            } break;
            case GET_SECTOR_SIZE: {
                LOG_DEBUG(DISK, "BlockSize %u", Node->CardInfo.BlockSize);
                *((uint32_t*)buff) = Node->CardInfo.BlockSize;
                ret = RES_OK;
            } break;
            case GET_BLOCK_SIZE: {
                LOG_DEBUG(DISK, "GET_BLOCK_SIZE %u", Node->CardInfo.BlockSize / SDIO_BLOCK_SIZE);
                *(uint32_t*)buff = Node->CardInfo.BlockSize / SDIO_BLOCK_SIZE;
                ret = RES_OK;
            } break;
            } // switch
        } else {
            LOG_ERROR(DISK, "HalErr %u=%s", err, HalStatusToStr(err));
        }
    }

    return ret;
}

bool sdio_proc_card_state(HAL_SD_CardStateTypeDef card_state) {
    bool res = false;
    switch(card_state) {
    case 0: {
        res = true;
    } break;
    case HAL_SD_CARD_READY: {
        res = true;
    } break;
    case HAL_SD_CARD_IDENTIFICATION: {
        res = true;
    } break;
    case HAL_SD_CARD_STANDBY: {
        res = true;
    } break;
    case HAL_SD_CARD_TRANSFER: {
        res = true;
    } break;
    case HAL_SD_CARD_SENDING: {
        res = true;
    } break;
    case HAL_SD_CARD_RECEIVING: {
        res = true;
    } break;
    case HAL_SD_CARD_PROGRAMMING: {
        res = true;
    } break;
    case HAL_SD_CARD_ERROR: {
        LOG_DEBUG(LG_SDIO, "CardErr");
        res = false;
    } break;
    case HAL_SD_CARD_DISCONNECTED: {
        LOG_ERROR(LG_SDIO, "CardDisconnected");
        res = false;
    } break;
    default: {
        LOG_ERROR(LG_SDIO, "CardState:%u-%s", card_state, CardState2Str(card_state));
    } break;
    }
    return res;
}

bool sdio_proc_status(SdioHandle_t* Node) {
    bool res = false;
    if(Node->SDIOx) {
        SdioRegSDIO_STA_t SDIO_STA;
        SDIO_STA.dword = Node->SDIOx->STA;
        res = SdioStatusDiag(SDIO_STA.dword);
    }
    return res;
}

bool sdio_proc_one(uint8_t num) {
    bool res = false;
#if 0
    res = sdio_is_connected(num);
    if(false == res) {
        LOG_ERROR(LG_SDIO, "CardDisconnected");
    } else {
        res = sdio_card_info_get(num);
    }
#endif
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
#if 0
        HAL_SD_CardStateTypeDef card_state = HAL_SD_GetCardState(&Node->Handle);
        sdio_proc_card_state(card_state);

        sdio_proc_status(Node);
#endif

        res = true;
        if(Node->rx_cnt_prev < Node->rx_cnt) {
            int32_t rx_diff = Node->rx_cnt - Node->rx_cnt_prev;
            LOG_WARNING(LG_SDIO, "RxInterrupt %u +%u %u ms", Node->rx_cnt, rx_diff, Node->rx_time_stamp);
        }

        if(Node->tx_cnt_prev < Node->tx_cnt) {
            int32_t tx_diff = Node->tx_cnt - Node->tx_cnt_prev;
            LOG_WARNING(LG_SDIO, "TxInterrupt %u +%u %u ms", Node->tx_cnt, tx_diff, Node->tx_time_stamp);
        }
        Node->tx_cnt_prev = Node->tx_cnt;
        Node->rx_cnt_prev = Node->rx_cnt;
    }
    return res;
}
