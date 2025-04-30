#include "ds_twr_initiator.h"

#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "ds_twr.h"
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

bool ds_twr_send_poll(DsTwr_t* const Node) {
    bool res = false;
    if(Node) {
        res = true;

#ifdef HAS_DECAWAVE
        Node->cur_id_index = array_index_next(Node->cur_id_index, Node->known_nodes_cnt);
        res = decawave_send_poll(1, &Node->IdInfo[Node->cur_id_index]);
        if(res) {
            LOG_DEBUG(DS_TWR, "TxPoll 0x%04x Ok", Node->IdInfo[Node->cur_id_index].id);
            res = true;
        } else {
            LOG_ERROR(DS_TWR, "TxPollErr");
            res = false;
        }
#endif
    } else {
        LOG_ERROR(DS_TWR, "NodeErr");
        res = false;
    }
    return res;
}







bool ds_twr_start_ll(DsTwr_t* const Node) {
    bool res = false;
    LOG_DEBUG(DS_TWR, "StartRange");
    if(Node) {
        ds_twr_reset(Node);
        res = ds_twr_send_poll(Node);
        if(res) {
            Node->state = DS_TWR_INITIATOR_LOOP;
            Node->start_ms = time_get_ms32();
        } else {
            LOG_ERROR(DS_TWR, "StartSendPollErr");
            res = false;
        }
    }
    return res;
}

bool ds_twr_start(DsTwr_t* const Node) {
    bool res = false;
    LOG_DEBUG(DS_TWR, "Start");
    if(Node) {
        res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_START);
    }
    return res;
}


static bool ds_twr_calc_initiator_t_loop(DsTwr_t* const Node) {
    bool res = false;
    if(Node) {

        if(Node->initiator.tx_stamp) {
            if(Node->initiator.rx_stamp) {
                if(Node->initiator.tx_stamp < Node->initiator.rx_stamp) {
                    Node->initiator.t_loop = Node->initiator.rx_stamp - Node->initiator.tx_stamp;
#ifdef HAS_DECAWAVE
                    DecaWaveHandle_t* DecaNode = DecaWaveGetNode(Node->decawave_num);
                    if(DecaNode) {
                        DecaNode->initiator.t_loop = Node->initiator.t_loop;
                    }
#endif

                    Node->initiator.t_loop_s = TIMER_2_SECONDS(Node->initiator.t_loop, Node->timer_clock);
                    char text[80] = "";
                    double t_loop_ns = SEC_2_NSEC(Node->initiator.t_loop_s);
                    sprintf(text, "Initiator Tloop %f ns", t_loop_ns);
                    LOG_DEBUG(DS_TWR, "%s", text);
                    LOG_DEBUG(DS_TWR, "Initiator Tloop %llu tick", Node->initiator.t_loop);
                    LOG_DEBUG(DS_TWR, "Initiator Tloop %llu-%llu=%llu ", Node->initiator.rx_stamp,
                              Node->initiator.tx_stamp, Node->initiator.t_loop);
                    res = true;
                } else {
                    LOG_ERROR(DS_TWR, "Time Stamp Invalid Rx%llu Tx:%llu", Node->initiator.rx_stamp,
                              Node->initiator.tx_stamp);
                }
            } else {
                LOG_ERROR(DS_TWR, "InitiatorInvalidRxTime");
            }
        } else {
            LOG_ERROR(DS_TWR, "InitiatorInvalidTxTime %llu", Node->initiator.tx_stamp);
        }
    }
    return res;
}

/*2*/
bool ds_twr_proc_initiator_loop(DsTwr_t* const Node, uint32_t up_time_ms) {
    bool res = false;
    uint32_t diff_ms = up_time_ms - Node->start_ms;
    LOG_PARN(DS_TWR, "ProcInitiatorLoop");
    switch((uint8_t)Node->cur_input) {

    /*That is TxDone from Poll sending*/
    case DS_TWR_INPUT_TX_TIME_STAMP:
        LOG_DEBUG(DS_TWR, "Proc TxTime %llu in %s", Node->tx_stamp, DsTwrState2Str(Node->state));
        Node->initiator.tx_stamp = Node->tx_stamp;
        Node->start_ms = time_get_ms32();
        break;

    case DS_TWR_INPUT_RX_PESPONSE_POLL:
        LOG_DEBUG(DS_TWR, "SpotResp+Poll");
        Node->start_ms = time_get_ms32();
        Node->poll_arrived = true;
        if(Node->initiator.t_loop) {
            // res = ds_twr_initiator_responce_send(Node);
            // if(res) {
            //    Node->state = DS_TWR_INITIATOR_DELAY;
            //    Node->start_ms = time_get_ms32();
            // Node->state = DS_TWR_INITIATOR_WAIT_TIMING;
            //}
        } else {
            LOG_DEBUG(DS_TWR, "WaitRxTimeStamp");
        }
        break;

    /*RxTime arrive after data fetching*/
    case DS_TWR_INPUT_RX_TIME_STAMP: {
        LOG_DEBUG(DS_TWR, "Proc RxTime %llu in %s", Node->rx_stamp, DsTwrState2Str(Node->state));
        /*It may be phantom frame*/
        Node->initiator.rx_stamp = Node->rx_stamp;
        res = ds_twr_calc_initiator_t_loop(Node);
        if(Node->poll_arrived) {
            Node->poll_arrived = false;
            Node->state = DS_TWR_INITIATOR_DELAY;
            Node->start_ms = time_get_ms32();
        } else {
            LOG_ERROR(DS_TWR, "UndefRxInInitiatorLoop");
        }
        // res = ds_twr_initiator_responce_send(Node);
        // Node->state = DS_TWR_INITIATOR_DELAY;
    } break;

    case DS_TWR_INPUT_RX_RESPONSE:
    case DS_TWR_INPUT_RX_PESPONDER_TIMINGS:
    case DS_TWR_INPUT_RX_POLL:
        //  case DS_TWR_INPUT_RX_RESPONSE_WITH_INITIATOR_T_LOOP:
        res = ds_twr_proc_error_input(Node);
        break;

    case DS_TWR_INPUT_TIME_OUT:
        res = ds_twr_proc_timeout(Node);
        break;
    case DS_TWR_INPUT_START:
    case DS_TWR_INPUT_NONE:
        res = true;
        break;
    }

    if(DS_TWR_TIME_OUT < diff_ms) {
        Node->err_cnt++;
        LOG_ERROR(DS_TWR, "InitiatorLoopNoResponce From [%u]=ID:0x%x,%s",
                Node->cur_id_index,
                  Node->IdInfo[Node->cur_id_index].id,
                  DsTwrDiagNode2Str(Node));
        Node->start_ms = time_get_ms32();
        res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_TIME_OUT);
    }
    return res;
}

static bool ds_twr_calc_initiator_delay(DsTwr_t* const Node) {
    bool res = false;
    if(Node->initiator.rx_stamp) {
        if(Node->initiator.tx_stamp) {
            if(Node->initiator.rx_stamp < Node->initiator.tx_stamp) {
                Node->initiator.t_delay = Node->initiator.tx_stamp - Node->initiator.rx_stamp;
#ifdef HAS_DECAWAVE
                DecaWaveHandle_t* DecaNode = DecaWaveGetNode(Node->decawave_num);
                if(DecaNode) {
                    DecaNode->initiator.t_delay = Node->initiator.t_delay;
                }
#endif
                LOG_DEBUG(DS_TWR, "InitiatorTdelay %llu tick", Node->initiator.t_delay);
                Node->initiator.t_delay_s = TIMER_2_SECONDS(Node->initiator.t_delay, Node->timer_clock);
                LOG_DEBUG(DS_TWR, "InitiatorTdelay %f s", Node->initiator.t_delay_s);
                LOG_DEBUG(DS_TWR, "InitiatorTdelay %llu-%llu=%llu", Node->initiator.tx_stamp, Node->initiator.rx_stamp,
                          Node->initiator.t_delay);
                res = true;
            } else {
                LOG_ERROR(DS_TWR, "InitiatorTdelayErr");
            }
        } else {
            LOG_ERROR(DS_TWR, "InvalidTxTime");
        }
    } else {
        LOG_ERROR(DS_TWR, "InvalidRxTime");
    }
    return res;
}

bool ds_twr_proc_initiator_delay(DsTwr_t* const Node, uint32_t up_time_ms) {
    bool res = false;
    uint32_t diff_ms = up_time_ms - Node->start_ms;

    Node->initiator.rx_stamp = Node->rx_stamp;
    res = ds_twr_calc_initiator_t_loop(Node);
    res = true;
#ifdef HAS_DECAWAVE
    if(false == Node->respond_sent) {
        res = decawave_send_response_payload(1, Node->IdInfo[Node->cur_id_index].id, UWB_VAR_INITIATOR_T_LOOP,
                                             (uint8_t*)&Node->initiator.t_loop, 9);
        if(res) {
            LOG_DEBUG(DS_TWR, "SendResp+TloopOk");
            Node->respond_sent = true;
        } else {
            LOG_ERROR(DS_TWR, "SendResp+TloopErr");
        }
    }
#endif

    switch((uint8_t)Node->cur_input) {
    case DS_TWR_INPUT_START:
    case DS_TWR_INPUT_NONE:
        res = true;
        break;

    case DS_TWR_INPUT_TX_TIME_STAMP:
        LOG_DEBUG(DS_TWR, "Proc TxTime %llu in %s", Node->tx_stamp, DsTwrState2Str(Node->state));
        if(Node->respond_sent) {
            Node->initiator.tx_stamp = Node->tx_stamp;
            res = ds_twr_calc_initiator_delay(Node);
            Node->state = DS_TWR_INITIATOR_WAIT_TIMING;
            Node->start_ms = time_get_ms32();
        } else {
            LOG_ERROR(DS_TWR, "UndefTxEvent");
        }
        break;

    case DS_TWR_INPUT_RX_PESPONSE_POLL:
    case DS_TWR_INPUT_RX_TIME_STAMP:
    case DS_TWR_INPUT_RX_PESPONDER_TIMINGS:
    case DS_TWR_INPUT_RX_POLL:
    case DS_TWR_INPUT_RX_RESPONSE:
        //  case DS_TWR_INPUT_RX_RESPONSE_WITH_INITIATOR_T_LOOP:
        res = ds_twr_proc_error_input(Node);
        break;

    case DS_TWR_INPUT_TIME_OUT:
        res = ds_twr_proc_timeout(Node);
        break;
    }

    if(DS_TWR_TIME_OUT < diff_ms) {
        LOG_ERROR(DS_TWR, "InitiatorDelayNoResponceErr");
        Node->start_ms = time_get_ms32();
        res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_TIME_OUT);
    }
    return res;
}

static bool ds_twr_dist_get_lll(DsTwr_t* const Node) {
    bool res= false;
#ifdef HAS_DECAWAVE
    res= decawave_dist_get(  Node->decawave_num,
                             &Node->IdInfo[Node->cur_id_index].range_m.cur);
#endif
    if(res){
        Node->IdInfo[Node->cur_id_index].range_m.min = MIN(Node->IdInfo[Node->cur_id_index].range_m.min,
                Node->IdInfo[Node->cur_id_index].range_m.cur);
        Node->IdInfo[Node->cur_id_index].range_m.max = MAX(Node->IdInfo[Node->cur_id_index].range_m.max,
                Node->IdInfo[Node->cur_id_index].range_m.cur);
        Node->IdInfo[Node->cur_id_index].valid = res;
    }
    return res;
}

bool ds_twr_proc_wait_timings(DsTwr_t* const Node, uint32_t up_time_ms) {
    bool res = false;
    uint32_t diff_ms = up_time_ms - Node->start_ms;

    switch((uint8_t)Node->cur_input) {

    case DS_TWR_INPUT_RX_PESPONDER_TIMINGS:
        LOG_DEBUG(DS_TWR, "Got RX_PESPONDER_TIMINGS in %s", DsTwrState2Str(Node->state));
        Node->respond_arrive = true; /*TODO do not reuse variable*/
        break;

    case DS_TWR_INPUT_RX_TIME_STAMP:
        LOG_DEBUG(DS_TWR, "Proc RxTime %llu in %s", Node->rx_stamp, DsTwrState2Str(Node->state));
        if(Node->respond_arrive) {
            Node->respond_arrive = false;
            Node->spin_cnt++;

            LOG_DEBUG(DS_TWR, "ID 0x%x InitiatorSpin %u!", Node->IdInfo[Node->cur_id_index].id, Node->spin_cnt);
            Node->state = DS_TWR_IDLE;
            Node->start_ms = time_get_ms32();

            res = ds_twr_dist_get_lll(Node);
#ifdef HAS_DECAWAVE
            //res = decawave_dist_get(Node->decawave_num, &Node->IdInfo[Node->cur_id_index].range_m);
            //Node->IdInfo[Node->cur_id_index].valid = res;
#endif
            ds_twr_reset(Node);
        } else {
            LOG_ERROR(DS_TWR, "UndefRxInWaitTiming");
        }
        res = true;
        break;

    case DS_TWR_INPUT_START:
    case DS_TWR_INPUT_NONE:
        res = true;
        break;

    case DS_TWR_INPUT_TIME_OUT:
        res = ds_twr_proc_timeout(Node);
        break;

    case DS_TWR_INPUT_TX_TIME_STAMP:
        LOG_ERROR(DS_TWR, "UnderTxTime in %s", DsTwrState2Str(Node->state));
        res = ds_twr_proc_error_input(Node);
        break;
    case DS_TWR_INPUT_RX_POLL:
    case DS_TWR_INPUT_RX_RESPONSE:
    case DS_TWR_INPUT_RX_PESPONSE_POLL:
        res = ds_twr_proc_error_input(Node);
        break;

    default:
        break;
    }

    if(DS_TWR_TIME_OUT < diff_ms) {
        LOG_ERROR(DS_TWR, "InitiatorHangOnInWaitTimings From ID[%u]=0x%x, %s",
                Node->cur_id_index,
                Node->IdInfo[Node->cur_id_index].id,
                DsTwrDiagNode2Str(Node));
        Node->start_ms = time_get_ms32();
        res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_TIME_OUT);
    }
    return res;
}




bool ds_twr_init_distances(const DsTwrConfig_t* const Config, DsTwr_t* const Node) {
    bool res = false;
    uint8_t i = 0;
    uint8_t cnt = ARRAY_SIZE(Node->IdInfo);
    LOG_INFO(DS_TWR, "MaxIDtrack %u StaticNodeCnt: %u", cnt, Config->known_nodes_cnt);
    for(i = 0; i < cnt; i++) {
        res = true;
        Node->IdInfo[i].num = i + 1;

        double_val_reset(&Node->IdInfo[i].range_m);

        Node->IdInfo[i].valid = false;
        if(i < Config->known_nodes_cnt) {
            Node->IdInfo[i].id = Config->known_nodes[i];
            Node->IdInfo[i].status = ID_STATUS_STATIC;
        } else {
            Node->IdInfo[i].status = ID_STATUS_UNDEF;
            Node->IdInfo[i].id = 0;
        }
    }
    return res;
}



bool ds_twr_enable_continuous(DsTwr_t* const Node, bool on_off) {
    bool res = false;
    LOG_WARNING(DS_TWR, "Continuous %s", OnOff2Str(on_off));
    if(Node) {
        Node->continuous = on_off;
        res = true;
    }
    return res;
}


bool ds_twr_calibrate(DsTwr_t* const TwrNode, double real_dist_m) {
    bool res = false;
    LOG_INFO(DS_TWR, "Calibrate. RealDist %f m", real_dist_m);
    if(TwrNode) {
        res = ds_twr_start(TwrNode);
        res = wait_in_loop_ms(1000);
#ifdef HAS_DECAWAVE
        DecaWaveHandle_t* DecaNode = DecaWaveGetNode(1);
        if(DecaNode) {
            DecaNode->final.ant_delay_m = DecaNode->final.distance_m.cur - real_dist_m;
            DecaNode->phase1.ant_delay_m = DecaNode->phase1.distance_m.cur - real_dist_m;
            DecaNode->phase2.ant_delay_m = DecaNode->phase2.distance_m.cur - real_dist_m;
            LOG_INFO(DS_TWR, "AntDelay %f m %f m %f m", DecaNode->phase1.ant_delay_m, DecaNode->phase2.ant_delay_m,
                     DecaNode->final.ant_delay_m);
#ifdef HAS_PARAM
            res = param_set(PAR_ID_PHASE1_OFFSET, (uint8_t*)&DecaNode->phase1.ant_delay_m);
            res = param_set(PAR_ID_PHASE2_OFFSET, (uint8_t*)&DecaNode->phase2.ant_delay_m);
            res = param_set(PAR_ID_FINAL_OFFSET, (uint8_t*)&DecaNode->final.ant_delay_m);
#endif
        }
#endif
    }
    return res;
}
