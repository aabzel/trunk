#include "decawave.h"

#include <float.h>

#include "code_generator.h"
#include "debug_info.h"
#include "decawave_diag.h"
#include "decawave_types.h"
#ifdef HAS_DS_TWR
#include "ds_twr.h"
#endif
#include "log.h"
#include "physics_utils.h"
#include "protocol.h"

#ifdef HAS_FAT_FS
#include "fat_fs_drv.h"
#endif

#include "time_mcal.h"
#include "tbfp_protocol.h"
#include "utils_math.h"
#ifdef HAS_UWB
#include "uwb_if.h"
#endif

#ifdef HAS_FIR
#include "fir.h"
#endif

#ifdef HAS_DISTANCE
#include "distance_drv.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

bool decawave_dist_get_ll( DecaWaveHandle_t* const Node, double* const dist) {
    bool res = false;
    if(Node && dist) {
        if(Node->final.valid) {
            *dist = Node->final.distance_real_m;
            res = true;
            uint32_t cur_time_ms=time_get_ms32();
            uint32_t diff_ms = cur_time_ms-Node->final.update_time_stamp_ms;
            int32_t ttl_ms = ((int32_t)UWB_DIST_UPDATE_TIMEOUT_MS)-((int32_t)diff_ms);
            LOG_NOTICE(DECAWAVE, "RealDist:%f m, TTL %d ms", Node->final.distance_real_m,ttl_ms);
            if(UWB_DIST_UPDATE_TIMEOUT_MS < diff_ms ){
                Node->final.valid = false;
            }
        } else {
            LOG_DEBUG(DECAWAVE, "%u StillInvalidDist", Node->num);
            *dist = 99999.0;
        }
    }
    return res;
}


COMPONENT_GET_NODE(DecaWave, decawave)
#if 0
DecaWaveHandle_t* DecaWaveGetNode(uint8_t num) {
    DecaWaveHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = decawave_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == DecaWaveInstance[i].num) {
            if(DecaWaveInstance[i].valid) {
                Node = &DecaWaveInstance[i];
                break;
            }
        }
    }
    return Node;
}
#endif

COMPONENT_GET_CONFIG(DecaWave, decawave)
#if 0

const DecaWaveConfig_t* DecaWaveGetConfig(uint8_t num) {
    const DecaWaveConfig_t* Config = NULL;
    uint32_t i = 0;
    uint32_t cnt = decawave_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == DecaWaveConfig[i].num) {
            if(DecaWaveConfig[i].valid) {
                Config = &DecaWaveConfig[i];
                break;
            }
        }
    }
    return Config;
}
#endif

bool decawave_is_valid_message(uint8_t message) {
    bool res = false;
    switch(message) {
    case DECA_BLINK:
        res = true;
        break;
    case DECA_RANGING_INIT:
        res = true;
        break;
    case DECA_POLL:
        res = true;
        break;
    case DECA_RESP:
        res = true;
        break;
    case DECA_RESP_POLL:
        res = true;
        break;
    case DECA_FINAL:
        res = true;
        break;
    }
    return res;
}



bool decawave_proc_header(DecaWaveHandle_t* const Node, const uint8_t* const arr, uint16_t size) {
    bool res = false;
    if(arr) {
        if(DECAWAVE_FRAME_MIN_SIZE <= size) {
            memcpy(&Node->rx_header, arr, sizeof(DecaWaveHeader_t));
            if(Node->preamble_val == Node->rx_header.preamble) {
                LOG_DEBUG(DECAWAVE, "PreambleOk read 0x%x", Node->rx_header.preamble);
                res = decawave_is_valid_message(Node->rx_header.message);
                if(res) {
                    LOG_DEBUG(DECAWAVE, "MessOk read 0x%x", Node->rx_header.message);
                    if(Node->rx_header.payload_size) {
                        LOG_DEBUG(DECAWAVE, "SpotPayload %u byte", Node->rx_header.payload_size);
                        if(Node->rx_header.payload_size < DECAWAVE_MAX_PAYLOAD) {
                            memcpy(Node->rx_payload, &arr[DECAWAVE_PAYLOAD_INDEX], Node->rx_header.payload_size);
                        }
                    }

                    // res = decawave_flow_control(LOG_LEVEL_NOTICE, Node);
                    res = protocol_check_flow_control(DECAWAVE, &Node->Flow, Node->rx_header.sequence_number, IF_UWB);
                    Node->rx_pkt_cnt++;

                    Node->crc16.calc = 0;
                    Node->crc16.read = 0;
                    memcpy(&Node->crc16.read, &arr[size - 2], 2);
                    res = crc16_check(arr, size - 2, Node->crc16.read, &Node->crc16.calc);
                    if(res) {
                        Node->crc_ok_cnt++;
                        LOG_DEBUG(DECAWAVE, "CrcOk read 0x%x", Node->crc16.read);
#ifdef HAS_DECAWAVE_SNIFFER
                        led_mono_blink(Node->debug_led_num,100);
                        decawave_log_sd(&(Node->rx_header));
#endif
                        res = true;
                    } else {
                        res = false;
                        Node->crc_err_cnt++;
                        DecaWaveHeaderDiag(LOG_LEVEL_ERROR, "RxHeader", &Node->rx_header);
                        LOG_ERROR(DECAWAVE, "WrongCrc Read 0x%x Calc 0x%x", Node->crc16.read, Node->crc16.calc);
                    }
                } else {
                    LOG_ERROR(DECAWAVE, "WrongMessage 0x%x", Node->rx_header.message);
                }
            } else {
                LOG_ERROR(DECAWAVE, "WrongPreamble 0x%x", Node->rx_header.preamble);
            }
        }
    }
    return res;
}

bool decawave_send_ll(DecaWaveHandle_t* const Node, DwcaMess_t mess_type, uint16_t destination_id, UwbVatiable_t var_id,
                      uint8_t* buff, uint32_t payload_size) {
    bool res = false;
    LOG_NOTICE(DECAWAVE, "Tx %s", DecaMes2Str(mess_type));
    if(Node) {
        Node->tx_header.preamble = Node->preamble_val;
        Node->tx_header.message = mess_type;
        Node->tx_sequence_number++;
        Node->tx_header.sequence_number = Node->tx_sequence_number;
        Node->tx_header.destination_addr = destination_id;
        Node->tx_header.source_addr = Node->addr;
        Node->tx_header.payload_size = payload_size;

        if(Node->tx_header.source_addr != Node->tx_header.destination_addr) {
            DecaWaveHeaderDiag(LOG_LEVEL_NOTICE, "Tx", &Node->tx_header);
            /*Compose frame*/
            memcpy(&Node->tx_frame[0], Node->tx_header.buff, sizeof(Node->tx_header));
            if(payload_size) {
                /*Payload*/
                Node->tx_frame[DECAWAVE_HEADER_SIZE] = var_id;
                if(buff) {
                    if(1 < payload_size) {
                        memcpy(&Node->tx_frame[DECAWAVE_HEADER_SIZE + 1], buff, payload_size - 1);
                    } else {
                        LOG_NOTICE(DECAWAVE, "SizeTooSmall %u Need 2+", payload_size);
                    }
                }
            }

            /*Compose CRC16*/
            Node->tx_size = sizeof(DecaWaveHeader_t) + payload_size;
            Node->crc16.calc = calc_crc16_ccitt_false(Node->tx_frame, Node->tx_size);
            memcpy(&Node->tx_frame[Node->tx_size], &Node->crc16.calc, CRC16_SIZE);
            Node->tx_size += CRC16_SIZE;

#ifdef HAS_TBFP
            res = tbfp_send(Node->tx_frame, Node->tx_size, Node->interface, 1, ACK_NO_NEED, FRAME_ID_DECAWAVE);
            if(res) {
                LOG_DEBUG(DECAWAVE, "Send %s Ok", DecaMes2Str(mess_type));
                res = true;
            } else {
                res = false;
                LOG_ERROR(DECAWAVE, "Send %s Err", DecaMes2Str(mess_type));
            }
#else
            res = false;
#endif /*HAS_TBFP*/
        } else {
            res = false;
            Node->err_cnt++;
            LOG_WARNING(DECAWAVE, "SrcID=DistID 0x%x", destination_id);
        }
    }
    return res;
}

bool decawave_send(uint8_t num, DwcaMess_t mess_type, uint16_t destination_id, UwbVatiable_t var_id, uint8_t* buff,
                   uint32_t size) {
    bool res = false;
    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    res = decawave_send_ll(Node, mess_type, destination_id, var_id, buff, size);
    return res;
}

bool decawave_send_poll(uint8_t num, const UwbIdInfo_t* const IdInfo) {
    bool res = false;
    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    if(Node) {
        Node->role = UWB_ROLE_TAG;
        PollPayload_t Paylpad;

        res = uwb_is_vaild_distance(  IdInfo->range_m.cur);
        if (res) {
            Paylpad.valid = IdInfo->valid;
            Paylpad.distance_real_m = IdInfo->range_m.cur;
        } else {
            Paylpad.valid = false;
            Paylpad.distance_real_m = DBL_MAX;
        }
        res =
            decawave_send_ll(Node, DECA_POLL, IdInfo->id, UWB_VAR_SHARE_DIST, Paylpad.buff, sizeof(PollPayload_t) + 1);
    }
    return res;
}

bool decawave_send_response_poll(uint8_t num) {
    bool res = false;
    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    if(Node) {
        Node->role = UWB_ROLE_ANCOR;
        res = decawave_send_ll(Node, DECA_RESP_POLL, Node->tag_addr, UWB_VAR_LACK, NULL, 0);
    }
    return res;
}

bool decawave_send_final(uint8_t num, UwbVatiable_t var_id, uint8_t* buff, uint32_t size) {
    bool res = false;
    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    if(Node) {
        res = decawave_send_ll(Node, DECA_FINAL, Node->tag_addr, var_id, buff, size);
        if(res) {
            Node->role = UWB_ROLE_ANCOR;
            Node->spin_cnt++;
#ifdef HAS_LED_MONO
            led_mono_blink(Node->debug_led_num, 50);
#endif
        }
    }
    return res;
}

bool decawave_send_response_payload(uint8_t num, uint16_t destination_id, UwbVatiable_t var_id, uint8_t* buff,
                                    uint32_t size) {
    bool res = false;
    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    if(Node) {
        res = decawave_send_ll(Node, DECA_RESP, destination_id, var_id, buff, size);
    }
    return res;
}

static bool decawave_calc_phase1(DecaWaveHandle_t* const Node) {
    bool res = false;
    LOG_PARN(DECAWAVE, "CalcPhase1...");
    if(Node->responder.t_delay < Node->initiator.t_loop) {
        Node->phase1.tof = (Node->initiator.t_loop - Node->responder.t_delay) / 2;
        Node->phase1.tof_s = TIMER_2_SECONDS(Node->phase1.tof, Node->timer_clock);
        Node->phase1.distance_m.cur = physics_timer_to_dist(Node->phase1.tof, Node->timer_clock);
        Node->phase1.distance_m.min = MIN(Node->phase1.distance_m.min, Node->phase1.distance_m.cur);
        Node->phase1.distance_m.max = MAX(Node->phase1.distance_m.max, Node->phase1.distance_m.cur);
        Node->phase1.distance_real_m = Node->phase1.distance_m.cur - Node->phase1.ant_delay_m;
        Node->phase1.update_time_stamp_ms = time_get_ms32();
        Node->phase1.valid = true;
        LOG_NOTICE(DECAWAVE, "Preliminary1Dist %f m", Node->phase1.distance_real_m);
        res = true;
    } else {
        LOG_ERROR(DECAWAVE, "Phase1CalcDist 1nd TimingErr Tloop:%llu<Tdelay:%llu", Node->initiator.t_loop,
                  Node->responder.t_delay);
        res = false;
    }
    return res;
}

static bool decawave_calc_phase2(DecaWaveHandle_t* const Node) {
    bool res = false;
    LOG_PARN(DECAWAVE, "CalcPhase2..");
    if(Node->initiator.t_delay < Node->responder.t_loop) {
        Node->phase2.tof = (Node->responder.t_loop - Node->initiator.t_delay) / 2;
        Node->phase2.tof_s = TIMER_2_SECONDS(Node->phase2.tof, Node->timer_clock);
        Node->phase2.distance_m.cur = physics_timer_to_dist(Node->phase2.tof, Node->timer_clock);
        Node->phase2.distance_m.min = MIN(Node->phase2.distance_m.min, Node->phase2.distance_m.cur);
        Node->phase2.distance_m.max = MAX(Node->phase2.distance_m.max, Node->phase2.distance_m.cur);
        Node->phase2.distance_real_m = Node->phase2.distance_m.cur - Node->phase2.ant_delay_m;
        Node->phase2.update_time_stamp_ms = time_get_ms32();
        Node->phase2.valid = true;
        LOG_NOTICE(DECAWAVE, "Preliminary2Dist %f m", Node->phase2.distance_real_m);
        res = true;
    } else {
        LOG_ERROR(DECAWAVE, "2nd TimingErr Tloop:%llu<Tdelay:%llu", Node->responder.t_loop, Node->initiator.t_delay);
        res = false;
    }
    return res;
}

bool decawave_proc_data(DecaWaveHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_PROTECTED(DECAWAVE, "ProcDataType 0x%x=%s", Node->rx_payload[0], DecaWaveVarId2Str(Node->rx_payload[0]));
        switch(Node->rx_payload[0]) {
        case UWB_VAR_SHARE_DIST: {
            if(sizeof(PollPayload_t) == (Node->rx_header.payload_size - 1)) {
                PollPayload_t PollPayload;
                memcpy(&PollPayload, &Node->rx_payload[1], sizeof(PollPayload_t));
                if(PollPayload.valid) {
                        if(PollPayload.distance_real_m<0.0){
                            LOG_WARNING(DECAWAVE, "NegativeDistFromInitiator %7.2f m", PollPayload.distance_real_m);
                            PollPayload.distance_real_m =0.0;
                        }
                        LOG_DEBUG(DECAWAVE, "DistFromInitiator %f m", PollPayload.distance_real_m);
                        Node->final.valid = true;
#ifdef HAS_DISTANCE
                        DistanceHandle_t* DistNode = DistanceGetNode(Node->distance_num);
                        if(DistNode) {
                            DistNode->input = DISTANCE_INPUT_NEW_MEASUREMENT;
                            DistNode->new_dist_time_stamp_ms = time_get_ms32();
                        }
#endif /*HAS_DISTANCE*/
                        Node->final.distance_real_m = PollPayload.distance_real_m;
                        DATA_UPDATE(Node->final.distance_m, PollPayload.distance_real_m);
#ifdef HAS_FAT_FS
                        res = fat_fs_save_double("DistM.txt", PollPayload.distance_real_m);
                        if (false==res) {
                            LOG_ERROR(DECAWAVE, "logDistErr");
                        }
#endif
                        Node->final.update_time_stamp_ms = time_get_ms32();
                        res = true;
#ifdef HAS_FIR
                        res = fir_proc(Node->fir_filter_num, PollPayload.distance_real_m,
                                       &Node->distance_filtered_real_m);
#endif /*HAS_FIR*/
                    }

            } else {
                LOG_DEBUG(DECAWAVE, "VrongPaylaodSize Need %u byte", sizeof(PollPayload_t));
            }
        } break;
        case UWB_VAR_RESPONDER_T_DELAY:
            memcpy(&Node->responder.t_delay, &Node->rx_payload[1], 8);
            res = true;
            break;
        case UWB_VAR_INITIATOR_T_LOOP:
            memcpy(&Node->initiator.t_loop, &Node->rx_payload[1], 8);
            decawave_calc_phase1(Node);
            //   res = fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_RESPONSE_WITH_INITIATOR_T_LOOP);
            res = true;
            break;
        case UWB_VAR_RESPONDER_TIMINGS: {
#ifdef HAS_DS_TWR
            ResponderTiming_t ResponderTiming;
            memcpy(&ResponderTiming, &Node->rx_payload[1], sizeof(ResponderTiming_t));
            Node->responder.t_delay = ResponderTiming.t_delay;
            Node->responder.t_loop = ResponderTiming.t_loop;
            LOG_DEBUG(DECAWAVE, "RxResponer Timings Tdelay %llu Tloop %llu", Node->responder.t_delay,
                      Node->responder.t_loop);
            LOG_DEBUG(DECAWAVE, "RxResponer Timings Tdelay 0x%llx Tloop 0x%llx", Node->responder.t_delay,
                      Node->responder.t_loop);
            DsTwrItem.start_ms = time_get_ms32();
            res = fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_PESPONDER_TIMINGS);
#endif
        } break;
        case UWB_VAR_INITIATOR_T_DELAY:
            memcpy(&Node->initiator.t_delay, &Node->rx_payload[1], 8);
            res = true;
            break;
        case UWB_VAR_RESPONDER_T_LOOP:
            memcpy(&Node->responder.t_loop, &Node->rx_payload[1], 8);

            res = true;
            break;
        case UWB_VAR_RAW_DATA:
            res = print_mem(&Node->rx_payload[1], Node->rx_header.payload_size - 1, true, true, true, true);
            break;
        default:
            LOG_ERROR(DECAWAVE, "UndefVariable 0x%x", Node->rx_payload[0]);
            res = false;
            break;
        } // switch
    }     // 0<size
    return res;
}

bool decawave_proc_poll(DecaWaveHandle_t* const Node) {
    bool res = false;
#ifdef HAS_DS_TWR
    LOG_DEBUG(DECAWAVE, "ProcRxPoll in State %s", DsTwrState2Str(DsTwrItem.state));
    res = decawave_proc_data(Node);

    DsTwrItem.start_ms = time_get_ms32();
    res = fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_POLL);
#endif

    return res;
}

bool decawave_proc_response(DecaWaveHandle_t* const Node) {
    bool res = false;
#ifdef HAS_DS_TWR
    LOG_PROTECTED(DECAWAVE, "ProcRxResp in State %s", DsTwrState2Str(DsTwrItem.state));
    res = decawave_proc_data(Node);
    DsTwrItem.start_ms = time_get_ms32();
    res = fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_RESPONSE);
#endif

    return res;
}

bool decawave_proc_resp_poll(DecaWaveHandle_t* const Node) {
    bool res = false;
#ifdef HAS_DS_TWR
    LOG_PROTECTED(DECAWAVE, "ProcRxResp+Poll in State %s", DsTwrState2Str(DsTwrItem.state));
    DsTwrItem.start_ms = time_get_ms32();
    res = fifo_push(&DsTwrItem.InputFifo, DS_TWR_INPUT_RX_PESPONSE_POLL);
#endif
    return res;
}

bool ss_twr_calc_distanse(DecaWaveHandle_t* const Node) {
    bool res = false;
    LOG_PROTECTED(DECAWAVE, "CalcSsTwrDist...");
    if(Node) {
        uint8_t ok_cnt = 0;
        res = decawave_calc_phase1(Node);
        if(res) {
            ok_cnt++;
        } else {
            LOG_ERROR(DECAWAVE, "Pase1Err");
            res = false;
        }

        res = decawave_calc_phase2(Node);
        if(res) {
            ok_cnt++;
        } else {
            LOG_ERROR(DECAWAVE, "Pase2Err");
            res = false;
        }

        if(2 == ok_cnt) {
            Node->avarage_distance_m.cur = AVERAGE_2(Node->phase1.distance_m.cur, Node->phase2.distance_m.cur);
            Node->avarage_distance_m.min = MIN(Node->avarage_distance_m.min, Node->avarage_distance_m.cur);
            Node->avarage_distance_m.max = MAX(Node->avarage_distance_m.max, Node->avarage_distance_m.cur);
            res = true;
        }

        Node->phase1.distance_real_m = Node->phase1.distance_m.cur - Node->phase1.ant_delay_m;
        Node->phase2.distance_real_m = Node->phase2.distance_m.cur - Node->phase2.ant_delay_m;
    }
    return res;
}

static bool decawave_calc_distanse(DecaWaveHandle_t* const Node) {
    bool res = false;
    if(Node) {
        if(Node->responder.t_delay < Node->initiator.t_loop) {
            if(Node->initiator.t_delay < Node->responder.t_loop) {
                LOG_DEBUG(DECAWAVE, "CalcDsTwrDist...");
                uint64_t numerator = (Node->initiator.t_loop * Node->responder.t_loop) -
                                     (Node->initiator.t_delay * Node->responder.t_delay);
                uint64_t denominator = (Node->initiator.t_loop + Node->initiator.t_delay + Node->responder.t_loop +
                                        Node->responder.t_delay);
                Node->final.tof = numerator / denominator;
                LOG_DEBUG(DECAWAVE, "Tof %llu tick", Node->final.tof);
                Node->final.tof_s = TIMER_2_SECONDS(Node->final.tof, Node->timer_clock);
                LOG_DEBUG(DECAWAVE, "Tof %f s ", Node->final.tof_s);
                // Node->distance_m = physics_timer_to_dist(Node->tof, Node->timer_clock);

                double distance_m = physics_timer_to_dist(Node->final.tof, Node->timer_clock);
                DATA_UPDATE(Node->final.distance_m, distance_m);
#ifdef HAS_FAT_FS
                res = fat_fs_save_double("uwb_dist_m.txt",distance_m);
                if (false==res) {
                    LOG_ERROR(DECAWAVE, "logDistErr");
                }
#endif
                //Node->final.distance_m.cur = physics_timer_to_dist(Node->final.tof, Node->timer_clock);
                //Node->final.distance_m.min = MIN(Node->final.distance_m.cur, Node->final.distance_m.min);
                //Node->final.distance_m.max = MAX(Node->final.distance_m.cur, Node->final.distance_m.max);
                Node->final.distance_real_m = Node->final.distance_m.cur - Node->final.ant_delay_m;
                Node->final.update_time_stamp_ms = time_get_ms32();
                Node->final.valid = true;
                // LOG_DEBUG(DECAWAVE, "Dist %f m", Node->final.distance_m);
                res = ss_twr_calc_distanse(Node);
                if(res) {
                    Node->spin_cnt++;
#ifdef HAS_LED_MONO
                    led_mono_blink(Node->debug_led_num, 50);
#endif
                    log_level_t ll = log_level_get(DECAWAVE);
                    if(LOG_LEVEL_DEBUG == ll) {
                        res = decawave_diag_distanse(1);
                    }
                }
            } else {
                res = false;
                LOG_ERROR(DECAWAVE, "2st TimingErr Tloop:%llu<Tdelay:%llu", Node->responder.t_loop,
                          Node->initiator.t_delay);
            }
        } else {
            res = false;
            LOG_ERROR(DECAWAVE, "DsTwrCalcDistanse 1nd TimingErr Tloop:%llu<Tdelay:%llu", Node->initiator.t_loop,
                      Node->responder.t_delay);
        }
    }
    return res;
}

bool decawave_proc_final(DecaWaveHandle_t* const Node) {
    bool res = false;
#ifdef HAS_DS_TWR
    DsTwrItem.start_ms = time_get_ms32();
    LOG_DEBUG(DECAWAVE, "SignalRxTimings in State %s", DsTwrState2Str(DsTwrItem.state));
#endif
    // res = ds_twr_parse_responder_timings(&DsTwrItem, Node->rx_payload, Node->rx_header.payload_size);
    res = decawave_proc_data(Node);
    if(res) {
        res = decawave_calc_distanse(Node);
        if(res) {
            Node->calc_dist_cnt++;
        } else {
            LOG_ERROR(DECAWAVE, "CalcDistErr");
            Node->err_cnt++;
        }
        res = true;
    }
    return res;
}

bool decawave_proc_payload(DecaWaveHandle_t* const Node) {
    bool res = false;
    LOG_PROTECTED(DECAWAVE, "ProcPayload %u Byte", Node->rx_header.payload_size);
    switch((uint8_t)Node->rx_header.message) {
    case DECA_BLINK:
        // res = decawave_proc_blink(Node);
        break;
    case DECA_RANGING_INIT:
        // res = decawave_ranging_init(Node);
        break;
    case DECA_POLL:
        res = decawave_proc_poll(Node);
        break;
    case DECA_RESP:
        res = decawave_proc_response(Node);
        break;
    case DECA_RESP_POLL:
        res = decawave_proc_resp_poll(Node);
        break;
    case DECA_FINAL:
        res = decawave_proc_final(Node);
        break;
    default:
        break;
    }
    return res;
}


bool decawave_proc(uint8_t num, const uint8_t* const arr, uint16_t size) {
    bool res = false;
    LOG_PROTECTED(DECAWAVE, "Proc %u byte", size);
    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    if(Node) {
        Node->rx_byte += size;
        memset(&Node->rx_header, 0, sizeof(DecaWaveHeader_t));
        res = decawave_proc_header(Node, arr, size);
        if(res) {
            // cli_printf(CRLF);
            DecaWaveHeaderDiag(LOG_LEVEL_PROTECTED, "Rx", &Node->rx_header);
            Node->tag_addr = Node->rx_header.source_addr;
            if(Node->rx_header.destination_addr == Node->addr) {
                LOG_DEBUG(DECAWAVE, "MyFrame 0x%04x", Node->addr);
                res = decawave_proc_payload(Node);
            } else {
                LOG_DEBUG(DECAWAVE, "AlienFrame Appeal:0x%04x My:0x%04x", Node->rx_header.destination_addr, Node->addr);
                res = true;
            }
        } else {
            LOG_ERROR(DECAWAVE, "FrameError");
        }
    } else {
        LOG_ERROR(DECAWAVE, "NodeErr %u", num);
    }
    return res;
}

static bool decawave_timeng_init(PhaseTimings_t* const Timing, double ant_delay_m) {
    bool res = false;
    if(Timing) {
        LOG_WARNING(DECAWAVE, "InitTiming");
        Timing->ant_delay_m = ant_delay_m;
        Timing->distance_real_m = 9999.9;
        Timing->update_time_stamp_ms = 0;
        Timing->tof = 0xFFFFFFFFFFFFFFFF;
        Timing->tof_s = 9999.9;
        Timing->valid = false;
        res = double_val_reset(&Timing->distance_m);
    }
    return res;
}



bool decawave_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DECAWAVE, "Init %u", num);
    const DecaWaveConfig_t* Config = DecaWaveGetConfig(num);
    if(Config) {
        LOG_WARNING(DECAWAVE, "SpotConfig %u", num);
        DecaWaveHandle_t* Node = DecaWaveGetNode(num);
        if(Node) {
            LOG_WARNING(DECAWAVE, "SpotItem %u", num);
            Node->addr = Config->addr_def;
            Node->debug_led_num = Config->debug_led_num;
            Node->fir_filter_num = Config->fir_filter_num;
            Node->interface = Config->interface;
            Node->preamble_val = Config->preamble_val;
            Node->timer_clock = Config->timer_clock;
            Node->distance_num = Config->distance_num;
            LOG_WARNING(DECAWAVE, "MyID 0x%x", Node->addr);
            Node->rx_byte = 0;
            Node->spin_cnt = 0;

            res = decawave_timeng_init(&Node->phase1, Config->phase1_ant_delay_m);
            res = decawave_timeng_init(&Node->phase2, Config->phase2_ant_delay_m);
            res = decawave_timeng_init(&Node->final, Config->ant_delay_m);
            res = double_val_reset(&Node->avarage_distance_m);

            res = protocol_flow_init(&Node->Flow);

#if 0
            (void)out_res;
            LOAD_PARAM(DECAWAVE, PAR_ID_PHASE1_OFFSET, Node->phase1.ant_delay_m, Config->ant_delay_m);
            LOAD_PARAM(DECAWAVE, PAR_ID_PHASE2_OFFSET, Node->phase2.ant_delay_m, Config->ant_delay_m);
            LOAD_PARAM(DECAWAVE, PAR_ID_FINAL_OFFSET, Node->final.ant_delay_m, Config->ant_delay_m);
#endif /*HAS_PARAM*/
#ifdef HAS_PARAM
            bool out_res = true;
            LOAD_PARAM(DECAWAVE, PAR_ID_DECAWAVE_ID, Node->addr, Config->addr_def);
            if(false == out_res) {
                LOG_WARNING(DECAWAVE, "ParamReadErr");
                res = false;
            }
#endif /*HAS_PARAM*/
        } else {
            LOG_ERROR(DECAWAVE, "%u NodeErr", num);
        }
    } else {
        LOG_DEBUG(DECAWAVE, "%u NoConf", num);
    }
    return res;
}

bool decawave_dist_get(uint8_t num, double* const dist) {
    bool res = false;
    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    if(Node) {
        res = decawave_dist_get_ll(Node, dist);
    } else {
        LOG_ERROR(DECAWAVE, "NodeErr %u", num);
    }
    return res;
}


COMPONENT_INIT_PATTERT(DECAWAVE, DECAWAVE, decawave)

