#include "tbfp.h"
/*FSM for parsing TBFP protocol from byte stream*/

#include <string.h>

#include "data_utils.h"
#include "protocol.h"
#include "std_includes.h"
#include "tbfp_diag.h"
#include "array_diag.h"

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_CRC8
#include "crc8_sae_j1850.h"
#endif

#ifdef HAS_INTERFACES_DIAG
#include "interfaces_diag.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_SYSTEM_DIAG
#include "system_diag.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */
static bool tbfp_parser_proc_wait_preamble(TbfpHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
#ifdef HAS_INTERFACES_DIAG
    LOG_PARN(TBFP, "ParsePre:%s,RxByte:0x%02x", InterfaceToStr(Node->inter_face), rx_byte);
#endif
    if(Node->preamble_val == rx_byte) {
        if(0 == Node->load_len) {
            Node->rx_frame[0] = rx_byte;
            Node->rx_state = WAIT_RETX_CNT;
            Node->load_len = 1;
#ifdef HAS_TBFP_DIAG
            Node->preamble_cnt++;
#endif

#ifdef HAS_INTERFACES_DIAG
#ifdef HAS_TBFP_FLOW_CONTROL
            LOG_PARN(TBFP, "IF:%s,Preamble:0x%x,Flow:%u", InterfaceToStr(Node->inter_face), rx_byte, Node->Flow.cur);
#endif /* HAS_TBFP_FLOW_CONTROL*/
#endif /*HAS_TBFP_DIAG*/
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_PARN(TBFP, "UnExpPreamErr");
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_PARN(TBFP, "ParsePreamErr In:0x%x,Need:0x%x", rx_byte, Node->preamble_val);
#endif
        res = tbfp_parser_reset_rx(Node, WAIT_PREAMBLE);
    }
    return res;
}

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */
/*
 * Wait Frame Flags
 * */
static bool tbfp_parser_proc_retransmit_cnt(TbfpHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "ParseReTx: %u", rx_byte);
#endif
    if(TBFP_INDEX_RETX == Node->load_len) {
        Node->rx_frame[TBFP_INDEX_RETX] = rx_byte;
        TbfpFrameFlags_t FrameFlags = {
            .byte = rx_byte,
        };
        Node->crc_check_need = FrameFlags.crc_check_need;

        Node->load_len = TBFP_INDEX_RETX + 1;
#ifdef HAS_INTERFACES_DIAG
        LOG_PARN(TBFP, "%s ReTxCnt:0x%x", InterfaceToStr(Node->inter_face), rx_byte);
#endif
        Node->rx_state = WAIT_SERIAL_NUM;
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(TBFP, "ParseReTxErr");
#endif
        res = tbfp_parser_reset_rx(Node, WAIT_RETX_CNT);
    }
    return res;
}

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */

/*pre flag SN LEN P_ID   DATA CRC*/
static bool tbfp_parser_proc_wait_serial_num(TbfpHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "ParseSn [%u]=0x%02x", Node->load_len, rx_byte);
#endif
    if(TBFP_INDEX_SER_NUM == Node->load_len) {
        Node->rx_frame[TBFP_INDEX_SER_NUM] = rx_byte;
        Node->load_len = TBFP_INDEX_SER_NUM + 1;
        Node->rx_state = WAIT_SERIAL_NUM;
        res = true;
    } else if((TBFP_INDEX_SER_NUM + 1) == Node->load_len) {
        Node->rx_frame[TBFP_INDEX_SER_NUM + 1] = rx_byte;
        Node->s_num = 0;
        memcpy(&Node->s_num, &Node->rx_frame[TBFP_INDEX_SER_NUM], TBFP_SIZE_SN);
        Node->load_len = TBFP_INDEX_SER_NUM + 2;
#ifdef HAS_INTERFACES_DIAG
        LOG_PARN(TBFP, "%s SN:%u=0x%04x", InterfaceToStr(Node->inter_face), Node->s_num, Node->s_num);
#endif
        Node->rx_state = WAIT_LEN;
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_PARN(TBFP, "ParseSnErr");
#endif
        res = tbfp_parser_reset_rx(Node, WAIT_SERIAL_NUM);
    }
    return res;
}

#ifdef HAS_TBFP_DIAG
static bool tbfp_update_len_stat(TbfpHandle_t* Node, uint16_t payload_len) {
    bool res = true;
    Node->max_len = MAX(Node->max_len, payload_len);
    Node->min_len = MIN(Node->min_len, payload_len);
    return res;
}
#endif /*HAS_TBFP_DIAG*/

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */
/*pre flag SN LEN P_ID   DATA CRC*/
static bool tbfp_parser_proc_wait_len(TbfpHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
    if(TBFP_INDEX_LEN == Node->load_len) {
        Node->rx_frame[TBFP_INDEX_LEN] = rx_byte;
        Node->load_len = TBFP_INDEX_LEN + 1;
        Node->rx_state = WAIT_LEN;
        res = true;
    } else if((TBFP_INDEX_LEN + 1) == Node->load_len) {
        Node->rx_frame[TBFP_INDEX_LEN + 1] = rx_byte;
        Node->load_len = TBFP_INDEX_LEN + TBFP_SIZE_LEN;
        memcpy(&(Node->exp_payload_len), &(Node->rx_frame[TBFP_INDEX_LEN]), TBFP_SIZE_LEN);
#ifdef HAS_INTERFACES_DIAG
        LOG_PARN(TBFP, "%s Len:%u=0x%04x", InterfaceToStr(Node->inter_face), Node->exp_payload_len,
                  Node->exp_payload_len);
#endif
        if(0 < Node->exp_payload_len) {
            if(Node->exp_payload_len <= TBFP_MAX_PAYLOAD) {
                Node->rx_state = WAIT_FRAME_ID;
                res = true;
            } else {
                Node->len_err_cnt++;
#ifdef HAS_INTERFACES_DIAG
                LOG_PARN(TBFP, "%s TooBigData %u Byte", InterfaceToStr(Node->inter_face), Node->exp_payload_len);
#endif
                res = tbfp_parser_reset_rx(Node, WAIT_LEN);
            }

        } else {
            // 0 == Node->exp_payload_len
            Node->rx_state = WAIT_FRAME_ID;
            res = true;
        }
    } else {
#ifdef HAS_LOG
        LOG_PARN(TBFP, "ParseLenErr");
#endif
        res = tbfp_parser_reset_rx(Node, WAIT_LEN);
    }
    return res;
}

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */
static bool tbfp_parser_proc_wait_frame_id(TbfpHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "ProcFrameId");
#endif
    if(WAIT_FRAME_ID == Node->rx_state) {
        res = true;
        Node->rx_frame[TBFP_INDEX_FRAME_ID] = rx_byte;
        Node->rx_state = WAIT_PAYLOAD;
        Node->load_len++;
    }
    return res;
}

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */
static bool tbfp_parser_proc_wait_payload(TbfpHandle_t* Node, uint8_t rx_byte) {
    bool res = false;
#ifdef HAS_INTERFACES_DIAG
    LOG_PARN(TBFP, "%s ParsePayLoad Data[%u]=%u=0x%02x", InterfaceToStr(Node->inter_face),
             Node->load_len - TBFP_SIZE_HEADER, rx_byte, rx_byte);
#endif
    if((TBFP_SIZE_HEADER + Node->exp_payload_len) <= Node->load_len) {
        res = tbfp_parser_reset_rx(Node, WAIT_PAYLOAD);
    } else {
        Node->rx_frame[Node->load_len] = rx_byte;
        if(Node->load_len == (TBFP_SIZE_HEADER + Node->exp_payload_len - 1)) {
            Node->rx_state = WAIT_CRC;
            res = true;
        } else if(Node->load_len < (TBFP_SIZE_HEADER + Node->exp_payload_len - 1)) {
            Node->rx_state = WAIT_PAYLOAD;
            res = true;
        } else {
            /*Payload OverRun*/
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "PayLoadOverRun");
#endif
            res = tbfp_parser_reset_rx(Node, WAIT_PAYLOAD);
        }
        Node->load_len++;
    }
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(TBFP, "ParsePayLoad Data[%u]=0x%02x", Node->load_len - TBFP_SIZE_HEADER, rx_byte);
#endif
    }
    return res;
}

/*
 Node - TBFP RAM node
 size- frame size
 */
static inline bool tbfp_proc_full_ll(TbfpHandle_t* const Node, uint16_t size) {
    bool res = true;
    Node->rx_done = true;

#ifdef HAS_TBFP_EXT
    res = is_tbfp_protocol(Node->fix_frame, size, Node->inter_face);
#endif

    if(res) {
        if(Node) {
#ifdef HAS_LOG
        	LOG_DEBUG(TBFP,"RxFrame:%s",ArrayToStr(Node->fix_frame,Node->rx_frame_len));
            LOG_PARN(TBFP, "IF:%s,ProcFull,Len:%u", InterfaceToStr(Node->inter_face), size);
#endif
            Node->proc_done = false; /**/
            Node->rx_byte += size;
            TbfpHeader_t inHeader = {0};
            memset(inHeader.buff, 0, sizeof(TbfpHeader_t));
            memcpy(&inHeader, Node->fix_frame, sizeof(TbfpHeader_t));
#ifdef HAS_TBFP_FLOW_CONTROL
            bool flow_ctrl_ok = false;
            flow_ctrl_ok = protocol_check_flow_control(TBFP, &Node->Flow, inHeader.snum, Node->inter_face);
            if(flow_ctrl_ok) {
                LOG_PARN(TBFP, "InFlowOk %s", InterfaceToStr(Node->inter_face));
            } else {
                Node->err_cnt++;
                LOG_NOTICE(TBFP, "InFlowErr %s", InterfaceToStr(Node->inter_face));
            }
#endif /*HAS_TBFP_FLOW_CONTROL*/

#ifdef HAS_TBFP_RETRANSMIT
            if((0 < inHeader.flags.lifetime) && (inHeader.flags.lifetime < 4)) {
                res = tbfp_send(&arr[TBFP_INDEX_PAYLOAD], inHeader.len, Node->inter_face, inHeader.flags.lifetime - 1,
                                (TbfpAck_t)inHeader.flags.ack_need, inHeader.payload_id);
            }
#endif /*HAS_TBFP_RETRANSMIT*/

            // res = tbfp_proc_payload(&Node->fix_frame[TBFP_INDEX_PAYLOAD], inHeader.len, Node->inter_face,
            // inHeader.payload_id);
            res = tbfp_proc_payload(Node, inHeader.len, inHeader.payload_id);
#ifdef HAS_LOG
            log_parn_res(TBFP, res, "ProcPayLoad");
#endif

#ifdef HAS_TBFP_ACK
            /*Ack After Proc to pass PC unit tests*/
            if(inHeader.flags.ack_need) {
                res = tbfp_send_ack(inHeader.snum, Node->inter_face);
            }
#endif

        } else {
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "UndefIf:%u", Node->inter_face);
#endif
        }

    } else {
#ifdef HAS_LOG
        LOG_ERROR(TBFP, "NotAframe");
#endif
    }

    return res;
}

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */
static bool tbfp_parser_proc_wait_crc8(TbfpHandle_t* const Node, const uint8_t rx_byte) {
    bool res = false;
#ifdef HAS_LOG
    LOG_PARN(TBFP, "ProcCrc8");
#endif
    uint16_t crc8_index = TBFP_SIZE_HEADER + Node->exp_payload_len;
    if(crc8_index == Node->load_len) {
        Node->rx_frame[Node->load_len] = rx_byte; /*read crc8*/
        Node->read_crc8 = rx_byte;
        Node->load_len = 0;
        uint16_t frame_len = TBFP_SIZE_HEADER + Node->exp_payload_len;
        res = true;
#ifdef HAS_CRC8
        uint8_t calc_crc8 = 0;
        if(Node->crc_check_need) {
            res = crc8_sae_j1850_check(&Node->rx_frame[0], frame_len, Node->read_crc8, &calc_crc8);
        } else {
            res = true;
        }
#endif
        if(res) {
#ifdef HAS_CRC8
#ifdef INTERFACE_DIAG
            LOG_PARN(TBFP, "%s,SN:%u=0x%04x,Crc8=0x02x,Ok!,Flow:%u", InterfaceToStr(Node->inter_face), Node->s_num,
                      Node->s_num, Node->read_crc8, Node->Flow.cur);
#endif
#endif
            // led_blink(&Led[LED_INDEX_RED], 10);

#ifdef HAS_TBFP_DIAG
            tbfp_update_len_stat(Node, Node->exp_payload_len);
#endif
            Node->rx_frame_len =  frame_len + TBFP_SIZE_CRC;
            memcpy(Node->fix_frame, Node->rx_frame,  Node->rx_frame_len );
            Node->rx_state = RX_DONE;
            Node->rx_pkt_cnt++;
            res = tbfp_parser_reset_rx(Node, WAIT_CRC);
            // res = tbfp_proc_full(Node->fix_frame, frame_len + TBFP_SIZE_CRC, Node->inter_face);
            res = tbfp_proc_full_ll(Node, frame_len + TBFP_SIZE_CRC);
#ifdef HAS_LOG
            log_parn_res(TBFP, res, "ProcFull");
#endif
        } else {
            Node->crc_err_cnt++;
#ifdef HAS_INTERFACES_DIAG
#ifdef HAS_CRC8
            LOG_PARN(TBFP, "IF:%s,SN:%u=0x%04x,Crc8Err,read:0x%02x,computed:0x%02x,RxPayLen:%u",
                      InterfaceToStr(Node->inter_face), Node->s_num, Node->s_num, Node->read_crc8, calc_crc8,
                      Node->exp_payload_len);
#endif
#endif

            res = false; // errors
        }
        res = tbfp_parser_reset_rx(Node, WAIT_CRC);
    } else {
#ifdef HAS_LOG
        LOG_ERROR(TBFP, "ParseCrc8Err");
#endif
        res = tbfp_parser_reset_rx(Node, WAIT_CRC);
    }
    return res;
}

/*
  size       1        1     2     2     N      1
  field    PREAMBLE|RETX|SER_NUM|LEN|PAYLOAD|CRC8
 */
bool tbfp_proc_byte(TbfpHandle_t* const Node, uint8_t rx_byte) {
    bool res = false;
#ifdef HAS_TIME
    Node->rx_time_stamp_ms = time_get_ms32();
#endif

#ifdef HAS_TBFP_DIAG
    LOG_PARN(TBFP, "ProcByte:[%u]=0x%02x,State:%s", Node->load_len, rx_byte, TbfpRxState2Str(Node->rx_state));
#endif
    switch(Node->rx_state) {
    case WAIT_PREAMBLE:
        res = tbfp_parser_proc_wait_preamble(Node, rx_byte);
        break;
    case WAIT_RETX_CNT:
        res = tbfp_parser_proc_retransmit_cnt(Node, rx_byte);
        break;
    case WAIT_SERIAL_NUM:
        res = tbfp_parser_proc_wait_serial_num(Node, rx_byte);
        break;
    case WAIT_LEN:
        res = tbfp_parser_proc_wait_len(Node, rx_byte);
        break;
    case WAIT_FRAME_ID:
        res = tbfp_parser_proc_wait_frame_id(Node, rx_byte);
        break;
    case WAIT_PAYLOAD:
        res = tbfp_parser_proc_wait_payload(Node, rx_byte);
        break;
    case WAIT_CRC:
        res = tbfp_parser_proc_wait_crc8(Node, rx_byte);
        break;
    default:
        res = tbfp_parser_reset_rx(Node, WAIT_UNDEF);
        break;
    }
    if(false == res) {
#ifdef HAS_LOG
        LOG_ERROR(TBFP, "ParseByteErr %u", rx_byte);
#endif
    }

    if(WAIT_PAYLOAD == Node->rx_state) {
        if(0 == Node->exp_payload_len) {
            Node->rx_state = WAIT_CRC;
        }
    }
    return res;
}

bool tbfp_parser_init(TbfpHandle_t* const Node, const TbfpConfig_t* const Config) {
    bool res = false;
    if(Config) {
        if(Node) {
#ifdef HAS_INTERFACES_DIAG
        LOG_WARNING(TBFP, "%s,InitParser", InterfaceToStr(Config->inter_face));
#endif
            Node->preamble_val = Config->preamble_val;
            Node->read_crc8 = 0;
            Node->exp_payload_len = 0;
            Node->load_len = 0;
            Node->s_num = 0;
            Node->rx_state = WAIT_PREAMBLE;
            res = true;
        } else {
#ifdef HAS_LOG
            LOG_ERROR(TBFP, "ParserNodeErr");
#endif
        }
    }
    return res;
}
