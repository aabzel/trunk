#include "ds_twr_responder.h"

#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "data_utils.h"
#ifdef HAS_DECAWAVE
#include "decawave.h"
#endif

#ifdef HAS_DECADRIVER
#include "decadriver.h"
#endif
#include "ds_twr_dependencies.h"
#ifdef HAS_DS_TWR_DIAG
#include "ds_twr_diag.h"
#endif
#include "common_diag.h"
#include "ds_twr.h"
#include "ds_twr_types.h"
#include "fifo_char.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "physics_utils.h"

#include "time_mcal.h"
#include "utils_math.h"

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_TBFP
#include "tbfp_protocol.h"
#endif

#ifdef HAS_DEBUG
#include "debug_info.h"
#endif

bool ds_twr_proc_rx_poll(DsTwr_t* const Node){
    bool res = false;
    LOG_DEBUG(DS_TWR, "Proc RxPoll in %s", DsTwrState2Str(Node->state));
    Node->poll_arrived = true; /*TODO*/
    Node->event = DS_TWR_EVENT_RX_POLL;
    Node->iter_cnt++;
    if(Node->responder.rx_stamp) {
        res = true;
    }
    return res;
}

bool ds_twr_proc_idle_rx_time(DsTwr_t* const Node){
	bool res = false;
    LOG_DEBUG(DS_TWR, "ProcRxTime %llu in %s", Node->rx_stamp, DsTwrState2Str(Node->state));
    Node->responder.rx_stamp = Node->rx_stamp;
    if(Node->poll_arrived) {
        Node->poll_arrived = false;
        Node->start_ms = time_get_ms32();
        LOG_DEBUG(DS_TWR, "GoTo RESPONDER_DELAY");
        Node->state = DS_TWR_RESPONDER_DELAY;
        res = true;
    } else {
        LOG_DEBUG(DS_TWR, "UndefRxIn %s",DsTwrState2Str(Node->state));
        res = false;
    }
    return res;
}

static bool ds_twr_send_responce_poll(DsTwr_t* const Node) {
    bool res = false;
#ifdef HAS_DECAWAVE
    res = decawave_send_response_poll(1);
#else
    res = true;
#endif
    return res;
}

bool ds_twr_proc_responder_delay(DsTwr_t* const Node, uint32_t up_time_ms) {
    bool res = false;

    uint32_t diff_ms = up_time_ms - Node->start_ms;

    if(false == Node->resp_poll_send) {
        res = ds_twr_send_responce_poll(Node);
        if(res) {
            Node->resp_poll_send = true;
        }
    }

    switch((uint8_t)Node->cur_input) {
    case DS_TWR_INPUT_START:
    case DS_TWR_INPUT_NONE:
        res = true;
        break;

    case DS_TWR_INPUT_RX_POLL: {/*??*/
    	res=ds_twr_proc_rx_poll(Node);
    }break;

    case DS_TWR_INPUT_RX_TIME_STAMP:{
    	res = ds_twr_proc_idle_rx_time(Node);
    	if(false==res){
            res = ds_twr_proc_error_input(Node);
    	}
    }break;

    case DS_TWR_INPUT_RX_PESPONDER_TIMINGS:
    case DS_TWR_INPUT_RX_PESPONSE_POLL:
    case DS_TWR_INPUT_RX_RESPONSE:{
    	res = ds_twr_proc_error_input(Node);
    }break;

    case DS_TWR_INPUT_TIME_OUT:
        res = ds_twr_proc_timeout(Node);
        break;

    case DS_TWR_INPUT_TX_TIME_STAMP:
        LOG_DEBUG(DS_TWR, "Proc TxTime %llu in %s", Node->tx_stamp, DsTwrState2Str(Node->state));
        Node->responder.tx_stamp = Node->tx_stamp;

        if(Node->responder.rx_stamp < Node->responder.tx_stamp) {
            Node->responder.t_delay = Node->responder.tx_stamp - Node->responder.rx_stamp;
#ifdef HAS_DECAWAVE
            DecaWaveHandle_t* DecaNode = DecaWaveGetNode(1);
            if(DecaNode) {
                DecaNode->responder.t_delay = Node->responder.t_delay;
            }
#endif

            LOG_DEBUG(DS_TWR, "Responder Tdelay %llu-%llu=%llu=%f s", Node->responder.tx_stamp,
                      Node->responder.rx_stamp, Node->responder.t_delay,
                      TIMER_2_SECONDS(Node->responder.t_delay, Node->timer_clock));
            if(Node->resp_poll_send) {
                Node->state = DS_TWR_RESPONDER_LOOP;
                Node->start_ms = time_get_ms32();
                res = true;
            } else {
                Node->state = DS_TWR_IDLE;
                LOG_ERROR(DS_TWR, "TxTimeStampBeforeTxRespPoll");
                res = false;
            }
        } else {
            Node->state = DS_TWR_IDLE;
            res = false;
            LOG_ERROR(DS_TWR, "TimingErr Rx:%llu Tx:%llu", Node->responder.rx_stamp, Node->responder.tx_stamp);
        }
        break;
    default:
        break;
    }

    if(DS_TWR_TIME_OUT < diff_ms) {
        LOG_ERROR(DS_TWR, "ResponderDdelayHangOnErr");
        Node->start_ms = time_get_ms32();
        res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_TIME_OUT);
    }
    return res;
}

static bool ds_twr_share_timings(DsTwr_t* const Node) {
    bool res = false;
    LOG_DEBUG(DS_TWR, "ShareWimings:%s", DsTwrInput2Str(Node->cur_input));
    if(Node) {
        ResponderTiming_t ResponderTiming;
        memset(&ResponderTiming, 0, sizeof(ResponderTiming_t));
        ResponderTiming.t_delay = Node->responder.t_delay;
        ResponderTiming.t_loop = Node->responder.t_loop;
        LOG_DEBUG(DS_TWR, "ShareResponderTiming Tdelay:%llu Tloop:%llu", Node->responder.t_delay,
                  Node->responder.t_loop);
        if(0 < ResponderTiming.t_delay) {
            if(0 < ResponderTiming.t_loop) {
                res = true;
#ifdef HAS_DECAWAVE
                res = decawave_send_final(1, UWB_VAR_RESPONDER_TIMINGS, ResponderTiming.buff,
                                          sizeof(ResponderTiming_t) + 1);
                if(res) {
                    LOG_DEBUG(DS_TWR, "SendResponderTimingOk");
                } else {
                    LOG_ERROR(DS_TWR, "SendResponderTimingErr");
                    res = false;
                }
#endif
            } else {
                LOG_ERROR(DS_TWR, "InvalidResponderTloop %llu", ResponderTiming.t_loop);
                res = false;
            }
        } else {
            LOG_ERROR(DS_TWR, "InvalidResponderTdelay %llu", ResponderTiming.t_delay);
            res = false;
        }
    }
    return res;
}

bool ds_twr_proc_responder_loop(DsTwr_t* const Node, uint32_t up_time_ms) {
    bool res = false;
    uint32_t diff_ms = up_time_ms - Node->start_ms;

    switch((uint8_t) Node->cur_input) {

    case DS_TWR_INPUT_RX_TIME_STAMP:
        LOG_DEBUG(DS_TWR, "Proc RxTime %llu in %s", Node->rx_stamp, DsTwrState2Str(Node->state));
        if(Node->respond_arrive) {
            Node->respond_arrive = false;
            Node->responder.rx_stamp = Node->rx_stamp;
            if(Node->responder.tx_stamp < Node->responder.rx_stamp) {
                Node->responder.t_loop = Node->responder.rx_stamp - Node->responder.tx_stamp;
                /**/
#ifdef HAS_DECAWAVE
                DecaWaveHandle_t* DecaNode = DecaWaveGetNode(1);
                if(DecaNode) {
                    DecaNode->responder.t_loop = Node->responder.t_loop;
                }
#endif

                LOG_DEBUG(DS_TWR, "Responder Tloop %llu-%llu=%llu->%f s", Node->responder.rx_stamp,
                          Node->responder.tx_stamp, Node->responder.t_loop,
                          TIMER_2_SECONDS(Node->responder.t_loop, Node->timer_clock));
                res = true;
                Node->share_timing = false;
                Node->start_ms = time_get_ms32();
                Node->state = DS_TWR_DONE;
            } else {
                LOG_ERROR(DS_TWR, "ResponderTloopErr");
                res = false;
                Node->start_ms = time_get_ms32();
                Node->state = DS_TWR_IDLE;
            }
        } else {
        	res = ds_twr_proc_idle_rx_time(Node);
            LOG_ERROR(DS_TWR, "UndefRxInRespLoop");
            res = false;
        }
        break;

    case DS_TWR_INPUT_RX_RESPONSE:
        // case DS_TWR_INPUT_RX_RESPONSE_WITH_INITIATOR_T_LOOP:

        Node->respond_arrive = true;
        LOG_DEBUG(DS_TWR, "SetRespArriveFlag in %s", DsTwrState2Str(Node->state));
        // res = ds_twr_cacl_preliminary_dist(Node);
        break;
    case DS_TWR_INPUT_START:
    case DS_TWR_INPUT_NONE:
        res = true;
        break;

    case DS_TWR_INPUT_TX_TIME_STAMP:
    case DS_TWR_INPUT_RX_PESPONDER_TIMINGS:
    case DS_TWR_INPUT_RX_PESPONSE_POLL:
    case DS_TWR_INPUT_RX_POLL:
    	res = ds_twr_proc_rx_poll(Node);
        //res = ds_twr_proc_error_input(Node);
        break;

    case DS_TWR_INPUT_TIME_OUT:
        res = ds_twr_proc_timeout(Node);
        break;

    default:
        break;
    }

    if(DS_TWR_TIME_OUT < diff_ms) {
        LOG_ERROR(DS_TWR, "ResponderLoopHangOnErr %s",DsTwrDiagNode2Str(Node));
        Node->start_ms = time_get_ms32();
        res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_TIME_OUT);
    }
    return res;
}

bool ds_twr_proc_done(DsTwr_t* const Node, uint32_t up_time_ms) {
    bool res = false;
    uint32_t diff_ms = up_time_ms - Node->start_ms;
    LOG_PARN(DS_TWR, "ProcDone Input:%s", DsTwrInput2Str(Node->cur_input));
    if(false == Node->share_timing) {
        res = ds_twr_share_timings(Node);
        if(res) {
            Node->share_timing = true;
        }
    }

    switch((uint8_t)Node->cur_input) {
    case DS_TWR_INPUT_NONE:
    case DS_TWR_INPUT_START:
        res = true;
        break;

    case DS_TWR_INPUT_TX_TIME_STAMP:
        LOG_DEBUG(DS_TWR, "Proc TxTime %llu in %s", Node->tx_stamp, DsTwrState2Str(Node->state));
        Node->start_ms = time_get_ms32();
        if(Node->share_timing) {
            Node->spin_cnt++;
            Node->share_timing = false;
            LOG_DEBUG(DS_TWR, "NewRespDsTwrn %u!", Node->spin_cnt);
            Node->state = DS_TWR_IDLE;
        } else {
            LOG_ERROR(DS_TWR, "UndefTxInDone");
        }
        break;

    case DS_TWR_INPUT_TIME_OUT:
        res = ds_twr_proc_timeout(Node);
        break;

    case DS_TWR_INPUT_RX_POLL:{
    	res=ds_twr_proc_rx_poll(Node);
    } break;
        //  case DS_TWR_INPUT_RX_RESPONSE_WITH_INITIATOR_T_LOOP:
    case DS_TWR_INPUT_RX_TIME_STAMP: {
    	res=ds_twr_proc_idle_rx_time(Node);
    }break;
    case DS_TWR_INPUT_RX_PESPONDER_TIMINGS:
    case DS_TWR_INPUT_RX_PESPONSE_POLL:
    case DS_TWR_INPUT_RX_RESPONSE:
        res = ds_twr_proc_error_input(Node);
        break;
    default:
        break;
    }

    if(DS_TWR_TIME_OUT < diff_ms) {
        Node->start_ms = time_get_ms32();
        LOG_ERROR(DS_TWR, "HandOnDone");
        res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_TIME_OUT);
    }
    return res;
}




