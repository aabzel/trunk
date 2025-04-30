#include "ds_twr.h"

#include <float.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "array.h"
#include "data_utils.h"
#include "ds_twr_initiator.h"
#include "ds_twr_responder.h"
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

static bool ds_twr_show_state(DsTwr_t* const Node) {
    bool res = false;
    if(Node->prev_state != Node->state) {
        LOG_DEBUG(DS_TWR, "State %s->%s", DsTwrState2Str(Node->prev_state), DsTwrState2Str(Node->state));
        res = true;
    }

    return res;
}

bool ds_twr_proc_timeout(DsTwr_t* const Node) {
    bool res = true;
    if(DS_TWR_IDLE != Node->state) {
        // cli_printf(CRLF);
        LOG_DEBUG(DS_TWR, "State %s Input %s", DsTwrState2Str(Node->state), DsTwrInput2Str(Node->cur_input));
    }
    Node->start_ms = time_get_ms32();

    res = ds_twr_reset(Node);
#ifdef HAS_DECADRIVER
    res = decadriver_init();
    // set_log_level(DECA, LOG_LEVEL_ERROR);
#endif /*HAS_DECADRIVER*/
    return res;
}

bool ds_twr_proc_error_input(DsTwr_t* const Node) {
    bool res = false;
    // cli_printf(CRLF);
    LOG_ERROR(DS_TWR, "State %s Input %s", DsTwrState2Str(Node->state), DsTwrInput2Str(Node->cur_input));
#ifdef HAS_DECADRIVER
    res = decadriver_init();
#endif /*HAS_DECADRIVER*/
    Node->err_cnt++;
    Node->state = DS_TWR_IDLE;
    Node->start_ms = time_get_ms32();

    return res;
}

bool ds_twr_proc_rx_time(DsTwr_t* const Node, uint64_t rx_stamp) {
    bool res = false;
    if(rx_stamp) {
        LOG_PROTECTED(DS_TWR, "SpotRxTime %llu State %s", rx_stamp, DsTwrState2Str(Node->state));
        Node->rx_stamp = rx_stamp;
        res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_RX_TIME_STAMP);
    } else {
        LOG_ERROR(DS_TWR, "InvalidRxTime %llu", rx_stamp);
    }
    return res;
}

bool ds_twr_proc_tx_time(DsTwr_t* const Node, uint64_t tx_stamp) {
    bool res = false;
    if(Node) {
        LOG_PROTECTED(DS_TWR, "SpotTxTime %llu State %s", tx_stamp, DsTwrState2Str(Node->state));
        Node->tx_stamp = tx_stamp;
        res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_TX_TIME_STAMP);
    } else {
        LOG_ERROR(DS_TWR, "TxTimeErr %llu", tx_stamp);
    }
    return res;
}

bool ds_twr_proc_idle(DsTwr_t* const Node, uint32_t up_time_ms) {
    bool res = false;
    if(Node) {
        uint32_t diff_ms = up_time_ms - Node->start_ms;
        LOG_PARN(DS_TWR, "Proc Idle Dur %10u", diff_ms);
        Node->resp_poll_send = false;

        switch((uint8_t)Node->cur_input) {
        case DS_TWR_INPUT_START: {
            LOG_DEBUG(DS_TWR, "ProcStartInIdle N:%u", Node->iter_cnt);
            res = ds_twr_start_ll(Node);
            if(res) {
                Node->iter_cnt++;
            } else {
                // ds_twr_start(Node);
            }
        } break;

        case DS_TWR_INPUT_TX_TIME_STAMP:
            LOG_DEBUG(DS_TWR, "%s Proc TxTime %llu", DsTwrState2Str(Node->state), Node->tx_stamp);
            res = true;
            break;
        case DS_TWR_INPUT_NONE:
            res = true;
            break;

        case DS_TWR_INPUT_RX_POLL: {
        	res = ds_twr_proc_rx_poll(Node);

        } break;

        case DS_TWR_INPUT_RX_TIME_STAMP:
        	res = ds_twr_proc_idle_rx_time(Node);
            break;

        case DS_TWR_INPUT_RX_PESPONDER_TIMINGS:
            // case DS_TWR_INPUT_RX_RESPONSE_WITH_INITIATOR_T_LOOP:
        case DS_TWR_INPUT_RX_PESPONSE_POLL:
        case DS_TWR_INPUT_RX_RESPONSE: {
            res = ds_twr_proc_error_input(Node);
        } break;

        case DS_TWR_INPUT_TIME_OUT:
            res = ds_twr_proc_timeout(Node);
            break;

        default:
            res = false;
            break;
        }

        if(Node->continuous) {
            res = ds_twr_start(Node);
        }

        if(DS_TWR_TIME_OUT < diff_ms) {
            Node->start_ms = time_get_ms32();
            res = fifo_push(&Node->InputFifo, DS_TWR_INPUT_TIME_OUT);
        }
    }
    return res;
}

static bool ds_twr_show_input(DsTwr_t* const Node) {
    bool res = false;
    switch((uint8_t)Node->cur_input) {
    case DS_TWR_INPUT_NONE:
        res = false;
        break;
    case DS_TWR_INPUT_TIME_OUT:
        res = false;
        break;
    default:
        LOG_DEBUG(DS_TWR, "NewInput %s State %s", DsTwrInput2Str(Node->cur_input), DsTwrState2Str(Node->state));
        res = true;
        break;
    }
    return res;
}


bool ds_twr_proc_one(DsTwr_t* const Node) {
    bool res = false;
    if(Node) {
        Node->proc_cnt++;
        Node->prev_state = Node->state;

        char input = DS_TWR_INPUT_NONE;
        Node->cur_input = DS_TWR_INPUT_NONE;
        res = fifo_pull(&Node->InputFifo, &input);
        if(res) {
            LOG_DEBUG(DS_TWR, "SpotInput in FiFo %s", DsTwrInput2Str(input));
            Node->cur_input = input;
        } else {
            Node->cur_input = DS_TWR_INPUT_NONE;
        }
        ds_twr_show_input(Node);

        uint32_t up_time_ms = time_get_ms32();
        LOG_PARN(DS_TWR, "Proc State:%s Time %10u", DsTwrState2Str(Node->state), up_time_ms);

        switch((uint8_t)Node->state) {
        case DS_TWR_IDLE:
            res = ds_twr_proc_idle(Node, up_time_ms);
            break;
        case DS_TWR_INITIATOR_LOOP:
            res = ds_twr_proc_initiator_loop(Node, up_time_ms);
            break;
        case DS_TWR_INITIATOR_DELAY:
            res = ds_twr_proc_initiator_delay(Node, up_time_ms);
            break;
        case DS_TWR_INITIATOR_WAIT_TIMING:
            res = ds_twr_proc_wait_timings(Node, up_time_ms);
            break;
        case DS_TWR_RESPONDER_DELAY:
            res = ds_twr_proc_responder_delay(Node, up_time_ms);
            break;
        case DS_TWR_RESPONDER_LOOP:
            res = ds_twr_proc_responder_loop(Node, up_time_ms);
            break;
        case DS_TWR_DONE:
            res = ds_twr_proc_done(Node, up_time_ms);
            break;
        default:
            res = false;
            break;
        }
        ds_twr_show_state(Node);
        Node->prev_input = Node->cur_input;
    }
    return res;
}

bool ds_twr_reset(DsTwr_t* const Node) {
    bool res = false;
    LOG_DEBUG(DS_TWR, "Reset");
    if(Node) {
        Node->tx_stamp = 0;
        Node->rx_stamp = 0;

        LOG_DEBUG(DS_TWR, "TimerClock %llu Hz", Node->timer_clock);
        Node->resp_poll_send = false;
        Node->cur_input = DS_TWR_INPUT_NONE;
        Node->prev_input = DS_TWR_INPUT_NONE;

        Node->state = DS_TWR_IDLE;
        // Node->final.tof = 0;
        // Node->final.tof_s = 0.0;

        Node->initiator.t_loop = 0;
        Node->initiator.t_delay = 0;
        Node->initiator.rx_stamp = 0;
        Node->initiator.tx_stamp = 0;

        Node->responder.t_loop = 0;
        Node->responder.t_delay = 0;
        Node->responder.rx_stamp = 0;
        Node->responder.tx_stamp = 0;

        res = fifo_init(&Node->InputFifo, Node->InFifoHeap, sizeof(Node->InFifoHeap));

        Node->poll_arrived = false;
        Node->share_timing = false;
        Node->respond_arrive = false;
        Node->respond_sent = false;

        Node->start_ms = time_get_ms32();
    }
    return res;
}

bool ds_twr_proc(void) {
    bool res = false;
    res = ds_twr_proc_one(&DsTwrItem);
    return res;
}

bool ds_twr_init_one(const DsTwrConfig_t* const Config, DsTwr_t* const Node) {
    bool res = false;
    LOG_WARNING(DS_TWR, "Init");
    set_log_level(DS_TWR, LOG_LEVEL_NOTICE);
    if(Node) {
        if(Config) {
            DsTwdDiagConfig(Config);
            Node->timer_clock = Config->timer_clock;
            Node->decawave_num = Config->decawave_num;
            // Node->ant_delay_m = Config->ant_delay_m;
            Node->interface = Config->interface;
            Node->known_nodes_cnt = Config->known_nodes_cnt;
        }
        res = ds_twr_init_distances(Config, Node);
        res = ds_twr_reset(Node);
        res = double_val_reset(&Node->offset_m);
        Node->resp_poll_send = false;
        Node->offset_m.max = 0.0;
        Node->init = true;
        Node->spin_cnt = 0;
        Node->cur_id_index = 0;
    }
    return res;
}

bool ds_twr_init(void) {
    bool res = false;
    set_log_level(DS_TWR, LOG_LEVEL_DEBUG);
    res = ds_twr_init_one(&DsTwrConfig, &DsTwrItem);
    set_log_level(DS_TWR, LOG_LEVEL_NOTICE);
    return res;
}
