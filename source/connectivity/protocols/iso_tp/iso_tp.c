#include "iso_tp.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "byte_utils.h"
#include "code_generator.h"
#include "log.h"
#include "protocol.h"
#ifdef HAS_CAN
#include "can_mcal.h"
#endif
#include "system_diag.h"
#include "time_mcal.h"
#ifdef HAS_UDS
#include "uds.h"
#endif

COMPONENT_GET_NODE(IsoTp, iso_tp)

COMPONENT_GET_CONFIG(IsoTp, iso_tp)

bool static iso_tp_proc_wait_flow_control_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node->unproc_frame) {
        LOG_INFO(ISO_TP, "ProcRxWaitFlowContol,%s", IsoTpNodeToStr(Node));
        IsoTpFlowControlHeader_t RxHeader;
        memcpy(RxHeader.buff, Node->RxFrame.data, 3);
        if(ISO_TP_FRAME_CODE_FLOW_CONTOL == RxHeader.frame_id) {
            IsoTpDiagFlowControlHeader(&RxHeader);
            if(FLOW_CONRTOL_FLAG_CONTINUE_TO_SEND == RxHeader.flow_status) {
                uint32_t cur_time_ms = time_get_ms32();
                Node->tx_period_ms = (uint32_t)(1000.0 * SepTime2Val(RxHeader.min_sep_time));
                Node->blocks_to_send = RxHeader.block_size;
                Node->tx_next_time_ms = cur_time_ms + Node->tx_period_ms;
                Node->sn = 0;
                res = true;
                Node->state = ISO_TP_STATE_TX_REST;
            }
        } else {
            LOG_ERROR(ISO_TP, "NotAFC");
        }
        Node->unproc_frame = false;

        LOG_INFO(ISO_TP, "%s", IsoTpNodeToStr(Node));
    }

    return res;
}

static bool iso_tp_send_flow_contol(IsoTpHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(ISO_TP, "SendFlowControl: BS:%u,ST%u ms", Node->block_size, Node->separation_time_ms);
    IsoTpFlowControlHeader_t TxFcHeader;
    TxFcHeader.frame_id = ISO_TP_FRAME_CODE_FLOW_CONTOL;
    TxFcHeader.block_size = Node->block_size;
    TxFcHeader.min_sep_time = Node->separation_time_ms;
    TxFcHeader.flow_status = FLOW_CONRTOL_FLAG_CONTINUE_TO_SEND;

    // reverse_byte_order_array(TxFcHeader.buff,3);
    Node->rx_block_cnt = 0;
    memcpy(Node->TxFrame.data, TxFcHeader.buff, 3);
    memset(&Node->TxFrame.data[3], ISO_TP_PADDING_BYTE, 5);

    Node->state = ISO_TP_STATE_WAIT_CONSECUTIVE_FRAME;
    res = iso_tp_if_sent_ll(Node);
    return res;
}

static bool iso_tp_proc_rx_data_ll(IsoTpHandle_t* Node) {
    bool res = false;
    LOG_WARNING(ISO_TP, "RxDone! Data:Size:%u byte", Node->expected_size);
    res = iso_tp_buff_print_ll(Node, Node->expected_size, ISO_TP_BUFF_RX);
#ifdef HAS_UDS
    res = uds_proc_rx_data(Node->uds_num, Node->RxData, Node->expected_size);
    if(res) {
        LOG_INFO(ISO_TP, "UdsProcOk");
    } else {
        LOG_ERROR(ISO_TP, "UdsProcOk");
    }
#endif
    return res;
}

bool static iso_tp_proc_idle_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node->unproc_frame) {
        LOG_INFO(ISO_TP, "ProcIdle,%s", IsoTpNodeToStr(Node));
        uint8_t frame_code = 0x0F & (Node->RxFrame.data[0] >> 4);
        switch(frame_code) {
        case ISO_TP_FRAME_CODE_SINGLE_FRAME: {
            res = true;
            IsoTpSingleFrameHeader_t RxHeader = {0};
            RxHeader.byte = Node->RxFrame.data[0];
            Node->expected_size = RxHeader.data_len;
            memcpy(Node->RxData, &Node->RxFrame.data[1], RxHeader.data_len);

            res = iso_tp_proc_rx_data_ll(Node);

            Node->unproc_frame = false;
        } break;

        case ISO_TP_FRAME_CODE_FIRST_FRAME: {
            Node->role = ISO_TP_ROLE_RECEIVER;
            LOG_PARN(ISO_TP, "RxFirstFrame DATA[01]:0x%02x%02x", Node->RxFrame.data[0], Node->RxFrame.data[1]);
            IsoTpFirstFrameHeader_t RxHeader;
            RxHeader.buff[0] = Node->RxFrame.data[0];
            RxHeader.buff[1] = Node->RxFrame.data[1];
            LOG_PARN(ISO_TP, "Word:0x%04x", RxHeader.word);
            RxHeader.word = reverse_byte_order_uint16(RxHeader.word);
            LOG_PARN(ISO_TP, "WordRev:0x%04x", RxHeader.word);
            // memcpy(RxHeader.buff, Node->RxFrame.data, 2);
            Node->expected_size = MASK_12BIT & RxHeader.word;
            LOG_PARN(ISO_TP, "StartRx,ExpectedSize:%u=0x%x Byte", Node->expected_size, Node->expected_size);
            memcpy(Node->RxData, &Node->RxFrame.data[2], 6);
            Node->rx_byte_cnt = 6;

            res = iso_tp_send_flow_contol(Node);
            Node->unproc_frame = false;

        } break;

        case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME: {
            LOG_ERROR(ISO_TP, "UnExpCF");
            Node->unproc_frame = false;
            res = false;
        } break;
        case ISO_TP_FRAME_CODE_FLOW_CONTOL: {
            LOG_ERROR(ISO_TP, "%u UnExpFC", Node->num);
            Node->unproc_frame = false;
            res = false;
        } break;
        default:
            break;
        }

        Node->unproc_frame = false;
    }
    return res;
}

bool iso_tp_proc_rx(uint8_t num, uint16_t rx_frame_id, IsoTpFrame_t* const RxFrame) {
    bool res = false;
    LOG_WARNING(ISO_TP, "%u,RxCAN-ID:0x%04x, %s", num, rx_frame_id, Frame2Str(RxFrame));
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        if(RxFrame) {
            memcpy(Node->RxFrame.data, RxFrame->data, 8);
            Node->rx_id = rx_frame_id;
            Node->unproc_frame = true;
            res = true;
        }
    } else {
        LOG_ERROR(ISO_TP, "NodeErr %u", num);
    }
    return res;
}

bool iso_tp_if_sent_ll(IsoTpHandle_t* Node) {
    bool res = false;
    LOG_PARN(ISO_TP, "SendToIf %s", InterfaceToStr(Node->interface));
    switch((uint32_t)Node->interface) {

    case IF_ISO_TP1: {
        iso_tp_proc_rx(1, Node->my_id, &Node->TxFrame);
        res = true;
    } break;

    case IF_ISO_TP2: {
        iso_tp_proc_rx(2, Node->my_id, &Node->TxFrame);
        res = true;
    } break;

#ifdef HAS_CAN1
    case IF_CAN1: {
        res = can_api_transmit_buff(1, Node->my_id, Node->TxFrame.data, 8);
    } break;
#endif

#ifdef HAS_CAN2
    case IF_CAN2: {
        res = can_api_transmit_buff(2, Node->my_id, Node->TxFrame.data, 8);
    } break;
#endif

    default:
        LOG_ERROR(ISO_TP, "UndefIf %s", InterfaceToStr(Node->interface));
        res = false;
        break;
    }
    return res;
}

IsoTpHandle_t* IsoTpIfToNode(Interfaces_t interface) {
    IsoTpHandle_t* Node = NULL;
    LOG_PARN(ISO_TP, "%s():", __FUNCTION__);
    uint32_t i = 0;
    uint32_t cnt = iso_tp_get_cnt();
    LOG_PARN(ISO_TP, "Cnt %u", cnt);
    for(i = 0; i < cnt; i++) {
        LOG_PARN(ISO_TP, "%u", i);
        if(IsoTpInstance[i].valid) {
            LOG_PARN(ISO_TP, "SpotValid %u", i);
            if(IsoTpInstance[i].interface == interface) {
                LOG_PARN(ISO_TP, "SpotNode  %u", i);
                Node = &IsoTpInstance[i];
                break;
            }
        }
    }
    return Node;
}

static bool iso_tp_send_consecutive_frame_ll(IsoTpHandle_t* Node) {
    bool res = false;
    memset(&Node->TxFrame.data[0], ISO_TP_PADDING_BYTE, 8);
    Node->tx_rest_byte = ((int32_t)Node->tx_size - (int32_t)Node->tx_done_bytes);
    if(0 < Node->tx_rest_byte) {
        IsoTpConsecutiveFrameHeader_t TxHeader;

        TxHeader.frame_id = ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME;
        Node->sn++;
        TxHeader.sn = (Node->sn) % 16;
        Node->TxFrame.data[0] = TxHeader.byte;

        uint32_t rest_chunk = uint32_limiter(Node->tx_rest_byte, 7);
        memcpy(&Node->TxFrame.data[1], &Node->TxData[Node->tx_done_bytes], rest_chunk);
        Node->tx_done_bytes += rest_chunk;
        Node->tx_rest_byte = ((int32_t)Node->tx_size - (int32_t)Node->tx_done_bytes);
        LOG_INFO(ISO_TP, "%u:SendConsecutiveFrame Progress:%u/%u, Rest:%u,SN:%u", Node->num, Node->tx_done_bytes,
                 Node->tx_size, Node->tx_rest_byte, Node->sn);
        res = iso_tp_if_sent_ll(Node);

        if(0 == Node->blocks_to_send) {

        } else {
            Node->blocks_to_send--;
            if(0 == Node->blocks_to_send) {
                LOG_INFO(ISO_TP, "WaitNextControlFrame");
                Node->state = ISO_TP_STATE_WAIT_FLOW_CONTROL;
            }
        }
    }
    return res;
}

static bool iso_tp_proc_tx_blocks_ll(IsoTpHandle_t* Node) {
    bool res = false;

    if(Node->unproc_frame) {
        uint8_t frame_code = 0x0F & (Node->RxFrame.data[0] >> 4);
        switch(frame_code) {
        case ISO_TP_FRAME_CODE_SINGLE_FRAME:
            LOG_ERROR(ISO_TP, "UnexpSF");
            res = false;
            break;
        case ISO_TP_FRAME_CODE_FIRST_FRAME:
            LOG_ERROR(ISO_TP, "UnexpFF");
            res = false;
            break;
        case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME:
            LOG_ERROR(ISO_TP, "UnexpCF");
            res = false;
            break;
        case ISO_TP_FRAME_CODE_FLOW_CONTOL:
            LOG_ERROR(ISO_TP, "UnexpCF?");
            res = iso_tp_proc_wait_flow_control_ll(Node);
            break;
        }
        Node->unproc_frame = true;
    } else {

        uint32_t cur_time_ms = time_get_ms32();
        if(Node->tx_next_time_ms < cur_time_ms) {
            if(Node->tx_done_bytes < Node->tx_size) {
                LOG_INFO(ISO_TP, "TxNext7Bytes,%s", IsoTpNodeToStr(Node));
                res = iso_tp_send_consecutive_frame_ll(Node);
                Node->tx_next_time_ms = cur_time_ms + Node->tx_period_ms;
            } else {
                Node->tx_rest_byte = 0;
                LOG_WARNING(ISO_TP, "Everything has been transferred. Size:%u Bytes", Node->tx_size);
                res = true;
                Node->state = ISO_TP_STATE_IDLE;
            }
        } else {
            LOG_PARN(ISO_TP, "Wait between tx,Cur:%u ms,Next:%u ms", cur_time_ms, Node->tx_next_time_ms);
        }
    }
    return res;
}

static bool iso_tp_verify_flow(IsoTpHandle_t* Node, IsoTpConsecutiveFrameHeader_t* Header) {
    bool res = false;
    if(Node) {
        if(Header) {
            if((Node->rx_prev_sn + 1) == (Header->sn)) {
                res = true;
            } else {
                if((1 == Header->sn) && (15 == Node->rx_prev_sn)) {
                    res = true;
                } else {
                    res = false;
                }
            }

            if(res) {
                LOG_INFO(ISO_TP, "FlowOk");
            } else {
                LOG_ERROR(ISO_TP, "FlowErr");
            }
            Node->rx_prev_sn = Header->sn;
        }
    }
    return res;
}

static bool iso_tp_proc_wait_consecutive_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node->unproc_frame) {
        LOG_INFO(ISO_TP, "%u:ProcRxConsecFrame", Node->num);

        uint8_t frame_code = 0x0F & (Node->RxFrame.data[0] >> 4);
        switch(frame_code) {
        case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME: {
            IsoTpConsecutiveFrameHeader_t RxHeader;
            Node->rx_block_cnt++;
            RxHeader.byte = Node->RxFrame.data[0];

            res = true;
            iso_tp_verify_flow(Node, &RxHeader);

            if(res) {
                Node->rx_rest_byte = (int32_t)Node->expected_size - (int32_t)Node->rx_byte_cnt;
                uint32_t rest_chunk = uint32_limiter((uint32_t)Node->rx_rest_byte, 7);
                memcpy(&Node->RxData[Node->rx_byte_cnt], &Node->RxFrame.data[1], rest_chunk);
                Node->rx_byte_cnt += rest_chunk;
                LOG_WARNING(ISO_TP, "CurRxProgress:%u/%u", Node->rx_byte_cnt, Node->expected_size);
                if(Node->expected_size <= Node->rx_byte_cnt) {
                    Node->state = ISO_TP_STATE_IDLE;
                    Node->rx_block_cnt = 0;

                    res = iso_tp_proc_rx_data_ll(Node);
                }
            }
            Node->rx_prev_sn = RxHeader.sn;

            if(Node->block_size == Node->rx_block_cnt) {
                res = iso_tp_send_flow_contol(Node);
            }

        } break;
        default:
            LOG_ERROR(ISO_TP, "UnexpFrame");
            res = false;
            break;
        }
        Node->unproc_frame = true;
        Node->rx_id = 0;
    }
    return res;
}

bool iso_tp_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(ISO_TP, "Proc %u", num);
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        if(Node->unproc_frame) {
            if(Node->rx_id == Node->my_id) {
                LOG_ERROR(ISO_TP, "%u,SpotMyFrameID:0x%x", num, Node->rx_id);
            } else {
                LOG_DEBUG(ISO_TP, "AlienID:0x%x,MyID:0x%x", Node->rx_id, Node->my_id);
                res = true;
            }
        }

        switch(Node->state) {
        case ISO_TP_STATE_IDLE:
            res = iso_tp_proc_idle_ll(Node);
            break;
        case ISO_TP_STATE_WAIT_FLOW_CONTROL:
            res = iso_tp_proc_wait_flow_control_ll(Node);
            break;
        case ISO_TP_STATE_WAIT_CONSECUTIVE_FRAME:
            res = iso_tp_proc_wait_consecutive_ll(Node);
            break;
            break;
        case ISO_TP_STATE_TX_REST:
            res = iso_tp_proc_tx_blocks_ll(Node);
            break;
        default:
            LOG_ERROR(ISO_TP, "UndefState %u", Node->state);
            break;
        }
    }
    return res;
}

static bool iso_tp_send_first_frame_ll(IsoTpHandle_t* Node, const uint8_t* const data, size_t size) {
    bool res = false;
    // IsoTpDiagNode(Node);
    if(Node) {
        IsoTpFirstFrameHeader_t TxHeader = {0};
        TxHeader.frame_id = ISO_TP_FRAME_CODE_FIRST_FRAME;
        TxHeader.data_len = (uint16_t)size;
        TxHeader.word = reverse_byte_order_uint16(TxHeader.word);
        // Node->TxFrame.data[0]=TxHeader.buff[0];
        // Node->TxFrame.data[1]=TxHeader.buff[1];
        memcpy(&Node->TxFrame.data[0], &TxHeader.buff[0], 2);
        uint32_t i = 0;
        for(i = 0; i < 6; i++) {
            Node->TxFrame.data[2 + i] = data[i];
        }
        // memcpy(&Node->TxFrame.data[2], data, 6); /*???????*/
        LOG_DEBUG(ISO_TP, "%u:SendFirstFrame,MyID:0x%x,DataLen:%u byte,%s", Node->num, Node->my_id, Node->tx_size,
                  Frame2Str(&Node->TxFrame));
        res = iso_tp_if_sent_ll(Node);
        Node->tx_done_bytes = 6;
    }
    return res;
}

static bool iso_tp_send_single_frame_ll(IsoTpHandle_t* Node, const uint8_t* const data, size_t size) {
    bool res = false;
    if(Node) {
        LOG_DEBUG(ISO_TP, "SendSingleFrame");
        if(size <= 7) {
            IsoTpSingleFrameHeader_t TxHeader = {0};
            TxHeader.frame_id = ISO_TP_FRAME_CODE_SINGLE_FRAME;
            TxHeader.data_len = size;
            Node->TxFrame.data[0] = TxHeader.byte;
            memcpy(&Node->TxFrame.data[1], data, size);
            res = iso_tp_if_sent_ll(Node);
            if(res) {
                Node->tx_done_bytes = size;
                Node->tx_rest_byte = 0;
            } else {
                LOG_ERROR(ISO_TP, "SendErr");
            }
        }
    } else {
        LOG_ERROR(ISO_TP, "NodeErr");
    }
    return res;
}

bool iso_tp_send(uint8_t num, const uint8_t* const data, size_t size) {
    bool res = false;
    LOG_INFO(ISO_TP, "%u:Send Size %u Byte", num, size);
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        if(size <= ISO_TP_MTU) {
            memcpy(Node->TxData, data, size);
            Node->tx_size = size;

            Node->tx_rest_byte = size;
            memset(&(Node->TxFrame.data), ISO_TP_PADDING_BYTE, 8);
            if(size <= 7) {
                res = iso_tp_send_single_frame_ll(Node, data, size);
                if(res) {
                    Node->state = ISO_TP_STATE_IDLE;
                }
            } else {
                res = iso_tp_send_first_frame_ll(Node, data, size);
                if(res) {
                    Node->state = ISO_TP_STATE_WAIT_FLOW_CONTROL;
                }
            }
        } else {
            LOG_ERROR(ISO_TP, "TooBigData");
        }
    } else {
        LOG_ERROR(ISO_TP, "NodeErr %u", num);
    }
    return res;
}

bool iso_tp_check(void) {
    bool res = true;
    return res;
}

COMPONENT_INIT_PATTERT(ISO_TP, ISO_TP, iso_tp)

COMPONENT_PROC_PATTERT(ISO_TP, ISO_TP, iso_tp)

static bool iso_tp_init_rx_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->role = ISO_TP_ROLE_RECEIVER;
        Node->state = ISO_TP_STATE_IDLE;
        Node->blocks_to_send = 0;
        Node->rx_block_cnt = 0;
        Node->rx_byte_cnt = 0;
        Node->rx_prev_sn = 0;
        Node->expected_size = 0;
        Node->unproc_frame = false;
        Node->rx_id = 0;
        Node->RxFrame.qword = 0;
        memset(Node->RxData, ISO_TP_PADDING_BYTE, sizeof(Node->RxData));
        res = true;
    }
    return res;
}

static bool iso_tp_init_tx_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->TxFrame.qword = 0;
        Node->sn = 0;
        Node->tx_period_ms = 0;
        Node->tx_next_time_ms = 0;
        Node->blocks_to_send = 0;
        Node->tx_done_bytes = 0;
        Node->tx_size = 0;
        memset(Node->TxData, ISO_TP_PADDING_BYTE, sizeof(Node->TxData));
        res = true;
    }
    return res;
}

static bool iso_tp_init_config_ll(IsoTpHandle_t* Node, const IsoTpConfig_t* Config) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->interface = Config->interface;
            Node->block_size = Config->block_size;
            Node->separation_time_ms = Config->separation_time_ms;
            Node->my_id = Config->my_id;
            Node->num = Config->num;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool iso_tp_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(ISO_TP, "%u Init", num);
    const IsoTpConfig_t* Config = IsoTpGetConfig(num);
    if(Config) {
        // TODO DiagConfig
        LOG_WARNING(ISO_TP, "SpotConfig %u", num);
        IsoTpHandle_t* Node = IsoTpGetNode(num);
        if(Node) {
            LOG_INFO(ISO_TP, "SpotNode %u", num);
            res = iso_tp_init_config_ll(Node, Config);
            Node->uds_num = Config->uds_num;

            Node->state = ISO_TP_STATE_IDLE;
            Node->role = ISO_TP_ROLE_RECEIVER;

            res = iso_tp_init_rx_ll(Node);
            res = iso_tp_init_tx_ll(Node);
            res = true;
        } else {
            LOG_ERROR(ISO_TP, "NodeErr %u", num);
        }
    } else {
        LOG_DEBUG(ISO_TP, "NoConfig %u", num);
    }

    set_log_level(ISO_TP, LOG_LEVEL_INFO);
    return res;
}

double SepTime2Val(uint8_t sep_time) {
    double time_s = 0.0;
    if((0 <= sep_time) && (sep_time <= 0x7F)) {
        time_s = ((double)sep_time) * 0.001;
    } else if((0xF1 <= sep_time) && (sep_time <= 0xF9)) {
        time_s = ((double)sep_time) * 0.000100;
    }

    return time_s;
}

bool iso_tp_init_custom(void) { return true; }
