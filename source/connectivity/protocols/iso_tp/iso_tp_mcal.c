#include "iso_tp_mcal.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "array_diag.h"
#include "byte_utils.h"
#include "cli_drv.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "interfaces_diag.h"
#include "log.h"
#include "protocol.h"
#include "system_diag.h"
#include "time_mcal.h"

#ifdef HAS_SLCAN
#include "slcan.h"
#endif

#ifdef HAS_CAN
#include "can_mcal.h"
#endif

#ifdef HAS_UDS
#include "uds.h"
#endif

COMPONENT_GET_NODE(IsoTp, iso_tp)

COMPONENT_GET_CONFIG(IsoTp, iso_tp)

IsoTpHandle_t* IsoTpIfToNode(const InterfaceType_t interface_if) {
    IsoTpHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = iso_tp_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(IsoTpInstance[i].valid) {
            if(interface_if.word == IsoTpInstance[i].interface_if.word) {
                Node = &IsoTpInstance[i];
                break;
            }
        }
    }
    return Node;
}

static bool iso_tp_is_valid_single_frame(const CanMessage_t* const RxMessage) {
    bool res = true;
    IsoTpFrame_t Frame = {0};
    memcpy(&Frame, RxMessage->data, 8);
    if(7 < Frame.SingleFrameHeader.data_len) {
        LOG_ERROR(ISO_TP, "SingleFrameSizeToBig:%u,Max:7 byte", Frame.SingleFrameHeader.data_len);
        res = false;
    }
    return res;
}

static bool iso_tp_is_valid_protocol_format(const IsoTpProtocolFormat_t protocol_format) {
    bool res = false;
    switch(protocol_format) {
    case ISO_TP_PROTOCOL_FORMAT_MIXED_ADDRESSING_TA6:
        res = true;
        break;
    case ISO_TP_PROTOCOL_FORMAT_MIXED_ADDRESSING_TA5:
        res = true;
        break;
    case ISO_TP_PROTOCOL_FORMAT_NORMAL_FIXED_ADDRESSING_TA5:
        res = true;
        break;
    case ISO_TP_PROTOCOL_FORMAT_NORMAL_FIXED_ADDRESSING_TA6:
        res = true;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

bool iso_tp_init_common(IsoTpHandle_t* Node, const IsoTpConfig_t* Config) {
    bool res = false;
    if(Config) {
        if(Node) {
#ifdef HAS_IQUEUE
            Node->iqueue_num = Config->iqueue_num;
#endif
            Node->addressing = Config->addressing;
            Node->interface_if = Config->interface_if;
            Node->block_size = Config->block_size;
            Node->tx_fifo_size = Config->tx_fifo_size;
            Node->TxFiFoMem = Config->TxFiFoMem;
            Node->separation_time_s = Config->separation_time_s;
            Node->uds_num = Config->uds_num;
            Node->my_id = Config->my_id;
            Node->cli_num = Config->cli_num;
            Node->name = Config->name;
            Node->num = Config->num;
            Node->uds_num = Config->uds_num;
            Node->valid = true;
            res = fifo_init(&Node->TxFifo, Config->TxFiFoMem, Config->tx_fifo_size);
            res = true;
        }
    }
    return res;
}

static uint8_t iso_tp_extract_frame_code(const uint8_t data0) {
    uint8_t frame_code = 0x0F & (data0 >> 4);
    return frame_code;
}

bool iso_tp_is_my_id(uint32_t id, IsoTpHandle_t* Node) {
    bool res = false;
    IsoTpNormalFixedAddress_t NormalFixedAddress = {0};
    NormalFixedAddress.dword = id;
    if(NormalFixedAddress.target_address == Node->my_id) {
        res = true;
    } else {
        LOG_DEBUG(ISO_TP, "ISO_TP_%u,My:0x%x,AlienAddress:[%s]", Node->num, Node->my_id,
                  IsoTpIdToStr(&NormalFixedAddress));
    }
    return res;
}

bool iso_tp_is_valid_config(const IsoTpConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        ifn(Config->interface_if.word) {
            LOG_ERROR(ISO_TP, "InterFace,Err", Config->num);
            res = false;
        }

        ifn(Config->addressing) {
            LOG_ERROR(ISO_TP, "%u,Addressing,Err", Config->num);
            res = false;
        }
#ifdef HAS_IQUEUE
        ifn(Config->iqueue_num) {
            LOG_ERROR(ISO_TP, "%u,iOueueNum,Err", Config->num);
            res = false;
        }
#endif

        ifn(0.0 < Config->separation_time_s) {
            LOG_ERROR(ISO_TP, "SepTimeS,Err", Config->num);
            res = false;
        }

        ifn(0 < Config->block_size) {
            LOG_ERROR(ISO_TP, "BlockSize,Err", Config->num);
            res = false;
        }

        ifn(Config->TxFiFoMem) {
            LOG_ERROR(ISO_TP, "TxFiFoMem,Err", Config->num);
            res = false;
        }

        ifn(0 < Config->tx_fifo_size) {
            LOG_ERROR(ISO_TP, "tx_fifo_size,Err", Config->num);
            res = false;
        }

        ifn(Config->name) { LOG_WARNING(ISO_TP, "Name,Err", Config->num); }
    }
    return res;
}

int8_t iso_tp_can_num_to_iso_tp_num(uint8_t can_num) {
    int8_t iso_tp_num = -1;
    //   Interfaces_t interface_if = can_num_to_interface(can_num);
    uint32_t cnt = iso_tp_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(INTERFACE_NAME_CAN == IsoTpInstance[i].interface_if.interface_name) {
            if(can_num == IsoTpInstance[i].interface_if.num) {
                if(IsoTpInstance[i].valid) {
                    iso_tp_num = IsoTpInstance[i].num;
                    break;
                }
            }
        }
    }

    return iso_tp_num;
}

static bool iso_tp_is_valid_flow_status(uint8_t flow_status) {
    bool res = false;
    switch(flow_status) {
    case FLOW_CONRTOL_FLAG_CONTINUE_TO_SEND:
        res = true;
        break;
    case FLOW_CONRTOL_FLAG_WAIT:
        res = true;
        break;
    case FLOW_CONRTOL_FLAG_OVERFLOW:
        res = true;
        break;
    default: {
        LOG_DEBUG(ISO_TP, "NotIsoTpFrame,Wrong,FlowStatus:0x%x", flow_status);
        res = false;
    } break;
    }
    return res;
}

static bool iso_tp_is_valid_frame_id(const uint8_t frame_id) {
    bool res = false;
    switch(frame_id) {
    case ISO_TP_FRAME_CODE_SINGLE_FRAME:
        res = true;
        break;
    case ISO_TP_FRAME_CODE_FIRST_FRAME:
        res = true;
        break;
    case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME:
        res = true;
        break;
    case ISO_TP_FRAME_CODE_FLOW_CONTOL:
        res = true;
        break;
    default: {
        res = false;
        LOG_DEBUG(ISO_TP, "NotIsoTpFrame,Wrong,FrameId:0x%x", frame_id);
    } break;
    }
    return res;
}

static bool iso_tp_proc_wait_flow_control_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node->unproc_frame) {
        LOG_PARN(ISO_TP, "ProcRxWaitFlowContol,%s", IsoTpNodeToStr(Node));
        IsoTpFlowControlHeader_t RxHeader = {0};
        memcpy(RxHeader.buff, Node->RxFrame.data, 3);
        if(ISO_TP_FRAME_CODE_FLOW_CONTOL == RxHeader.frame_id) {
            // IsoTpDiagFlowControlHeader(&RxHeader);
            if(FLOW_CONRTOL_FLAG_CONTINUE_TO_SEND == RxHeader.flow_status) {
                uint32_t cur_time_ms = time_get_ms32();
                res = iso_tp_is_valid_separation_time_code(RxHeader.min_sep_time);
                if(!res) {
                    /*
                    If an FC N_PDU message is received with a reserved STmin parameter value, then the sending network
                    entity shall use the longest STmin value specified by this part of ISO 15765 (7F16 = 127 ms) instead
                    of the value received from the receiving network entity for the duration of the on-going segmented
                    message transmission.
                    */
                    RxHeader.min_sep_time = 0x7F;
                    LOG_WARNING(ISO_TP, "MinSepTimeCodeError:0x%08X,SetMax:0x7F", RxHeader.min_sep_time);
                }
                float separation_time_s = iso_tp_separation_time_code_to_seconds(RxHeader.min_sep_time);
                Node->tx_period_ms = (uint32_t)SEC_2_MSEC(separation_time_s);
                Node->blocks_to_send = RxHeader.block_size;
                Node->tx_next_time_ms = cur_time_ms + Node->tx_period_ms;
                Node->tx_sn = 0;
                Node->state = ISO_TP_STATE_TX_REST;
                res = true;
            }
        } else {
            LOG_ERROR(ISO_TP, "NotAutoFlowControl");
        }
        Node->unproc_frame = false;

        LOG_PARN(ISO_TP, "%s", IsoTpNodeToStr(Node));
    }

    return res;
}

/*TODO test it*/
uint8_t separation_time_s_to_sep_time_code(float separation_time_s) {
    uint8_t sep_time_code = ISO_TP_SEPARATION_TIME_CODE_MAX_VAL_127_MS;
    if(USEC_2_SEC(100.0) <= separation_time_s) {
        if(separation_time_s <= USEC_2_SEC(900)) {
            sep_time_code = (uint8_t)roundf(10000.0f * separation_time_s + 240.0f);
        } else {
            if(separation_time_s <= 0.127f) {
                sep_time_code = (uint8_t)roundf(1000.0f * separation_time_s);
            } else {
                sep_time_code = ISO_TP_SEPARATION_TIME_CODE_MAX_VAL_127_MS;
            }
        }
    } else {
        sep_time_code = ISO_TP_SEPARATION_TIME_CODE_MIN_VAL_0_MS;
    }
    return sep_time_code;
}

static bool iso_tp_send_flow_contol(IsoTpHandle_t* Node) {
    bool res = false;
    LOG_DEBUG(ISO_TP, "Send,FlowControl,BS:%u,ST:%f s", Node->block_size, Node->separation_time_s);
    IsoTpFlowControlHeader_t TxFcHeader = {0};
    TxFcHeader.frame_id = ISO_TP_FRAME_CODE_FLOW_CONTOL;
    TxFcHeader.block_size = Node->block_size;
    TxFcHeader.min_sep_time = separation_time_s_to_sep_time_code(Node->separation_time_s);
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
    LOG_PARN(ISO_TP, "RxDone!Data:Size:%u byte", Node->expected_size);
    res = iso_tp_buff_print_ll(Node, Node->expected_size, ISO_TP_BUFF_RX);

#ifdef HAS_CLI
    // res = cli_process_data(Node->cli_num, Node->RxData, Node->expected_size);
#endif

#ifdef HAS_UDS
    res = uds_proc_rx_data(Node->uds_num, Node->RxData, Node->expected_size);
    log_info_res(ISO_TP, res, "UdsProc");
#endif
    return res;
}

static bool iso_tp_proc_idle_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node->unproc_frame) {
        LOG_PARN(ISO_TP, "ProcIdle,%s", IsoTpNodeToStr(Node));
        uint8_t frame_code = 0x0F & (Node->RxFrame.data[0] >> 4);
        switch(frame_code) {
        case ISO_TP_FRAME_CODE_SINGLE_FRAME: {
            res = true;
            IsoTpSingleFrameHeader_t RxHeader = {0};
            RxHeader.buff[0] = Node->RxFrame.data[0];
            Node->expected_size = RxHeader.data_len;
            memcpy(Node->RxData, &Node->RxFrame.data[1], RxHeader.data_len);
            res = iso_tp_proc_rx_data_ll(Node);
            Node->unproc_frame = false;
        } break;

        case ISO_TP_FRAME_CODE_FIRST_FRAME: {
            Node->rx_prev_sn = 0;
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
            LOG_ERROR(ISO_TP, "UnExpConsecutiveFrame");
            Node->unproc_frame = false;
            res = false;
        } break;

        case ISO_TP_FRAME_CODE_FLOW_CONTOL: {
            LOG_ERROR(ISO_TP, "%u UnExpFlowContol", Node->num);
            Node->unproc_frame = false;
            res = false;
        } break;
        default:
            LOG_ERROR(ISO_TP, "UnExpFrameCode:0x%x", frame_code);
            break;
        }

        Node->unproc_frame = false;
    }
    return res;
}

bool iso_tp_busy_set(uint8_t num, bool on_off) {
    bool res = false;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        Node->in_progress = on_off;
        res = true;
    }
    return res;
}

bool iso_tp_is_idle(uint8_t num) {
    bool res = false;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        res = !Node->in_progress;
    }
    return res;
}

static bool iso_tp_is_valid_flow_control_frame(const CanMessage_t* const RxMessage) {
    bool res = true;
    IsoTpFrame_t Frame = {0};
    memcpy(&Frame, RxMessage->data, 8);
    res = iso_tp_is_valid_flow_status(Frame.FlowControlHeader.flow_status);
    return res;
}

bool iso_tp_is_valid_frame(const CanMessage_t* const RxMessage) {
    bool res = false;
    uint8_t frame_id = 0x0F & (RxMessage->data[0] >> 4);
    res = iso_tp_is_valid_frame_id(frame_id);
    if(res) {
        LOG_PARN(ISO_TP, "RxFrame:%s", IsoTpFrameIdToStr(frame_id));
        switch(frame_id) {
        case ISO_TP_FRAME_CODE_SINGLE_FRAME:
            res = iso_tp_is_valid_single_frame(RxMessage);
            break;
        case ISO_TP_FRAME_CODE_FIRST_FRAME:
            res = true;
            break;
        case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME:
            res = true;
            break;
        case ISO_TP_FRAME_CODE_FLOW_CONTOL:
            res = iso_tp_is_valid_flow_control_frame(RxMessage);
            break;
        default: {
            res = false;
            LOG_ERROR(ISO_TP, "NotIsoTpFrame,Wrong,FrameId:0x%x", frame_id);
        } break;
        }
    }
    return res;
}

uint32_t iso_tp_compose_normal_fixed_addr(const uint8_t source_address, const uint8_t target_address) {
    IsoTpNormalFixedAddress_t Id = {0};
    Id.dword = 0;
    Id.source_address = source_address;
    Id.target_address = target_address;
    Id.protocol_format = ISO_TP_PROTOCOL_FORMAT_NORMAL_FIXED_ADDRESSING_TA5;
    Id.data_page = 0;
    Id.reserved = 0;
    Id.priority = CAN_PRIORITY_TOP;
    LOG_DEBUG(ISO_TP, "Src:0x%02X->Dst:0x%02X--NormalFixedAddr:0x%08X", source_address, target_address, Id.dword);
    return Id.dword;
}

_WEAK_FUN_
uint8_t* iso_tp_rx_data_get(uint8_t num, uint16_t* const size) {
    uint8_t* payload = NULL;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        payload = Node->RxData;
        *size = Node->rx_msg_size;
    }
    return payload;
}

bool iso_tp_writer(const uint8_t num) {
    bool res = false;
    InterfaceType_t interface_if;
    interface_if.num = num;
    interface_if.interface_name = INTERFACE_NAME_ISO_TP;
    res = writer_interface_set(interface_if);
    return res;
}

_WEAK_FUN_
bool iso_tp_rx_message_naiv(uint8_t num, const CanMessage_t* const RxMessage) {
    bool res = false;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        LOG_PARN(ISO_TP, "RxMesg*:%s", CanMessageToStr(RxMessage));
        memcpy(Node->RxFrame.data, RxMessage->data, 8);
        Node->rx_id = RxMessage->identifier.standard;
        Node->unproc_frame = true;
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool iso_tp_rx_message(uint8_t num, const CanMessage_t* const RxMessage) {
    bool res = false;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        if(RxMessage) {
            LOG_DEBUG(ISO_TP, "RxMesg*:%s", CanMessageToStr(RxMessage));
            res = iso_tp_is_valid_frame(RxMessage);
            if(res) {
                memcpy(Node->RxFrame.data, RxMessage->data, 8);
                Node->rx_id = RxMessage->identifier.standard;
                Node->unproc_frame = true;
                res = true;
            } else {
                LOG_ERROR(ISO_TP, "ISO_TP_%u,RxNotIsoTpFrame:%s", num, CanMessageToStr(RxMessage));
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool iso_tp_tx_proc_one(uint8_t num) {
    bool res = false;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        if(ISO_TP_STATE_IDLE == Node->state) {
            uint32_t count = fifo_get_count(&Node->TxFifo);
            if(0 < count) {
                uint8_t txTemp[200] = {0};
                uint32_t txLen = 0;
                res = fifo_pull_array(&Node->TxFifo, txTemp, sizeof(txTemp), &txLen);
                if(res) {
                    if(txLen) {
                        res = iso_tp_send(Node->num, Node->target_id, txTemp, txLen);
                    }
                }
            }
        }
    }
    return res;
}

/*For self test*/
bool iso_tp_proc_rx(uint8_t num, uint16_t rx_frame_id, IsoTpFrame_t* const RxFrame) {
    bool res = false;
    LOG_NOTICE(ISO_TP, "IsoTp%u,RxCanID:0x%04x, %s", num, rx_frame_id, IsoTpFrameToStr(RxFrame));
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        if(RxFrame) {
            memcpy(Node->RxFrame.data, RxFrame->data, 8);
            Node->rx_id = rx_frame_id;
            Node->unproc_frame = true;
            res = true;
        }
    } else {
        LOG_ERROR(ISO_TP, "ProcRxNodeErr %u", num);
    }
    return res;
}
#if 0
#endif

static bool iso_tp_send_can(IsoTpHandle_t* Node, const CanMessage_t* const TxMessage) {
    bool res = false;
    switch(Node->interface_if.num) {
    case 0: {
        res = can_mcal_transmit_message(0, TxMessage);
    } break;
    case 1: {
        res = can_mcal_transmit_message(1, TxMessage);
    } break;
    case 2: {
        res = can_mcal_transmit_message(2, TxMessage);
    } break;
    default:
        break;
    }
    return res;
}

static bool iso_tp_send_iso_tp(IsoTpHandle_t* Node) {
    bool res = false;
    switch(Node->interface_if.num) {
    case 1: {
        iso_tp_proc_rx(1, Node->my_id, &Node->TxFrame);
    } break;
    case 2: {
        iso_tp_proc_rx(2, Node->my_id, &Node->TxFrame);
    } break;
    default:
        break;
    }
    return res;
}

static bool iso_tp_compose_can_message(IsoTpHandle_t* Node, CanMessage_t* CanMessage) {
    bool res = true;
    memcpy(CanMessage->data, Node->TxFrame.data, 8);
    uint32_t tx_id = iso_tp_compose_normal_fixed_addr(Node->my_id, Node->target_id);
    CanMessage->identifier.standard = tx_id;
    CanMessage->id_type = CAN_FRAME_ID_EXTENDED;
    CanMessage->frame_type = CAN_TX_FRAME_DATA;
    CanMessage->size = 8;
    return res;
}

bool iso_tp_if_sent_ll(IsoTpHandle_t* Node) {
    bool res = false;
    LOG_PARN(ISO_TP, "SendToIf:%u=%s", Node->interface_if, InterfaceTypeToStr(Node->interface_if));
    CanMessage_t TxMessage = {0};
    res = iso_tp_compose_can_message(Node, &TxMessage);

    switch(Node->interface_if.interface_name) {
    case INTERFACE_NAME_CAN: {
        res = iso_tp_send_can(Node, &TxMessage);
    } break;
    case INTERFACE_NAME_ISO_TP: {
        res = iso_tp_send_iso_tp(Node);
    } break;

    default:
        LOG_ERROR(ISO_TP, "UndefIf %s", InterfaceTypeToStr(Node->interface_if));
        res = false;
        break;
    }
    return res;
}

static bool iso_tp_send_consecutive_frame_ll(IsoTpHandle_t* Node) {
    bool res = false;
    memset(&Node->TxFrame.data[0], ISO_TP_PADDING_BYTE, 8);
    Node->tx_rest_byte = ((int32_t)Node->tx_size - (int32_t)Node->tx_done_bytes);
    if(0 < Node->tx_rest_byte) {

        IsoTpConsecutiveFrameHeader_t TxHeader = {0};
        TxHeader.frame_id = ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME;
        Node->tx_sn++;
        TxHeader.sn = (Node->tx_sn) % 16;
        Node->TxFrame.data[0] = TxHeader.buff[0];

        uint32_t rest_chunk = uint32_limiter(Node->tx_rest_byte, 7);
        memcpy(&Node->TxFrame.data[1], &Node->TxData[Node->tx_done_bytes], rest_chunk);
        Node->tx_done_bytes += rest_chunk;
        Node->tx_rest_byte = ((int32_t)Node->tx_size - (int32_t)Node->tx_done_bytes);
        LOG_DEBUG(ISO_TP, "SendConsecutiveFrame:%s", IsoToConsecutiveToStr(Node));
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
        uint8_t frame_code = iso_tp_extract_frame_code(Node->RxFrame.data[0]);
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
            LOG_ERROR(ISO_TP, "UnexpFC");
            res = iso_tp_proc_wait_flow_control_ll(Node);
            break;
        default:
            res = false;
            break;
        }
        Node->unproc_frame = true;
    } else {
        uint32_t cur_time_ms = time_get_ms32();
        if(Node->tx_next_time_ms < cur_time_ms) {
            if(Node->tx_done_bytes < Node->tx_size) {
                LOG_PARN(ISO_TP, "TxNext7Bytes,%s", IsoTpNodeToStr(Node));
                res = iso_tp_send_consecutive_frame_ll(Node);
                Node->tx_next_time_ms = cur_time_ms + Node->tx_period_ms;
            } else {
                Node->tx_rest_byte = 0;
                LOG_INFO(ISO_TP, "TxDone.Size:%u Bytes", Node->tx_size);
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
                LOG_PARN(ISO_TP, "FlowOk");
            } else {
                LOG_ERROR(ISO_TP, "FlowErr,%s", IsoTpFlowToStr(Node));
            }
            Node->rx_prev_sn = Header->sn;
        }
    }
    return res;
}

static bool iso_tp_proc_wait_consecutive_in_consecutive_frame(IsoTpHandle_t* const Node) {
    bool res = false;
    IsoTpConsecutiveFrameHeader_t RxHeader;
    Node->rx_block_cnt++;
    RxHeader.buff[0] = Node->RxFrame.data[0];

    iso_tp_verify_flow(Node, &RxHeader);

    Node->rx_rest_byte = (int32_t)Node->expected_size - (int32_t)Node->rx_byte_cnt;
    uint32_t rest_chunk = uint32_limiter((uint32_t)Node->rx_rest_byte, 7);
    memcpy(&Node->RxData[Node->rx_byte_cnt], &Node->RxFrame.data[1], rest_chunk);
    Node->rx_byte_cnt += rest_chunk;
    LOG_PARN(ISO_TP, "LOG_PARN:%u/%u", Node->rx_byte_cnt, Node->expected_size);
    if(Node->expected_size <= Node->rx_byte_cnt) {
        Node->state = ISO_TP_STATE_IDLE;
        Node->rx_block_cnt = 0;

        res = iso_tp_proc_rx_data_ll(Node);
    }

    Node->rx_prev_sn = RxHeader.sn;

    if(Node->block_size == Node->rx_block_cnt) {
        res = iso_tp_send_flow_contol(Node);
    }
    return res;
}

static bool iso_tp_proc_wait_consecutive_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node->unproc_frame) {
        LOG_PARN(ISO_TP, "ISO_TP_%u:ProcWaitConsecFrame", Node->num);
        uint8_t frame_code = 0x0F & (Node->RxFrame.data[0] >> 4);
        switch(frame_code) {
        case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME: {
            res = iso_tp_proc_wait_consecutive_in_consecutive_frame(Node);
        } break;
        default: {
            Node->unproc_frame = false;
            LOG_ERROR(ISO_TP, "UnexpFrameCode:%s,%s", IsoTpFrameIdToStr(frame_code), IsoTpNodeToStr(Node));
            iso_tp_reset_ll(Node);
            res = false;
        } break;
        }
        // Node->unproc_frame = true;
        Node->rx_id = 0;
    }
    return res;
}

static bool iso_tp_is_my_address(IsoTpHandle_t* const Node) {
    bool res = false;
    Node->RxAddress.dword = Node->rx_id;
    LOG_DEBUG(ISO_TP, "RxID:%s", IsoTpIdToStr(&Node->RxAddress));
    if(Node->my_id == Node->RxAddress.target_address) {
        Node->target_id = Node->RxAddress.source_address;
        res = true;
    } else {
        LOG_DEBUG(ISO_TP, "ISO_TP_%u,AlienAddress:[%s]", Node->num, IsoTpIdToStr(&Node->RxAddress));
    }
    return res;
}

static bool iso_tp_proc_fsm(IsoTpHandle_t* Node) {
    bool res = false;
    /* consecutive frames must be send automatically */
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
    case ISO_TP_STATE_TX_REST:
        res = iso_tp_proc_tx_blocks_ll(Node);
        break;
    default:
        LOG_ERROR(ISO_TP, "UndefState %u", Node->state);
        break;
    }
    return res;
}

_WEAK_FUN_
bool iso_tp_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(ISO_TP, "Proc,ISO_TP_%u", num);
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        if(Node->init) {
            if(Node->unproc_frame) {
                LOG_DEBUG(ISO_TP, "NewFrame:%s", IsoTpNodeToStr(Node));
                /*TODO IsIsoTpID?*/
                bool is_my_frame = iso_tp_is_my_address(Node);
                if(is_my_frame) {
                    LOG_PARN(ISO_TP, "%u,SpotMyFrameID:0x%02X", num, Node->rx_id);
                } else {
                    LOG_PARN(ISO_TP, "AlienID:0x%02X,MyID:0x%02X", Node->RxAddress.target_address, Node->my_id);
                    Node->unproc_frame = false;
                    res = true;
                }
            }
            res = iso_tp_proc_fsm(Node);
            Node->spin++;
        }
    }
    return res;
}

static bool iso_tp_send_first_frame_ll(IsoTpHandle_t* Node, const uint8_t* const data, uint32_t size) {
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
                  IsoTpFrameToStr(&Node->TxFrame));
        res = iso_tp_if_sent_ll(Node);
        Node->tx_done_bytes = 6;
    }
    return res;
}

_WEAK_FUN_
IsoTpState_t iso_tp_state_get(uint8_t num) {
    IsoTpState_t state = ISO_TP_STATE_UNDEF;
    return state;
}

static bool iso_tp_send_single_frame_ll(IsoTpHandle_t* Node, const uint8_t* const data, uint32_t size) {
    bool res = false;
    if(Node) {
        if(size <= 7) {
            IsoTpSingleFrameHeader_t TxHeader = {0};
            TxHeader.frame_id = ISO_TP_FRAME_CODE_SINGLE_FRAME;
            TxHeader.data_len = size;
            Node->TxFrame.data[0] = TxHeader.buff[0];
            memcpy(&Node->TxFrame.data[1], data, size);
            res = iso_tp_if_sent_ll(Node);
            if(res) {
                LOG_DEBUG(ISO_TP, "Send,SingleFrame,Len:%u,Data:%x", TxHeader.data_len, ArrayToStr(data, size));
                Node->tx_done_bytes = size;
                Node->tx_rest_byte = 0;
            } else {
                LOG_ERROR(ISO_TP, "SendErr");
            }
        }
    } else {
        LOG_ERROR(ISO_TP, "ssfNodeErr");
    }
    return res;
}

bool iso_tp_is_valid_id(const uint32_t id) {
    bool res = false;
    IsoTpNormalFixedAddress_t NormalFixed = {0};
    NormalFixed.dword = id;
    if(0 == NormalFixed.reserved) {
        if(0 == NormalFixed.data_page) {
            res = iso_tp_is_valid_protocol_format(NormalFixed.protocol_format);
        }
    }

    return res;
}

_WEAK_FUN_
uint16_t iso_tp_rx_size_get(uint8_t num) {
    uint16_t rx_size = 0;
    return rx_size;
}

_WEAK_FUN_
float iso_tp_separation_time_get(uint8_t num) {
    float separation_time_s = -1.0;
    return separation_time_s;
}

_WEAK_FUN_
bool iso_tp_send_naiv(uint8_t num, uint8_t target_address, const uint8_t* const tx_data, const uint32_t size) {
    bool res = false;
    LOG_INFO(ISO_TP, "ISO_TP_%u:Send,Addr:0x%x,Size:%u Byte", num, target_address, size);
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        Node->rx_prev_sn = 0;
        memcpy(Node->TxData, tx_data, size);
        Node->tx_size = size;
        Node->target_id = target_address;

        Node->tx_rest_byte = size;
        memset(&(Node->TxFrame.data), ISO_TP_PADDING_BYTE, 8);
        if(size <= 7) {
            res = iso_tp_send_single_frame_ll(Node, tx_data, size);
            if(res) {
                Node->state = ISO_TP_STATE_IDLE;
            }
        } else {
            res = iso_tp_send_first_frame_ll(Node, tx_data, size);
            if(res) {
                Node->state = ISO_TP_STATE_WAIT_FLOW_CONTROL;
            }
        }
    } else {
        LOG_ERROR(ISO_TP, "snNodeErr %u", num);
    }
    return res;
}

_WEAK_FUN_
bool iso_tp_send(uint8_t num, uint8_t dst_addr, const uint8_t* const tx_data, uint32_t size) {
    bool res = false;
    LOG_INFO(ISO_TP, "ISO_TP_%u:Send,DstAddr:0x%x,Size:%u Byte", num, dst_addr, size);
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        Node->rx_prev_sn = 0;
        if(size <= ISO_TP_MTU) {
            memcpy(Node->TxData, tx_data, size);
            Node->tx_size = size;
            Node->target_id = dst_addr;
            Node->tx_rest_byte = size;

            memset(&(Node->TxFrame.data), ISO_TP_PADDING_BYTE, 8);
            if(size <= 7) {
                res = iso_tp_send_single_frame_ll(Node, tx_data, size);
                if(res) {
                    Node->state = ISO_TP_STATE_IDLE;
                }
            } else {
                res = iso_tp_send_first_frame_ll(Node, tx_data, size);
                if(res) {
                    Node->state = ISO_TP_STATE_WAIT_FLOW_CONTROL;
                }
            }
        } else {
            LOG_ERROR(ISO_TP, "TooBigData");
        }
    } else {
        LOG_ERROR(ISO_TP, "sNodeErr %u", num);
    }
    return res;
}

bool iso_tp_check(void) {
    bool res = true;
    return res;
}

COMPONENT_PROC_PATTERT(ISO_TP, ISO_TP, iso_tp)

static bool iso_tp_init_rx_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->role = ISO_TP_ROLE_RECEIVER;
        Node->state = ISO_TP_STATE_IDLE;
        Node->subscription_id = 0;
        Node->blocks_to_send = 0;
        Node->expected_size = 0;
        Node->rx_block_cnt = 0;
        Node->rx_byte_cnt = 0;
        Node->rx_prev_sn = 0;
        Node->rx_id = 0;
        Node->rx_rest_byte = 0;
        Node->rx_sn = 0;
        Node->rx_prev_sn = 0;
        Node->RxFrame.qword = 0;
        memset(Node->RxData, ISO_TP_PADDING_BYTE, sizeof(Node->RxData));
        Node->unproc_frame = false;
        res = true;
    }
    return res;
}

static bool iso_tp_init_tx_ll(IsoTpHandle_t* Node) {
    bool res = false;
    if(Node) {
        Node->TxFrame.qword = 0;
        Node->tx_sn = 0;
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

bool iso_tp_reset_ll(IsoTpHandle_t* Node) {
    bool res = false;
    Node->state = ISO_TP_STATE_IDLE;
    Node->role = ISO_TP_ROLE_RECEIVER;
    Node->spin = 0;
    res = iso_tp_init_rx_ll(Node);
    if(res) {
        res = iso_tp_init_tx_ll(Node);
    }
    return res;
}

uint8_t iso_tp_my_id_get(uint8_t num) {
    uint8_t my_id = 0;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        my_id = Node->my_id;
    }
    return my_id;
}

bool iso_tp_my_id_set(uint8_t num, uint8_t my_id) {
    bool res = false;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        Node->my_id = my_id;
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool iso_tp_init_one(uint8_t num) {
    bool res = false;
    LOG_INFO(ISO_TP, "ISO_TP%u Init", num);
    const IsoTpConfig_t* Config = IsoTpGetConfig(num);
    if(Config) {
        res = iso_tp_is_valid_config(Config);
        if(res) {
            LOG_WARNING(ISO_TP, "%s", IsoTpConfigToStr(Config));
            IsoTpHandle_t* Node = IsoTpGetNode(num);
            if(Node) {
                LOG_INFO(ISO_TP, "SpotNode %u", num);
                res = iso_tp_init_common(Node, Config);
                res = iso_tp_reset_ll(Node);
                Node->spin = 0;
                Node->init = true;
            } else {
                LOG_ERROR(ISO_TP, "iNodeErr %u", num);
            }
        }
    } else {
        LOG_DEBUG(ISO_TP, "NoConfig %u", num);
    }

    log_level_set(ISO_TP, LOG_LEVEL_INFO);
    return res;
}

static void iso_tpx_puts(uint8_t num, const char* str, int32_t len) {
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        if(str) {
            if(len) {
                bool res = fifo_push_array(&Node->TxFifo, (uint8_t*)str, (uint32_t)len);
                if(!res) {
                    Node->error_cnt++;
                }
            }
        }
    }
}

void iso_tp1_puts(void* stream_ptr, const char* str, int32_t len) { iso_tpx_puts(1, str, len); }

static void iso_tpx_putc(uint8_t num, void* stream_ptr, char ch) {
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        bool res = fifo_push(&Node->TxFifo, (uint8_t)ch);
        if(!res) {
            Node->error_cnt++;
        }
    }
}

void iso_tp1_putc(void* stream_ptr, char ch) { iso_tpx_putc(1, stream_ptr, ch); }

// bool uart_writer_transmit(struct sWriterHandle_t* Node) {
bool iso_tp1_writer_transmit(void* base) {
    bool res = false;
    WriterHandle_t* Node = (WriterHandle_t*)base;
    if(Node) {
        strcpy((char*)Node->data, "");
        uint32_t out_len = 0;
        Node->in_transmit = 0;
        res = fifo_pull_array(&Node->fifo, Node->data, 200, &out_len);
        if(false == res) {
            Node->fifo.err_cnt++;
        } else {
            Node->in_transmit = out_len;
        }

        if(0 < Node->in_transmit) {
            Node->tx_cnt += Node->in_transmit;
            if(Node->enable) {
                IsoTpHandle_t* IsoTp = IsoTpGetNode(1);
                if(IsoTp) {
                    res = fifo_push_array(&IsoTp->TxFifo, (uint8_t*)Node->data, (uint32_t)Node->in_transmit);
                }
            }
            Node->in_transmit = 0;
        }
    }
    return res;
}

void iso_tp2_puts(void* stream_ptr, const char* str, int32_t len) { iso_tpx_puts(2, str, len); }

void iso_tp2_putc(void* stream_ptr, char ch) { iso_tpx_putc(2, stream_ptr, ch); }

// bool uart_writer_transmit(struct sWriterHandle_t* Node) {
bool iso_tp2_writer_transmit(void* base) {
    bool res = false;
    WriterHandle_t* Node = (WriterHandle_t*)base;
    if(Node) {
        strcpy((char*)Node->data, "");
        uint32_t out_len = 0;
        Node->in_transmit = 0;
        res = fifo_pull_array(&Node->fifo, Node->data, 200, &out_len);
        if(false == res) {
            Node->fifo.err_cnt++;
        } else {
            Node->in_transmit = out_len;
        }

        if(0 < Node->in_transmit) {
            Node->tx_cnt += Node->in_transmit;
            if(Node->enable) {
                IsoTpHandle_t* IsoTp = IsoTpGetNode(2);
                if(IsoTp) {
                    res = fifo_push_array(&IsoTp->TxFifo, (uint8_t*)Node->data, (uint32_t)Node->in_transmit);
                }
            }
            Node->in_transmit = 0;
        }
    }
    return res;
}

/*TODO Add inverse function */
float iso_tp_separation_time_code_to_seconds(const uint8_t code) {
    float time_s = 0.0;
    if(code <= ISO_TP_SEPARATION_TIME_CODE_MAX_VAL_127_MS) {
        time_s = ((float)code) * 0.001f;
    } else if((0xF1 <= code) && (code <= 0xF9)) {
        time_s = ((float)code) * 0.0001f;
    } else {
        LOG_ERROR(ISO_TP, "UndefSepTimeCode:0x%08X", code);
    }

    return time_s;
}

_WEAK_FUN_
bool iso_tp_init_custom(void) { return true; }

/* See Table 20 — Definition of STmin values */
bool iso_tp_is_valid_separation_time_code(const uint8_t code) {
    bool res = false;
    if(code <= 0x7F) {
        res = true;
    }

    if(false == res) {
        if(0xF1 <= code) {
            if(code <= 0xF9) {
                res = true;
            }
        }
    }
#if 0
    if(0x80<=code) {
        if(code<=0xF0) {
            res = false ;
        }
    }

    if(0xFA<=code) {
            res = false ;
    }
#endif

    return res;
}

_WEAK_FUN_
bool iso_tp_tx_proc(void) {
    bool res = false;
    uint32_t ok = 0;
    uint32_t cnt = iso_tp_get_cnt();
    (void)cnt;
    uint32_t num = 0;
    for(num = 0; num <= cnt; num++) {
        res = iso_tp_tx_proc_one(num);
        ok = ok_cnt_update(ok, res);
    }
    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool iso_tp_mcal_init(void) {
    bool res = true;
    res = iso_tp_init_custom();
    uint32_t ok = 0;
    uint32_t cnt = iso_tp_get_cnt();
    uint8_t num = 0;
    for(num = 0; num <= cnt; num++) {
        res = iso_tp_init_one(num);
        if(res) {
            ok++;
        } else {
        }
    }
    if(cnt == ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
