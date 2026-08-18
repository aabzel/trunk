
#include "decadriver_callback.h"

#include "decadriver.h"
#include "log.h"
#ifdef HAS_DS_TWR
#include "ds_twr.h"
#endif /*HAS_DS_TWR*/

/*!
 * @fn rx_ok_callback()
 * @brief Callback to process RX good frame events
 * @param  cb_data  callback data
 * @return  none
 */
void rx_ok_callback(const dwt_cb_data_t* cb_data) {
    bool res = false;
    LOG_DEBUG(DECA, "RxOkCallBack");
    DecaDriverInstance.rx_it = true;
    DecaDriverInstance.rx_cnt++;
    res = decadriver_read_data();
    if(res) {
        LOG_DEBUG(DECA, "RxDataOk");
    } else {
        LOG_PROTECTED(DECA, "RxDataErr");
    }

    dwt_readrxtimestamp((uint8*)&DecaDriverInstance.rx_time_stamp.cur);
    LOG_PROTECTED(DECA, "SpotRxTime %llu", DecaDriverInstance.rx_time_stamp.cur);

#ifdef HAS_DS_TWR
    res = ds_twr_proc_rx_time(&DsTwrItem, DecaDriverInstance.rx_time_stamp.cur);
    if(false == res) {
        LOG_PROTECTED(DECA, "ProcRxTimeErr");
    }
#endif /*HAS_DS_TWR*/
    DecaDriverInstance.rx_time_stamp.prev = DecaDriverInstance.rx_time_stamp.cur;
}

/*!
 * @fn tx_conf_callback()
 * @brief Callback to process TX confirmation events
 * @param  cb_data  callback data
 * @return  none
 */
void tx_conf_callback(const dwt_cb_data_t* cb_data) {
    LOG_DEBUG(DECA, "TxConfirmCallBack");
    DecaDriverInstance.tx_cnt++;
    dwt_forcetrxoff();
    decadriver_set_rx();
    dwt_readtxtimestamp((uint8*)&DecaDriverInstance.tx_time_stamp.cur);
    LOG_PROTECTED(DECA, "SpotTxTime %llu", DecaDriverInstance.tx_time_stamp.cur);
#ifdef HAS_DS_TWR
    bool res = false;
    res = ds_twr_proc_tx_time(&DsTwrItem, DecaDriverInstance.tx_time_stamp.cur);
    if(false == res) {
        LOG_PROTECTED(DECA, "ProcTxTimeErr");
    }
#endif /*HAS_DS_TWR*/
    DecaDriverInstance.tx_time_stamp.prev = DecaDriverInstance.tx_time_stamp.cur;
    DecaDriverInstance.tx_it = true;
}

/*!
 * @fn rx_to_callback()
 * @brief Callback to process RX timeout events
 * @param  cb_data  callback data
 * @return  none
 */
void rx_to_callback(const dwt_cb_data_t* cb_data) {
    LOG_DEBUG(DECA, "RxTimeOutCallBack");
    DecaDriverInstance.rx_time_out_cnt++;
    dwt_forcetrxoff();
    decadriver_set_rx();
}

/*!
 * @fn rx_err_callback()
 * @brief Callback to process RX error events
 * @param  cb_data  callback data
 * @return  none
 */
void rx_err_callback(const dwt_cb_data_t* cb_data) {
    LOG_DEBUG(DECA, "RxErrCallBack");
    DecaDriverInstance.err_cnt++;
    dwt_forcetrxoff();
    decadriver_set_rx();
}
