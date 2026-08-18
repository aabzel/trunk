#include "decadriver.h"

#include <string.h>

#include "bit_utils.h"
#include "convert.h"
#include "debug_info.h"
#include "deca_device_api.h"
#include "deca_regs.h"
#include "decadriver_callback.h"
#include "decadriver_config.h"
#ifdef HAS_DECADRIVER_DIAG
#include "decadriver_diag.h"
#endif
#include "gpio_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "super_cycle.h"
#ifdef HAS_TBFP
#include "tbfp_protocol.h"
#endif

#ifdef HAS_DS_TWR
#include "ds_twr.h"
#endif /*HAS_DS_TWR*/

bool decadriver_set_rx(void) {
    bool res = false;
    DecaDriverInstance.rx_it = false;
    int ret = dwt_rxenable(DWT_START_RX_IMMEDIATE);
    if(DWT_SUCCESS == ret) {
        res = true;
        LOG_DEBUG(DECA, "SetRxOk");
    } else {
        res = false;
        LOG_ERROR(DECA, "SetRxErr");
    }
    return res;
}

bool dwm1000_reset(void) {
    bool res = false;
    LOG_DEBUG(DECA, "HwReset");
    set_log_level(GPIO, LOG_LEVEL_INFO);
    switch(DecaDriverConfig.reset_active_level) {
    case GPIO_LVL_LOW: {
        res = gpio_set_pull(DecaDriverConfig.reset.byte, GPIO__PULL_DOWN);
    } break;
    case GPIO_LVL_HI: {
        res = gpio_set_pull(DecaDriverConfig.reset.byte, GPIO__PULL_UP);
    } break;
    default:
        break;
    }
    res = wait_ms(5);

    switch(DecaDriverConfig.reset_active_level) {
    case GPIO_LVL_LOW: {
        res = gpio_set_pull(DecaDriverConfig.reset.byte, GPIO__PULL_UP);

    } break;
    case GPIO_LVL_HI: {
        res = gpio_set_pull(DecaDriverConfig.reset.byte, GPIO__PULL_DOWN);
    } break;
    default:
        break;
    }

    res = wait_ms(2);
    set_log_level(GPIO, LOG_LEVEL_INFO);
    return res;
}

bool decadriver_read_data(void) {
    bool res = false;
    uint32 frame_len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFLEN_MASK;
    if((2 < frame_len) && frame_len <= RX_BUF_LEN) {
        dwt_readrxdata(DecaDriverInstance.buff, frame_len, 0);
        DecaDriverInstance.rx_byte_cnt += frame_len - 2;
        log_level_t log_lev = log_level_get(DECA);
        if(LOG_LEVEL_DEBUG == log_lev) {
            print_mem(DecaDriverInstance.buff, frame_len - 2, true, true, true, true);
        }
        res = true;
        dwt_forcetrxoff();
        decadriver_set_rx();
#ifdef HAS_TBFP
        res = tbfp_proc(DecaDriverInstance.buff, frame_len - 2, IF_UWB, true);
        if(res) {
            LOG_DEBUG(TBFP, "DataProcOk");
        } else {
            LOG_ERROR(TBFP, "DataProcOk");
        }
#endif /*HAS_TBFP*/
    } else {
        LOG_ERROR(DECA, "RxLenErr %u", frame_len);
        res = false;
    }
    return res;
}

static uint32_t UsToDw1000Us(uint32_t duration_us) {
    uint32_t code = ((double)(duration_us * 512)) / ((double)499.2);
    return code;
}

/* 49 days max*/
/*none blocking wait for self test and polling*/
bool decadriver_wait_tx_done_ms(uint32_t wait_pause_ms) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(SYS, "Pause %u ms", wait_pause_ms);
#endif
    if(wait_pause_ms) {
#ifdef HAS_FREE_RTOS
        vTaskDelay(wait_pause_ms / portTICK_RATE_MS);
        res = true;
#endif

        uint32_t start_ms = 0U;
        uint32_t curr_ms = 0U;
        start_ms = time_get_ms32();
        bool loop = true;

        while(loop) {
#ifdef HAS_SUPER_CYCLE
            super_cycle_iteration();
#endif
            curr_ms = time_get_ms32();
            uint32_t diff_ms = curr_ms - start_ms;
            if(wait_pause_ms < diff_ms) {
                res = false;
                LOG_ERROR(DECA, "TimeOut %u", wait_pause_ms);
                loop = false;
                break;
            }

            if(DecaDriverInstance.tx_it) {
                loop = false;
                res = true;
                break;
            }
        }
    } else {
        res = true;
    }
    return res;
}

static bool decadriver_init_cache(DecaDriverInstance_t* instance) {
    bool res = false;
    if(instance) {
        memset(instance, 0, sizeof(DecaDriverInstance_t));
        instance->valid = true;
        instance->spi_link_err_cnt = 0;
        instance->proc_cnt = 0;
    }
    return res;
}

bool decadriver_init(void) {
    bool res = false;
    LOG_DEBUG(DECA, "Init");
    decadriver_init_cache(&DecaDriverInstance);
    DecaDriverInstance.spi_num = DecaDriverConfig.spi_num;
    dwm1000_reset();
    // set_log_level(SPI, LOG_LEVEL_DEBUG);
    // set_log_level(DECA, LOG_LEVEL_DEBUG);
    int ret = dwt_initialise(DecaDriverConfig.init_arg);
    if(DWT_SUCCESS == ret) {
        res = true;
        LOG_DEBUG(DECA, "InitOk");

        dwt_config_t LocalColfig = {0};
        memcpy(&LocalColfig, &DecaDriverConfig.config, sizeof(dwt_config_t));
        dwt_configure(&LocalColfig);

        dwt_setcallbacks(&tx_conf_callback, &rx_ok_callback, &rx_to_callback, &rx_err_callback);

        dwt_enablegpioclocks();
        /* Apply default antenna delay value. See NOTE 1 below. */
        dwt_setrxantennadelay(RX_ANT_DLY);
        dwt_settxantennadelay(TX_ANT_DLY);

        // dwt_setrxaftertxdelay(UsToDw1000Us(DecaDriverConfig.rx_delay_us));
        dwt_setrxtimeout(UsToDw1000Us(DecaDriverConfig.rx_timeout_us));
        dwt_setpreambledetecttimeout(DecaDriverConfig.preamble_detect_timeout_pac);
        // dwt_setinterrupt(DWT_INT_ALL, 1);

        res = decadriver_set_rx();
    } else {
        LOG_ERROR(DECA, "InitErr %d=%s", ret, DecaErrToStr(ret));
    }
    // set_log_level(SPI, LOG_LEVEL_INFO);
    // set_log_level(DECA, DecaDriverConfig.log_level);
    return res;
}

bool decadriver_is_connected(DecaDriverInstance_t* const item) {
    bool res = false;
    uint32 devid = dwt_readdevid();
    if(DWT_DEVICE_ID == devid) {
        res = true;
        item->connected = true;
        LOG_PARN(DECA, "Connected!");
    } else {
        LOG_ERROR(DECA, "WrongDevIdErr: 0x%04x Exp:0x%04x", devid, DWT_DEVICE_ID);
        res = false;
        item->err_cnt++;
        item->connected = false;
    }
    return res;
}

bool decadriver_tx(const uint8_t* const buff, uint32_t size) {
    bool res = false;
#ifdef HAS_DECADRIVER_TX
    if(buff) {
        if(size) {
            LOG_DEBUG(DECA, "Tx %u byte", size);
            DecaDriverInstance.tx_it = false;
            dwt_forcetrxoff();

            int ret = DWT_ERROR;
            ret = dwt_writetxdata(size + 2, (uint8*)buff, 0); /* Zero offset in TX buffer. */
            if(DWT_SUCCESS == ret) {
                res = true;
                dwt_writetxfctrl(size + 2, 0, 1); /* Zero offset in TX buffer, ranging. */
                ret = dwt_starttx(DWT_START_TX_IMMEDIATE);
                if(DWT_SUCCESS == ret) {
                    LOG_DEBUG(DECA, "StartTxOk");
                    res = true;
                } else {
                    LOG_ERROR(DECA, "StartTxErr");
                    res = false;
                }
            } else {
                LOG_ERROR(DECA, "WriteTxDataErr");
                res = false;
            }
        }
    }
#else
    LOG_ERROR(DECA, "TxIsProhibitedInCompilation");
#endif
    return res;
}

bool decadriver_proc(void) {
    bool res = false;

#ifdef HAS_DECA_POLL_CONNECTED
    res = decadriver_is_connected(&DecaDriverInstance);
#else
    res = true;
#endif
    if(res) {
        LOG_PARN(DECA, "Connected!");
        DecaDriverInstance.spi_link_err_cnt = 0;
        DecaDriverInstance.proc_cnt++;
        // DecaDriverInstance.status_reg = dwt_read32bitreg(SYS_STATUS_ID);
        // decadriver_proc_status(&DecaDriverInstance, DecaDriverInstance.status_reg);
        dwt_isr();

#ifdef HAS_DECA_POLL_TIME_STAMP
        dwt_readtxtimestamp((uint8*)&DecaDriverInstance.tx_time_stamp.cur);
        dwt_readrxtimestamp((uint8*)&DecaDriverInstance.rx_time_stamp.cur);

        if(DecaDriverInstance.tx_time_stamp.cur != DecaDriverInstance.tx_time_stamp.prev) {
            LOG_NOTICE(DECA, "TxStamp %llu", DecaDriverInstance.tx_time_stamp.cur);
#ifdef HAS_DS_TWR
            res = ds_twr_proc_tx_time(&DsTwrItem, DecaDriverInstance.tx_time_stamp.cur);
#endif /*HAS_DS_TWR*/
        }

        if(DecaDriverInstance.rx_time_stamp.cur != DecaDriverInstance.rx_time_stamp.prev) {
            LOG_NOTICE(DECA, "RxStamp %llu", DecaDriverInstance.rx_time_stamp.cur);
#ifdef HAS_DS_TWR
            res = ds_twr_proc_rx_time(&DsTwrItem, DecaDriverInstance.rx_time_stamp.cur);
#endif /*HAS_DS_TWR*/
        }

        DecaDriverInstance.tx_time_stamp.prev = DecaDriverInstance.tx_time_stamp.cur;
        DecaDriverInstance.rx_time_stamp.prev = DecaDriverInstance.rx_time_stamp.cur;
#endif /*HAS_DECA_POLL_TIME_STAMP*/
    } else {
        DecaDriverInstance.spi_link_err_cnt++;
        LOG_ERROR(DECA, "SPI%U LinkErr After %u try", DecaDriverInstance.spi_num, DecaDriverInstance.spi_link_err_cnt);
        /*reboot DW1000*/
        if(100 < DecaDriverInstance.spi_link_err_cnt) {
            res = dwm1000_reset();
            res = decadriver_init();
        }
        res = false;
    }
    return res;
}
