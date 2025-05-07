#include "tbfp_re_tx_ack_fsm.h"

#include <string.h>

#include "data_utils.h"
#include "log.h"
#include "tbfp_protocol.h"
#include "tbfp_retx_diag.h"
#include "time_mcal.h"
#ifdef HAS_SX1262
#include "sx1262_constants.h"
#include "sx1262_drv.h"
#endif /*HAS_SX1262*/

#include "system.h"
#include "system_diag.h"

bool is_tbfp_retx_idle(TbfpHandle_t* Node) {
    bool res = false;
    if((TBFP_IDLE == Node->ReTxFsm.state) && (0 == Node->ReTxFsm.retx_cnt)) {
        res = true;
    }
    return res;
}

#define TX_DONE_EXTRA_TIME_MS 10
bool tbfp_retx_start(TbfpHandle_t* Node, uint8_t* array, uint32_t len) {
    bool res = false;
    if(Node && array && (0 < len)) {
        memcpy(Node->tx_frame, array, len);
        Node->tx_frame_len = len;
#ifdef HAS_SX1262
        if(IF_SX1262 == Node->interface) {
            double t_frame = sx1262_calc_tx_time(&Sx1262Instance);
            Node->ReTxFsm.tx_done_time_out_ms = (uint32_t)(t_frame * 1000.0) + TX_DONE_EXTRA_TIME_MS;
            LOG_DEBUG(RETX, "ExpectTxDoneTimeOut: %u ms", (uint32_t)(t_frame * 1000.0));
            Node->ReTxFsm.retx_cnt = TBFP_RETX_TRY_MAX;
            res = sx1262_start_tx(Node->tx_frame, Node->tx_frame_len, TX_SINGLE_MODE);
            if(res) {
                Node->ReTxFsm.time_stamp_start_ms = get_time_ms32();
                ;
                Node->ReTxFsm.state = TBFP_WAIT_TX_DONE;
                LOG_DEBUG(RETX, "%s Send Try:%u", InterfaceToStr(Node->interface),
                          TBFP_RETX_TRY_MAX - Node->ReTxFsm.retx_cnt + 1);
                Node->ReTxFsm.retx_cnt--;
            } else {
                LOG_ERROR(SX1262, "StartTxErr");
                Node->ReTxFsm.state = TBFP_IDLE;
            }
        } else {
            LOG_ERROR(RETX, "ReTxOnlyForSX1262_If");
        }
#endif
    }
    return res;
}

bool tbfp_retx_init(TbfpHandle_t* Node) {
    bool res = false;
    LOG_INFO(TBFP, "ReTxInit");
    if(Node) {
        memset(&(Node->ReTxFsm), 0, sizeof(TbfpReTxFsm_t));
        Node->ReTxFsm.state = TBFP_IDLE;
        Node->ReTxFsm.retx_cnt = 0;
        Node->ReTxFsm.ack_time_out_cnt = 0;
        res = true;
    }
    return res;
}

static bool tbfp_proc_retx_wait_tx_done(TbfpHandle_t* Node, uint32_t time_stamp_cur) {
    bool res = false;
    uint32_t time_stamp_diff = 0;
    time_stamp_diff = time_stamp_cur - Node->ReTxFsm.time_stamp_start_ms;

    switch(Node->ReTxFsm.input) {
    case TBFP_IN_TX_DONE:
        LOG_DEBUG(RETX, "%s TxDoneOk after %u ms", InterfaceToStr(Node->interface), time_stamp_diff);
        Node->ReTxFsm.state = TBFP_WAIT_ACK;
        Node->ReTxFsm.time_stamp_start_ms = time_stamp_cur;
        time_stamp_diff = 0;
        res = true;
        break;
    case TBFP_IN_TX_DONE_TIME_OUT:
        Node->ReTxFsm.state = TBFP_IDLE;
        Node->ReTxFsm.err_cnt++;
        Node->ReTxFsm.err_tx_done++;
        Node->ReTxFsm.time_stamp_start_ms = time_stamp_cur;
        LOG_ERROR(RETX, "%s LackTxDone after %u ms", InterfaceToStr(Node->interface), time_stamp_diff);
        time_stamp_diff = 0;
        break;
    case TBFP_IN_TX_FRAME:
    case TBFP_IN_RX_ACK:
    case TBFP_IN_NONE:
    case TBFP_IN_RX_ACK_TIME_OUT:
        res = false;
        break;
    default:
        res = false;
        break;
    }

    if(Node->ReTxFsm.tx_done_time_out_ms < time_stamp_diff) {
        Node->ReTxFsm.input = TBFP_IN_TX_DONE_TIME_OUT;
        LOG_DEBUG(RETX, "%s State:%s InPut:%s", InterfaceToStr(Node->interface),
                  tbfp_retx_state2str(Node->ReTxFsm.state), tbfp_retx_in2str(Node->ReTxFsm.input));
        res = true;
    }
    return res;
}

static bool tbfp_proc_retx_wait_ack(TbfpHandle_t* Node, uint32_t time_stamp_cur) {
    bool res = false;
    uint32_t time_stamp_diff = 0;
    time_stamp_diff = time_stamp_cur - Node->ReTxFsm.time_stamp_start_ms;

    switch(Node->ReTxFsm.input) {
    case TBFP_IN_RX_ACK:
        Node->ReTxFsm.state = TBFP_IDLE;
        Node->ReTxFsm.time_stamp_start_ms = get_time_ms32();
        Node->ReTxFsm.spin_cnt++;
        Node->ReTxFsm.ack_rx_cnt++;
        LOG_DEBUG(RETX, "%s AckOk After %u try", InterfaceToStr(Node->interface),
                  TBFP_RETX_TRY_MAX - Node->ReTxFsm.retx_cnt);
        Node->ReTxFsm.retx_cnt = 0;
        time_stamp_diff = 0;
        res = true;
        break;
    case TBFP_IN_RX_ACK_TIME_OUT:
        Node->ReTxFsm.state = TBFP_IDLE;
        Node->ReTxFsm.ack_time_out_cnt++;
        Node->ReTxFsm.time_stamp_start_ms = get_time_ms32();
        if(0 == Node->ReTxFsm.retx_cnt) {
            Node->ReTxFsm.silence_cnt++;
            LOG_DEBUG(RETX, "%s LackAck %u ms Adter %u try", InterfaceToStr(Node->interface), time_stamp_diff,
                      TBFP_RETX_TRY_MAX);
            Node->ReTxFsm.no_reply_cnt++;
        } else {
            LOG_DEBUG(RETX, "%s LackAck %u ms", InterfaceToStr(Node->interface), time_stamp_diff);
        }
        time_stamp_diff = 0;
        res = true;
        break;
    case TBFP_IN_NONE:
    case TBFP_IN_TX_DONE_TIME_OUT:
    case TBFP_IN_TX_FRAME:
    case TBFP_IN_TX_DONE:
        res = true;
        break;
    default:
        res = false;
        break;
    }

    if((Node->ReTxFsm.tx_done_time_out_ms + TX_DONE_EXTRA_TIME_MS) < time_stamp_diff) {
        Node->ReTxFsm.input = TBFP_IN_RX_ACK_TIME_OUT;
        LOG_DEBUG(RETX, "%s State:%s InPut:%s", InterfaceToStr(Node->interface),
                  tbfp_retx_state2str(Node->ReTxFsm.state), tbfp_retx_in2str(Node->ReTxFsm.input));
    }
    return res;
}

static bool tbfp_proc_retx_idle(TbfpHandle_t* Node) {
    bool res = false;
    if(0 < Node->ReTxFsm.retx_cnt) {
#ifdef HAS_SX1262
        if(IF_SX1262 == Node->interface) {
            LOG_DEBUG(RETX, "ExpectTxDoneTimeOut: %u ms",
                      Node->ReTxFsm.tx_done_time_out_ms - TX_DONE_EXTRA_TIME_MS);

            res = sx1262_start_tx(Node->tx_frame, Node->tx_frame_len, TX_SINGLE_MODE);
            if(res) {
                Node->ReTxFsm.time_stamp_start_ms = get_time_ms32();
                LOG_DEBUG(RETX, "%s Send Try:%u", InterfaceToStr(Node->interface),
                          TBFP_RETX_TRY_MAX - Node->ReTxFsm.retx_cnt + 1);
                Node->ReTxFsm.retx_cnt--;
                Node->ReTxFsm.state = TBFP_WAIT_TX_DONE;
            } else {
                Node->ReTxFsm.state = TBFP_IDLE;
            }
        } else {
            LOG_ERROR(RETX, "ReTxOnlyForSX1262_If");
        }
#endif
    }
    return res;
}

static bool tbfp_proc_retx_one(TbfpHandle_t* Node) {
    bool res = false;
    uint32_t time_stamp = get_time_ms32();
    if(Node) {
        switch(Node->ReTxFsm.state) {
        case TBFP_IDLE:
            res = tbfp_proc_retx_idle(Node);
            break;
        case TBFP_WAIT_TX_DONE:
            res = tbfp_proc_retx_wait_tx_done(Node, time_stamp);
            break;
        case TBFP_WAIT_ACK:
            res = tbfp_proc_retx_wait_ack(Node, time_stamp);
            break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

bool tbfp_retx_proc(void) {
    bool res = false;
    bool out_res = true;
    uint8_t i = 0;
    for(i = 0; i < ARRAY_SIZE(TbfpProtocol); i++) {
        res = tbfp_proc_retx_one(&TbfpProtocol[i]);
        if(false == res) {
            out_res = false;
        }
    }
    return out_res;
}

bool tbfp_retx_ack(TbfpHandle_t* Node, uint16_t ser_num) {
    bool res = false;
    if(Node) {
        if(Node->ReTxFsm.expected_ser_num != ser_num) {
            LOG_WARNING(RETX, "%s ExpAckSn:%u RxAckSn:%u", InterfaceToStr(Node->interface),
                        Node->ReTxFsm.expected_ser_num, ser_num);
        } else {
            LOG_DEBUG(RETX, "%s RxAckSn:%u", InterfaceToStr(Node->interface), ser_num);
        }
        Node->ReTxFsm.input = TBFP_IN_RX_ACK;
        LOG_DEBUG(RETX, "%s State:%s InPut:%s", InterfaceToStr(Node->interface),
                  tbfp_retx_state2str(Node->ReTxFsm.state), tbfp_retx_in2str(Node->ReTxFsm.input));
        res = true;
    }
    return res;
}

bool tbfp_retx_tx_done(Interfaces_t interface) {
    bool res = false;
    LOG_DEBUG(RETX, "%s TxDone", InterfaceToStr(interface));
    uint8_t i = 0;
    for(i = 0; i < ARRAY_SIZE(TbfpProtocol); i++) {
        if(TbfpProtocol[i].interface == interface) {
            TbfpProtocol[i].ReTxFsm.input = TBFP_IN_TX_DONE;
            LOG_DEBUG(RETX, "%s State:%s InPut:%s", InterfaceToStr(interface),
                      tbfp_retx_state2str(TbfpProtocol[i].ReTxFsm.state),
                      tbfp_retx_in2str(TbfpProtocol[i].ReTxFsm.input));
            res = true;
        }
    }

    return res;
}
