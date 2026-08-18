#include "decadriver.h"

#include <string.h>

#include "bit_utils.h"
#include "convert.h"
#include "debug_info.h"
#include "deca_device_api.h"
#include "deca_regs.h"
#include "decadriver_config.h"
#include "gpio_drv.h"
#include "log.h"
#include "none_blocking_pause.h"

static bool decadriver_set_rx(void) {
    bool res = false;
    // dwt_rxreset() ;
    int ret = dwt_rxenable(DWT_START_RX_IMMEDIATE);
    if(DWT_SUCCESS == ret) {
        res = true;
        LOG_INFO(DECA, "SetRxOk");
    } else {
        res = false;
        LOG_ERROR(DECA, "SetRxErr");
    }
    return res;
}

bool dwm1000_reset(void) {
    bool res = false;
    LOG_WARNING(DECA, "HwReset");
    set_log_level(GPIO, LOG_LEVEL_DEBUG);
    res = gpio_set_pull(DecaDriverConfig.reset.byte, GPIO__PULL_DOWN);
    res = wait_ms(5);

    res = gpio_set_pull(DecaDriverConfig.reset.byte, GPIO__PULL_AIR);
    res = wait_ms(2);
    set_log_level(GPIO, LOG_LEVEL_INFO);
    return res;
}

static bool decadriver_read_data(void) {
    bool res = false;
    uint32 frame_len = dwt_read32bitreg(RX_FINFO_ID) & RX_FINFO_RXFLEN_MASK;
    if((2 < frame_len) && frame_len <= RX_BUF_LEN) {
        dwt_readrxdata(DecaDriverInstance.buff, frame_len, 0);
        print_mem(DecaDriverInstance.buff, frame_len - 2, true, true, true, true);
        res = true;
        int ret = dwt_rxenable(DWT_START_RX_IMMEDIATE);
        if(DWT_SUCCESS == ret) {
            LOG_INFO(DECA, "RxSetOk");
        } else {
            LOG_ERROR(DECA, "RxSetErr");
        }
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

/*!
 * @fn rx_ok_cb()
 * @brief Callback to process RX good frame events
 * @param  cb_data  callback data
 * @return  none
 */
static void rx_ok_cb(const dwt_cb_data_t* cb_data) {
    LOG_WARNING(DECA, "RxOkCallBack");
    decadriver_read_data();
    // decadriver_set_rx();
}

/*!
 * @fn rx_to_cb()
 *
 * @brief Callback to process RX timeout events
 * @param  cb_data  callback data
 * @return  none
 */
static void rx_to_cb(const dwt_cb_data_t* cb_data) {
    LOG_WARNING(DECA, "RxTimeOutCallBack");
    // decadriver_set_rx();
}

/*!
 * @fn rx_err_cb()
 *
 * @brief Callback to process RX error events
 *
 * @param  cb_data  callback data
 *
 * @return  none
 */
static void rx_err_cb(const dwt_cb_data_t* cb_data) {
    LOG_WARNING(DECA, "RxErrCallBack");
    // decadriver_set_rx();
}

/*!
 * @fn tx_conf_cb()
 * @brief Callback to process TX confirmation events
 * @param  cb_data  callback data
 * @return  none
 */
static void tx_conf_cb(const dwt_cb_data_t* cb_data) {
    LOG_WARNING(DECA, "TxConfirmCallBack");
    // decadriver_set_rx();
}

bool decadriver_init(void) {
    bool res = false;
    LOG_INFO(DECA, "Init");

    dwm1000_reset();
    set_log_level(SPI, LOG_LEVEL_INFO);

    int ret = dwt_initialise(DecaDriverConfig.init_arg);
    if(DWT_SUCCESS == ret) {
        res = true;
        LOG_INFO(DECA, "InitOk");

        dwt_config_t LocalColfig = {0};
        memcpy(&LocalColfig, &DecaDriverConfig.config, sizeof(dwt_config_t));
        dwt_configure(&LocalColfig);

        dwt_setcallbacks(&tx_conf_cb, &rx_ok_cb, &rx_to_cb, &rx_err_cb);

        /* Apply default antenna delay value. See NOTE 1 below. */
        dwt_setrxantennadelay(RX_ANT_DLY);
        dwt_settxantennadelay(TX_ANT_DLY);

        // dwt_setrxaftertxdelay(UsToDw1000Us(DecaDriverConfig.rx_delay_us));
        dwt_setrxtimeout(UsToDw1000Us(DecaDriverConfig.rx_timeout_us));
        dwt_setpreambledetecttimeout(DecaDriverConfig.preamble_detect_timeout_pac);

        // dwt_setinterrupt(DWT_INT_ALL, 1);

        res = decadriver_set_rx();
    } else {
        LOG_ERROR(DECA, "InitErr %d", ret);
    }
    set_log_level(SPI, LOG_LEVEL_INFO);
    set_log_level(DECA, LOG_LEVEL_INFO);
    return res;
}

bool decadriver_is_connected(DecaDriverInstance_t* const item) {
    bool res = false;
    uint32 devid = dwt_readdevid();
    if(DWT_DEVICE_ID == devid) {
        res = true;
        item->connected = true;
    } else {
        res = false;
        item->err_cnt++;
        item->connected = false;
    }
    return res;
}

bool decadriver_tx(uint8_t* buff, uint32_t size) {
    bool res = false;
    // dwt_rxreset();

    LOG_INFO(DECA, "Tx %u byte", size);
    int ret = DWT_ERROR;
    ret = dwt_writetxdata(size, buff, 0); /* Zero offset in TX buffer. */
    if(DWT_SUCCESS == ret) {
        res = true;
        dwt_writetxfctrl(size, 0, 1); /* Zero offset in TX buffer, ranging. */
        ret = dwt_starttx(DWT_START_TX_IMMEDIATE);
        if(DWT_SUCCESS == ret) {
            LOG_INFO(DECA, "StartTxOk");
            res = true;
        } else {
            LOG_ERROR(DECA, "StartTxErr");
            res = false;
        }
    } else {
        LOG_ERROR(DECA, "WriteTxDataErr");
        res = false;
    }
    return res;
}

static bool decadriver_dummy_foo(void) {
    bool res = true;
    return res;
}

#define SYS_STATUS_PROC(LOG_LEVEL, MASK, TEXT, HANDLER)                                                                \
    do {                                                                                                               \
        if(MASK & sys_status_reg) {                                                                                    \
            processed_bit_cnt++;                                                                                       \
            log_write(LOG_LEVEL, DECA, TEXT);                                                                          \
            HANDLER();                                                                                                 \
        }                                                                                                              \
    } while(0);

static bool decadriver_proc_status(DecaDriverInstance_t* const item, uint32 sys_status_reg) {
    bool res = false;

    if(sys_status_reg) {
        dwt_write32bitreg(SYS_STATUS_ID, sys_status_reg);

        int8_t total_set_bit_cnt = count_set_bits(sys_status_reg);
        LOG_WARNING(DECA, "SomethingHappened SYS_STATUS 0x%08x = 0b_%s SetBits %u", sys_status_reg,
                    utoa_bin32(sys_status_reg), total_set_bit_cnt);
        int8_t processed_bit_cnt = 0;

        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_IRQS, "Interrupt Request Status", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_CPLOCK, "Clock PLL Lock", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_ESYNCR, "External Sync Clock Reset", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_AAT, "Automatic Acknowledge Trigger", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_TXFRB, "TxFrame Begins", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_TXPRS, "TxPreamble Sent", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_TXPHS, "TxPHY Header Sent", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_TXFRS, "TxFrameSent", decadriver_set_rx);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_RXPRD, "Receiver Preamble Detected status", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_RXSFDD, "Receiver Start Frame Delimiter Detected",
                        decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_LDEDONE, "LDE processing done", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_RXPHD, "Receiver PHY Header Detect", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_RXDFR, "Receiver Data Frame Ready", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_RXRFTO, "Receive Frame Wait Timeout", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_RXOVRR, "Receiver Overrun", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_WARNING, SYS_STATUS_RXPTO, "Preamble detection timeout", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_GPIOIRQ, "GPIO interrupt", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_SLP2INIT, "SLEEP to INIT", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_RFPLL_LL, "RF PLL Losing Lock", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_CLKPLL_LL, "Clock PLL Losing Lock", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_WARNING, SYS_STATUS_HPDWARN, "Half Period Delay Warning", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_TXBERR, "TxBuffer Error", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_HSRBP, "Host Side Receive Buffer Pointer", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_ICRBP, "IC side Receive Buffer Pointer", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_RXPHE, "RxPHY HeaderErr", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_RXFCE, "RxFCSErr", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_RXRFSL, "RxReed Solomon Frame Sync Loss", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_RXSFDTO, "RxSFD timeout", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_AFFREJ, "Automatic Frame Filtering rejection",
                        decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_LDEERR, "Leading edge detection processingErr",
                        decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_ALL_RX_TO, "RxTimeOut", decadriver_dummy_foo);
        SYS_STATUS_PROC(LOG_LEVEL_ERROR, SYS_STATUS_ALL_RX_ERR, "RxErr", decadriver_set_rx);
        SYS_STATUS_PROC(LOG_LEVEL_INFO, SYS_STATUS_RXFCG, "RxFCSGood", decadriver_read_data);

        if(processed_bit_cnt < total_set_bit_cnt) {
            LOG_ERROR(DECA, "UnProcBits %d", total_set_bit_cnt - processed_bit_cnt);
        } else if(total_set_bit_cnt < processed_bit_cnt) {
            LOG_ERROR(DECA, "TooMuchProcBits %d", processed_bit_cnt);
        } else {
            LOG_INFO(DECA, "All %d BitsProcessed", processed_bit_cnt);
        }
    }

    return res;
}

bool decadriver_proc(void) {
    bool res = false;
    res = decadriver_is_connected(&DecaDriverInstance);
    if(res) {
        // DecaDriverInstance.status_reg = dwt_read32bitreg(SYS_STATUS_ID);
        // decadriver_proc_status(&DecaDriverInstance, DecaDriverInstance.status_reg);
        dwt_isr();
    } else {
        LOG_ERROR(DECA, "SpiLinkErr");
        res = false;
    }
    return res;
}
