
#include "tbfp_retx_diag.h"

#include <string.h>
#include <inttypes.h>

#include "tbfp_re_tx_ack_fsm_types.h"

const char* tbfp_retx_in2str(TbfpReTxInput_t in){
    const char *name="?";
    switch(in) {
        case TBFP_IN_NONE :  name="None";break;
        case TBFP_IN_RX_ACK_TIME_OUT :name="RxAckTineOut";break;
        case TBFP_IN_TX_DONE_TIME_OUT:name="TxDoneTimeOut";break;
        case TBFP_IN_TX_FRAME:name="TxFrame"; break;
        case TBFP_IN_TX_DONE: name="TxDone"; break;
        case TBFP_IN_RX_ACK: name="RxAck";break;
        default: break;
    }
    return name;
}

const char* tbfp_retx_state2str(TbfpReTxState_t state){
    const char *name="?";
    switch(state) {
        case TBFP_IDLE :  name="Idle";break;
        case TBFP_WAIT_TX_DONE: name="WaitTx";break;
        case TBFP_WAIT_ACK :name="WaitAck";break;
        default: break;
    }
    return name;
}

bool tbfp_diag_retx(void) {
    bool res = false;
    uint32_t i;
    static const table_col_t cols[] = {
        {8, "if"}, {9, "SpinCnt"}, {9, "State"},  {9, "LackTxDone"}, {9, "AckRx"},
        {9, "AckTx"},
#if HAS_TBFP_RETRANSMIT
        {9, "ReTx"},
#endif
        {9, "NoRepl"}, {7, "Err"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t tbfp_cnt = tbfp_get_cnt();
    for(i = 0; i < tbfp_cnt; i++) {
        TbfpHandle_t* TbfpNode = TbfpGetNode(i);
        if(TbfpNode) {
            cli_printf(TSEP);
            cli_printf(" %6s " TSEP, InterfaceToStr(TbfpNode->interface));
            cli_printf(" %7u " TSEP, TbfpNode->ReTxFsm.spin_cnt);
#if HAS_TBFP_RETRANSMIT
            cli_printf(" %7s " TSEP, tbfp_retx_state2str(TbfpNode->ReTxFsm.state));
#endif
            cli_printf(" %7u " TSEP, TbfpNode->ReTxFsm.err_tx_done);
            cli_printf(" %7u " TSEP, TbfpNode->ReTxFsm.ack_rx_cnt);
            cli_printf(" %7u " TSEP, TbfpNode->ReTxFsm.ack_tx_cnt);
            cli_printf(" %7u " TSEP, TbfpNode->ReTxFsm.retx_cnt);
            cli_printf(" %7u " TSEP, TbfpNode->ReTxFsm.no_reply_cnt);
            cli_printf(" %5u " TSEP, TbfpNode->ReTxFsm.err_cnt);
            cli_printf(CRLF);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
