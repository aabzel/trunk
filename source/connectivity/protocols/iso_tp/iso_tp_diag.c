#include "iso_tp_diag.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "byte_utils.h"
#include "debug_info.h"
#include "iso_tp.h"
#include "log.h"
#include "num_to_str.h"
#include "system_diag.h"
#include "table_utils.h"
#include "writer_config.h"

bool iso_tp_buff_print_ll(IsoTpHandle_t* Node, uint32_t size, IsoTpBuff_t buff) {
    bool res = false;
    if(Node) {
        switch((uint8_t)buff) {
        case ISO_TP_BUFF_TX: {
            LOG_INFO(ISO_TP, "%u,TxData", Node->num);
            res = print_hex(Node->TxData, size);
            cli_printf(CRLF);
        } break;

        case ISO_TP_BUFF_RX: {
            LOG_INFO(ISO_TP, "%u,RxData", Node->num);
            res = print_hex(Node->RxData, size);
            cli_printf(CRLF);
        } break;
        }
    }
    return res;
}

bool iso_tp_diag(void) {
    bool res = false;
    uint32_t i;
    static const table_col_t cols[] = {
        {5, "num"}, {8, "my_ID"}, {9, "state"},  {9, "role"},   {10, "if"},
        {9, "BS"},  {9, "SN"},    {9, "TxSize"}, {9, "RxSize"}, {9, "ExpSize"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t iso_tp_cnt = iso_tp_get_cnt();
    for(i = 0; i <= iso_tp_cnt; i++) {
        IsoTpHandle_t* Node = IsoTpGetNode(i);
        if(Node) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, Node->num);
            cli_printf(" 0x%04x " TSEP, Node->my_id);

            cli_printf(" %7s " TSEP, IsoTpState2Str(Node->state));
            cli_printf(" %7s " TSEP, IsoTpRole2Str(Node->role));
            cli_printf(" %8s " TSEP, InterfaceToStr(Node->interface));
            cli_printf(" %7u " TSEP, Node->block_size);
            cli_printf(" %7u " TSEP, Node->sn);
            cli_printf(" %7u " TSEP, Node->tx_size);
            cli_printf(" %7u " TSEP, Node->rx_byte_cnt);
            cli_printf(" %7u " TSEP, Node->expected_size);
            cli_printf(CRLF);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

const char* SepTime2Str(uint8_t sep_time) {
    static char name[20] = {0};
    double time_s = SepTime2Val(sep_time);
    sprintf(name, "%f ms", time_s * 1000.0);
    return name;
}

const char* FrameId2Str(IsoTpFrameCode_t frame_id) {
    const char* name = "?";
    switch((uint8_t)frame_id) {
    case ISO_TP_FRAME_CODE_SINGLE_FRAME:
        name = "0=SingleFrame,HS:1";
        break;
    case ISO_TP_FRAME_CODE_FIRST_FRAME:
        name = "1=FirstFrame,HS:2";
        break;
    case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME:
        name = "2=ConsecutiveFrame,HS:1";
        break;
    case ISO_TP_FRAME_CODE_FLOW_CONTOL:
        name = "3=FlowControl,HS:3";
        break;
    default:
        break;
    }
    return name;
}

const char* FlowStatus2Str(IsoTpFlowControlFlag_t flow_status) {
    const char* name = "?";
    switch((uint8_t)flow_status) {
    case FLOW_CONRTOL_FLAG_CONTINUE_TO_SEND:
        name = "ContinueSend";
        break;
    case FLOW_CONRTOL_FLAG_WAIT:
        name = "Wait";
        break;
    case FLOW_CONRTOL_FLAG_OVERFLOW:
        name = "OverFlow";
        break;
    default:
        break;
    }
    return name;
}

const char* IsoTpState2Str(IsoTpState_t state) {
    const char* name = "?";
    switch((uint8_t)state) {
    case ISO_TP_STATE_IDLE:
        name = "Idle";
        break;
    case ISO_TP_STATE_WAIT_FLOW_CONTROL:
        name = "WaitFC";
        break;
    case ISO_TP_STATE_WAIT_CONSECUTIVE_FRAME:
        name = "WaitCF";
        break;
    case ISO_TP_STATE_TX_REST:
        name = "Tx";
        break;
    default:
        break;
    }
    return name;
}

const char* IsoTpRole2Str(IsoTpRole_t role) {
    const char* name = "?";
    switch(role) {
    case ISO_TP_ROLE_SENDER:
        name = "Tx";
        break;
    case ISO_TP_ROLE_RECEIVER:
        name = "Rx";
        break;
    default:
        break;
    }
    return name;
}

const char* IsoTpNodeToStr(const IsoTpHandle_t* const Node) {
    static char text[150] = {0};
    if(Node) {
        sprintf(text, "I:%u,RxID:0x%x,MyID:0x%x,%s,%s,RxByte:%u,ExpSize:%u byte,TxByte:%u,TxRestByte:%u", Node->num,
                Node->rx_id, Node->my_id, IsoTpState2Str(Node->state), IsoTpRole2Str(Node->role), Node->rx_byte_cnt,
                Node->expected_size, Node->tx_size, Node->tx_rest_byte);
    }
    return text;
}

bool IsoTpDiagNode(const IsoTpHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(ISO_TP, "%s", IsoTpNodeToStr(Node));
        res = true;
    }
    return res;
}

bool IsoTpDiagFlowControlHeader(IsoTpFlowControlHeader_t* Header) {
    bool res = false;
    if(Header) {
        LOG_INFO(ISO_TP, "FS:%s,Frame:%s,BS:%u,ST:%s", FlowStatus2Str(Header->flow_status),
                 FrameId2Str(Header->frame_id), Header->block_size, SepTime2Str(Header->min_sep_time));

        res = true;
    }
    return res;
}

const char* SingleFrameToStr(const IsoTpFrame_t* const Frame) {
    static char text[150] = {0};
    IsoTpSingleFrameHeader_t Header;
    Header.byte = Frame->data[0];
    sprintf(text, "SingleFrame:0,DL:%u,%s", Header.data_len, ArrayToStr(&Frame->data[1], 7));
    return text;
}

const char* FirstFrameToStr(const IsoTpFrame_t* const Frame) {
    static char text[150] = {0};
    IsoTpFirstFrameHeader_t Header;
    Header.buff[0] = Frame->data[0];
    Header.buff[1] = Frame->data[1];
    Header.word = reverse_byte_order_uint16(Header.word);
    uint16_t expected_size = MASK_12BIT & Header.word;
    sprintf(text, "FirstFrame:1,DL:%u,%s", expected_size, ArrayToStr(&Frame->data[2], 6));
    return text;
}

const char* ConsecutiveFrameToStr(const IsoTpFrame_t* const Frame) {
    static char text[150] = {0};
    if(Frame) {
        sprintf(text, "ConsecutiveFrame:2,SN:%u,%s", Frame->ConsecutiveFrameHeader.sn, ArrayToStr(&Frame->data[1], 7));
    }
    return text;
}

const char* FlowControlToStr(const IsoTpFrame_t* const Frame) {
    static char text[150] = {0};
    if(Frame) {

        sprintf(text, "FlowControl:3:FS:%s,BS:%u,%s", FlowStatus2Str(Frame->FlowControlHeader.flow_status),
                Frame->FlowControlHeader.block_size, SepTime2Str(Frame->FlowControlHeader.min_sep_time),
                ArrayToStr(&Frame->data[3], 5));
    }
    return text;
}

const char* FrameDataToStr(const IsoTpFrame_t* const Frame) {
    static char text[20] = {0};
    if(Frame) {
        strcpy(text, "");
        array2str(Frame->data, 8, text, sizeof(text));
    }
    return text;
}

const char* Frame2Str(const IsoTpFrame_t* const Frame) {
    static char text[150] = {0};
    if(Frame) {
        strcpy(text, "?");
        uint8_t frame_code = 0x0F & (Frame->data[0] >> 4);
        switch(frame_code) {
        case ISO_TP_FRAME_CODE_SINGLE_FRAME:
            sprintf(text, "%s,0x%s", SingleFrameToStr(Frame), FrameDataToStr(Frame));
            break;
        case ISO_TP_FRAME_CODE_FIRST_FRAME:
            sprintf(text, "%s,0x%s", FirstFrameToStr(Frame), FrameDataToStr(Frame));
            break;
        case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME:
            sprintf(text, "%s,0x%s", ConsecutiveFrameToStr(Frame), FrameDataToStr(Frame));
            break;
        case ISO_TP_FRAME_CODE_FLOW_CONTOL:
            sprintf(text, "%s,0x%s", FlowControlToStr(Frame), FrameDataToStr(Frame));
            break;
        }
    }
    return text;
}

bool iso_tp_buff_print(uint8_t num, uint32_t size, IsoTpBuff_t buff) {
    bool res = false;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        res = iso_tp_buff_print_ll(Node, size, buff);
    }
    return res;
}
