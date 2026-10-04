#include "iso_tp_diag.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "byte_utils.h"
#include "common_diag.h"
#include "debug_info.h"
#include "compiler_const.h"
#include "interfaces_diag.h"
#include "iso_tp_mcal.h"
#include "log.h"
#include "num_to_str.h"
#include "can_diag.h"
#include "system_diag.h"
#include "table_utils.h"
#include "writer_config.h"

const char* IsoTpRoleToStr(const IsoTpRole_t role) {
    const char* name = "?";
    switch(role) {
        case ISO_TP_ROLE_SENDER:   name = "Tx"; break;
        case ISO_TP_ROLE_RECEIVER: name = "Rx"; break;
        default:        break;
    }
    return name;
}

const char*  IsoTpAddressingToStr(const IsoTpAddressing_t addressing) {
    const char* name = "?";
    switch(addressing) {
        case ISO_TP_ADDRESSING_NORMAL:      name = "Normal";     break;
        case ISO_TP_ADDRESSING_FIXED:       name = "Fixed";      break;
        case ISO_TP_ADDRESSING_EXTENDED:    name = "Extended";   break;
        case ISO_TP_ADDRESSING_MIXED_11BIT: name = "Mixed11bit"; break;
        case ISO_TP_ADDRESSING_MIXED_29BIT: name = "Mixed29bit"; break;
        default: name = "?"; break;
    }
    return name;
}

const char* IsoTpStateToStr(const IsoTpState_t state) {
    const char* name = "?";
    switch(state) {
        case ISO_TP_STATE_IDLE:                   name = "Idle";   break;
        case ISO_TP_STATE_WAIT_FLOW_CONTROL:      name = "WaitFC"; break;
        case ISO_TP_STATE_WAIT_CONSECUTIVE_FRAME: name = "WaitCF"; break;
        case ISO_TP_STATE_TX_REST:                name = "Tx";     break;
        default: break;
    }
    return name;
}

const char* IsoTpProtocolFormatToStr(const IsoTpProtocolFormat_t protocol_format){
    const char* name = "?";
    switch(protocol_format) {
        case ISO_TP_PROTOCOL_FORMAT_MIXED_ADDRESSING_TA6:   name = "MixedFun";   break;
        case ISO_TP_PROTOCOL_FORMAT_MIXED_ADDRESSING_TA5:   name = "MixedPhy"; break;
        case ISO_TP_PROTOCOL_FORMAT_NORMAL_FIXED_ADDRESSING_TA5: name = "NormalFixedPhy"; break;
        case ISO_TP_PROTOCOL_FORMAT_NORMAL_FIXED_ADDRESSING_TA6: name = "NormalFixedFun";     break;
        default: break;
    }
    return name;
}

static const char* FlowStatusToStr(const IsoTpFlowControlFlag_t flow_status) {
    const char* name = "?";
    switch(flow_status) {
        case FLOW_CONRTOL_FLAG_CONTINUE_TO_SEND: name = "ContinueSend"; break;
        case FLOW_CONRTOL_FLAG_WAIT:             name = "Wait";         break;
        case FLOW_CONRTOL_FLAG_OVERFLOW:         name = "OverFlow";     break;
        default:        break;
    }
    return name;
}

const char* IsoTpFrameIdToStr(const IsoTpFrameCode_t frame_id) {
    const char* name = "?";
    switch(frame_id) {
        case ISO_TP_FRAME_CODE_SINGLE_FRAME:      name = "FC:0,SingleFrame,HdrSz:1";      break;
        case ISO_TP_FRAME_CODE_FIRST_FRAME:       name = "FC:1,FirstFrame,HdrSz:2";       break;
        case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME: name = "FC:2,ConsecutiveFrame,HdrSz:1"; break;
        case ISO_TP_FRAME_CODE_FLOW_CONTOL:       name = "FC:3,FlowControl,HdrSz:3";      break;
        default: name = QWordToStr(frame_id); break;
    }
    return name;
}

static const char* ConsecutiveFrameToStr(const IsoTpFrame_t* const Frame) {
    static char LText[150] = {0};
    if(Frame) {
        strcpy(LText, "ConsecutiveFrame:2,");
        snprintf(LText, sizeof(LText), "%sSN:%u,", LText, Frame->ConsecutiveFrameHeader.sn);
        snprintf(LText, sizeof(LText), "%s%s,", LText, ArrayToStr(&Frame->data[1], 7));
    }
    return LText;
}

bool iso_tp_buff_print_ll(IsoTpHandle_t* Node, uint32_t size, IsoTpBuff_t buff) {
    bool res = false;
    if(Node) {
        switch(buff) {
        case ISO_TP_BUFF_TX: {
            LOG_INFO(ISO_TP, "%u,TxData", Node->num);
            // res = print_hex(Node->TxData, size);
            res = print_mem(Node->TxData, (int32_t)size, true, true, true, true);
            Node->TxData[size] = 0;
            cli_printf("%s" CRLF, Node->TxData);
        } break;

        case ISO_TP_BUFF_RX: {
            LOG_INFO(ISO_TP, "%u,RxData", Node->num);
            // res = print_mem(Node->RxData, size);
            res = print_mem(Node->RxData, (int32_t)size, true, true, true, true);
            Node->RxData[size] = 0;
            cli_printf("%s" CRLF, Node->RxData);
        } break;
        default: res = false ; break;
        }
        cli_printf(CRLF);
    }
    return res;
}

_WEAK_FUN_
bool iso_tp_diag(void) {
    bool res = false;
    uint32_t i;
    static const table_col_t cols[] = {
        {5, "num"},
        {6, "myID"},
        {6, "TaID"},
        {9, "state"},  {9, "role"},   {10, "if"},
        {9, "BS"},  {9, "txSN"},  {9, "TxSize"}, {9, "RxSize"},
        {9, "ExpSize"},
        {9, "spin"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t iso_tp_cnt = iso_tp_get_cnt();
    for(i = 0; i <= iso_tp_cnt; i++) {
        IsoTpHandle_t* Node = IsoTpGetNode(i);
        if(Node) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, Node->num);
            cli_printf(" 0x%02x " TSEP, Node->my_id);
            cli_printf(" 0x%02x " TSEP, Node->target_id);

            cli_printf(" %7s " TSEP, IsoTpStateToStr(Node->state));
            cli_printf(" %7s " TSEP, IsoTpRoleToStr(Node->role));
            cli_printf(" %8s " TSEP, InterfaceTypeToStr(Node->interface_if));
            cli_printf(" %7u " TSEP, Node->block_size);
            cli_printf(" %7u " TSEP, Node->sn);
            cli_printf(" %7u " TSEP, Node->tx_size);
            cli_printf(" %7u " TSEP, Node->rx_byte_cnt);
            cli_printf(" %7u " TSEP, Node->expected_size);
            cli_printf(" %7u " TSEP, Node->spin);
            cli_printf(CRLF);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

static const char* SepTimeToStr(uint8_t sep_time_code) {
    static char name[20] = {0};
    float time_s = iso_tp_separation_time_code_to_seconds(sep_time_code);
    sprintf(name, "%f ms", SEC_2_MSEC(time_s ));
    return name;
}

static const char* FrameDataToStr(const IsoTpFrame_t* const Frame) {
    static char LText[20] = {0};
    if(Frame) {
        strcpy(LText, "");
        array2str(Frame->data, 8, LText, sizeof(LText));
    }
    return LText;
}



static const char* SingleFrameToStr(const IsoTpFrame_t* const Frame) {
    static char LText[150] = {0};
    if(Frame) {
        IsoTpSingleFrameHeader_t Header = {0};
        Header.buff[0] = Frame->data[0];
        strcpy(LText, "SingleFrame:0");
        snprintf(LText, sizeof(LText), "%sDatLen:%u,", LText, Header.data_len);
        snprintf(LText, sizeof(LText), "%s%s,", LText,  ArrayToStr(&Frame->data[1], 7));
    }
    return LText;
}

const char* IsoTpIdToStr(const IsoTpNormalFixedAddress_t* const can_id) {
    static char LText[150] = {0};
    if(can_id) {
        strcpy(LText, "");
        snprintf(LText, sizeof(LText), "%sID:0x%08X,", LText, can_id->dword);
        snprintf(LText, sizeof(LText), "%sExt:0x%08X:", LText, can_id->extended);
        snprintf(LText, sizeof(LText), "%sSource:0x%02X->", LText, can_id->source_address);
        snprintf(LText, sizeof(LText), "%sTarget:0x%02X,", LText, can_id->target_address);
        snprintf(LText, sizeof(LText), "%sPrFrmt:%s,", LText, IsoTpProtocolFormatToStr(can_id->protocol_format));
        snprintf(LText, sizeof(LText), "%sDP:%u,", LText, can_id->data_page);
        snprintf(LText, sizeof(LText), "%sR:%u,", LText, can_id->reserved);
        snprintf(LText, sizeof(LText), "%sPrio:%s,", LText,CanPriorityToStr( can_id->priority));
    }
    return LText;
}

const char* IsoTpNodeToStr(const IsoTpHandle_t* const Node) {
    static char LText[150] = {0};
    if(Node) {
        strcpy(LText, "");
        snprintf(LText, sizeof(LText), "%sN:%u,", LText, Node->num);
        snprintf(LText, sizeof(LText), "%sState:%s,", LText, IsoTpStateToStr(Node->state));
        snprintf(LText, sizeof(LText), "%sRole:%s,", LText, IsoTpRoleToStr(Node->role));
        snprintf(LText, sizeof(LText), "%sMyID:0x%x,", LText, Node->my_id);
        snprintf(LText, sizeof(LText), "%sSubID:0x%x,", LText, Node->subscription_id);
        snprintf(LText, sizeof(LText), "%sRxID:0x%x,", LText, Node->rx_id);
        snprintf(LText, sizeof(LText), "%sRxByte:%u,", LText, Node->rx_byte_cnt);
        snprintf(LText, sizeof(LText), "%sTxByte:%u,", LText, Node->tx_size);
        snprintf(LText, sizeof(LText), "%sExpSize:%u,", LText, Node->expected_size);
        snprintf(LText, sizeof(LText), "%sTxRestByte:%u,", LText, Node->tx_rest_byte);
        snprintf(LText, sizeof(LText), "%sInit:%s,", LText, OnOffToStr(Node->init));
        snprintf(LText, sizeof(LText), "%sSpin:%u,", LText, Node->spin);
    }
    return LText;
}

const char* IsoTpFlowToStr(const IsoTpHandle_t* const Node) {
    static char LText[150] = {0};
    if(Node) {
        strcpy(LText, "");
        snprintf(LText, sizeof(LText), "%sN:%u,", LText, Node->num);
        snprintf(LText, sizeof(LText), "%sSNprv:%u->", LText, Node->rx_prev_sn);
        snprintf(LText, sizeof(LText), "%sSNcur:%u,", LText, Node->rx_sn);
    }
    return LText;
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
        static char LText[150] = {0};
        strcpy(LText, "");
        snprintf(LText, sizeof(LText), "%sFlowStat:%s", LText, FlowStatusToStr(Header->flow_status) );
        snprintf(LText, sizeof(LText), "%sFrameId:%s", LText, IsoTpFrameIdToStr(Header->frame_id));
        snprintf(LText, sizeof(LText), "%sBlkSize:%u", LText, Header->block_size);
        snprintf(LText, sizeof(LText), "%sSepTime:%s", LText,  SepTimeToStr(Header->min_sep_time));
        LOG_INFO(ISO_TP, "%s",LText);
        res = true;
    }
    return res;
}

static const char* FirstFrameToStr(const IsoTpFrame_t* const Frame) {
    static char LText[150] = {0};
    IsoTpFirstFrameHeader_t Header;
    Header.buff[0] = Frame->data[0];
    Header.buff[1] = Frame->data[1];
    Header.word = reverse_byte_order_uint16(Header.word);
    uint16_t expected_size = MASK_12BIT & Header.word;
    sprintf(LText, "FirstFrame:1,DL:%u,%s", expected_size, ArrayToStr(&Frame->data[2], 6));
    return LText;
}

static const char* FlowControlToStr(const IsoTpFrame_t* const Frame) {
    static char LText[150] = {0};
    if(Frame) {
        strcpy(LText, "FlowControl:3,");
        snprintf(LText, sizeof(LText), "%sFlowStat:%s,", LText, FlowStatusToStr(Frame->FlowControlHeader.flow_status) );
        snprintf(LText, sizeof(LText), "%sBS:%u", LText, Frame->FlowControlHeader.block_size);
        snprintf(LText, sizeof(LText), "%sSepTime:%s,", LText, SepTimeToStr(Frame->FlowControlHeader.min_sep_time));
        snprintf(LText, sizeof(LText), "%sData:%s,", LText, ArrayToStr(&Frame->data[3], 5)   );
    }
    return LText;
}

const char* IsoTpFrameToStr(const IsoTpFrame_t* const Frame) {
    static char LText[150] = {0};
    if(Frame) {
        strcpy(LText, "?");
        uint8_t frame_code = 0x0F & (Frame->data[0] >> 4);
        switch(frame_code) {
        case ISO_TP_FRAME_CODE_SINGLE_FRAME:
            sprintf(LText, "%s,0x%s", SingleFrameToStr(Frame), FrameDataToStr(Frame));
            break;
        case ISO_TP_FRAME_CODE_FIRST_FRAME:
            sprintf(LText, "%s,0x%s", FirstFrameToStr(Frame), FrameDataToStr(Frame));
            break;
        case ISO_TP_FRAME_CODE_CONSECUTIVE_FRAME:
            sprintf(LText, "%s,0x%s", ConsecutiveFrameToStr(Frame), FrameDataToStr(Frame));
            break;
        case ISO_TP_FRAME_CODE_FLOW_CONTOL:
            sprintf(LText, "%s,0x%s", FlowControlToStr(Frame), FrameDataToStr(Frame));
            break;
        default: {
           strcpy(LText, "NotIsoTpFrame");
        }  break;
        }
    }
    return LText;
}

const char* IsoToConsecutiveToStr(const IsoTpHandle_t* const Node) {
    static char LText[150] = {0};
    if(Node) {
        strcpy(LText, "");
        snprintf(LText, sizeof(LText), "%sN:%u,", LText, Node->num);
        snprintf(LText, sizeof(LText), "%s%s,", LText, ProgressToStr(Node->tx_done_bytes, Node->tx_size));
        snprintf(LText, sizeof(LText), "%sRest:%u Byte,", LText, Node->tx_rest_byte);
        snprintf(LText, sizeof(LText), "%stxSN:%u,", LText, Node->tx_sn);
    }
    return LText;
}

bool iso_tp_buff_print(uint8_t num, uint32_t size, IsoTpBuff_t buff) {
    bool res = false;
    IsoTpHandle_t* Node = IsoTpGetNode(num);
    if(Node) {
        res = iso_tp_buff_print_ll(Node, size, buff);
    }
    return res;
}

const char* IsoTpConfigToStr(const IsoTpConfig_t* const Config) {
    static char LText[150] = {0};
    if(Config) {
        strcpy(LText, "");
        snprintf(LText, sizeof(LText), "%sN:%u,", LText, Config->num);
        snprintf(LText, sizeof(LText), "%sIF:%s,", LText, InterfaceTypeToStr(Config->interface_if));
        snprintf(LText, sizeof(LText), "%sAddrType:%s,", LText, IsoTpAddressingToStr(Config->addressing));
        snprintf(LText, sizeof(LText), "%sMyId:0x%x,", LText, Config->my_id);
        snprintf(LText, sizeof(LText), "%sSepTime:%f s,", LText, Config->separation_time_s);
        snprintf(LText, sizeof(LText), "%sBlockSize:%u,", LText, Config->block_size);
        snprintf(LText, sizeof(LText), "%s%s,", LText, Config->name);
        snprintf(LText, sizeof(LText), "%sUDS%d,", LText, Config->uds_num);
    }
    return LText;
}
