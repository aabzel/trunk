#include "protocol_diag.h"

#include <stdio.h>
#include <string.h>

#ifdef HAS_ARRAY
#include "array.h"
#endif
#include "byte_utils.h"
#include "interfaces_diag.h"
#include "log.h"
#include "protocol_types.h"
#include "sys_constants.h"
#include "system_diag.h"

char* ProtocolRxState2Str(ProtocolRxState_t rx_state) {
    char* name = "?";
    switch((uint8_t)rx_state) {
    case WAIT_PREAMBLE:
        name = "Pre";
        break;
    case WAIT_LEN:
        name = "Len";
        break;
    case WAIT_SERIAL_NUM:
        name = "Sn";
        break;
    case WAIT_RETX_CNT:
        name = "ReTx";
        break;
    case WAIT_PAYLOAD:
        name = "Pay";
        break;
    case WAIT_CRC:
        name = "Crc";
        break;
    case WAIT_UNDEF:
        name = "Und";
        break;
    case RX_DONE:
        name = "Done";
        break;
    case WAIT_INIT:
        name = "Init";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

bool flow_ctrl_print_lost(facility_t facility, FlowCrtl_t* Node, uint16_t s_num, Interfaces_t interface) {
    bool res = true;
    if(Node) {
        if(Node->prev_s_num < (s_num - 1)) {
            if(0 < Node->lost_rx_frames) {
                if(Node->prev_s_num) {
                    Node->total_lost_rx_frames += Node->lost_rx_frames;
                }
            }
            if((Node->prev_s_num + 1) == (s_num - 1)) {
#ifdef HAS_INTERFACES_DIAG
                LOG_DEBUG(facility, "%s Lost_%u %u: Flow:%u", InterfaceToStr(interface), Node->lost_rx_frames,
                          s_num - 1, Node->cur);
#endif
            } else {
#ifdef HAS_INTERFACES_DIAG
                LOG_DEBUG(facility, "%s Lost_%u %u-%u Flow:%u", InterfaceToStr(interface), Node->lost_rx_frames,
                          Node->prev_s_num + 1, s_num - 1, Node->cur);
#endif
            }

        } else {
            res = false;
        }
    }
    return res;
}

bool flow_ctrl_diag(facility_t facility, FlowCrtl_t* Node, Interfaces_t interface) {
    bool res = false;
    if(Node) {
#ifdef HAS_INTERFACES_DIAG
        log_write(LOG_LEVEL_INFO, facility, "DiagFlow: %s", InterfaceToStr(interface));
#endif
        log_write(LOG_LEVEL_INFO, facility, "PrevSN %u", Node->prev_s_num);
        log_write(LOG_LEVEL_INFO, facility, "Cur %u", Node->cur);
        log_write(LOG_LEVEL_INFO, facility, "Max %u", Node->maximum_continuous);
        log_write(ErrValue2LogLevel(Node->lost_rx_frames), facility, "Lost %u", Node->lost_rx_frames);
        log_write(ErrValue2LogLevel(Node->err_cnt), facility, "Err %u", Node->err_cnt);
        log_write(LOG_LEVEL_INFO, facility, "Ok %u", Node->ok_cnt);
        log_write(ErrValue2LogLevel(Node->torn_cnt), facility, "TornCnt %u+%u", Node->torn_cnt,
                  Node->torn_cnt - Node->torn_cnt_prev);
        log_write(ErrValue2LogLevel(Node->order_err), facility, "OrderErr %u", Node->order_err);
        log_write(LOG_LEVEL_INFO, facility, "Duplicate %u", Node->duplicate_cnt);
        res = true;
    }
    return res;
}

char* Mask322Str(const Addr32Mask_t* const Mask) {
    if(Mask) {
        if(Mask->size <= 32) {
            char lText[300] = "0";
            memset(lText, 0, sizeof(lText));
            uint32_t i = 0;
            for(i = 0; i < 32; i++) {
                if(i < Mask->size) {
                    if((1 << i) == (Mask->addr & (1 << i))) {
                        lText[i] = '1';
                    } else {
                        lText[i] = '0';
                    }
                } else {
                    lText[i] = 'x';
                    break;
                }
            }
            array_reverse_bytes((uint8_t* const)lText, Mask->size + 1);
            sprintf(text, "%s:%u", lText, Mask->size);
        }
    }
    return text;
}

const char* ProtocolFrame2Str(const uint8_t* const data, size_t size, Protocol_t protocol) {
    const char* name = "?";
    switch((uint32_t)protocol) {
#ifdef HAS_STACK_FRAME
    case PROTO_STACK_FRAME:
        name = StackFrame2Str(data, size);
        break;
#endif
    default:
        break;
    }
    return name;
}

const char* FlowCtrl2Str(const FlowCrtl_t* const Node) {
    static char lText[80] = {0};
    if(Node) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "SN:%u,PrevFlow:%u,CurFlow:%u,MaxFlow:%u,TornCnt:%u,Lost:%u", Node->cur_sn,
                 Node->prev_flow, Node->cur, Node->maximum_continuous, Node->torn_cnt, Node->lost_rx_frames);
    }
    return lText;
}
