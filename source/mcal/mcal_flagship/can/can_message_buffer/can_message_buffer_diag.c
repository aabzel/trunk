#include "can_message_buffer_diag.h"

#include "array_diag.h"
#include "log.h"
#include "byte_utils.h"
#include "writer_config.h"
#include "table_utils.h"
#include "std_includes.h"
#include "can_message_buffer.h"
#include "diag_inc.h"
#include "common_diag.h"
#include "str_utils.h"
#include "connectivity_diag.h"
#include "can_mcal.h"

static const char* CanCodeToStr(const CanCode_t code) {
    char* name = "?";
    switch(code) {
        case CAN_CODE_INACTIVE:     name = "INACT_Rx";    break;
        case CAN_CODE_INACTIVE_2:   name = "INACT_Tx";    break;
        case CAN_CODE_EMPTY:        name = "EMPTY";       break;
        case CAN_CODE_FULL:         name = "FULL";        break;
        case CAN_CODE_OVERRUN:      name = "OVERRUN";     break;
        case CAN_CODE_RANSWER:      name = "RANSWER";     break;
        case CAN_CODE_BUSY:         name = "BUSY";        break;
        case CAN_CODE_ABORT:        name = "ABORT";       break;
        case CAN_CODE_DATA:         name = "TxDATA";      break;
        case CAN_CODE_TANSWER:      name = "TANSWER";     break;
        default:  name = "?";  break;
    }
    return name;
}

bool can_diag_wakeup_message_buffers(const uint8_t num) {
    bool res = false;
    return res;
}

static bool can_diag_message_buffer_8(CanHandle_t* const Node) {
    bool res = false;
    CanMessageBuffer_t* MessageBuffer = (CanMessageBuffer_t*)(Node->CANx->RAM);

    cli_printf(CRLF);
    uint8_t maxmb = 0;
    res = can_last_message_buffer_number_get(Node->num, &maxmb);
    LOG_INFO(CLK,"maxmb:%u",maxmb);
    static const table_col_t cols[] = {
        {4, "MB"},
        {10, "IDstd"}, {12, "IDext"}, {10, "CODE"}, {4, "EDL"},  {5, "IDE"},
        {4, "Size"}, {5, "BRS"},
        {7, "time_stamp"},
        {6, "ESI"},    {4, "RTR"},    {4, "SRR"},   {4, "PRIO"}, {20, "DAT"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t i = 0;
    for(i = 0; i < maxmb / 4; i++) {
        CanMessageBufferLayOut_t MesgBufLayOut = {0};
        memcpy(MesgBufLayOut.buf, MessageBuffer->MbPayload8[i].buff, 8);
        uint32_t j = 0;
        for(j = 2; j < 4; j++) {
            MesgBufLayOut.dword[j] = reverse_byte_order_uint32(MessageBuffer->MbPayload64[i].dword[j]);
        }

        char temp[300] = {0};
        strcpy(temp, TSEP);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, i);
        snprintf(temp, sizeof(temp), "%s 0x%06x " TSEP, temp, MesgBufLayOut.ID.STANDARD);
        snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, MesgBufLayOut.ID.EXTENDED);
        snprintf(temp, sizeof(temp), "%s %7s " TSEP, temp, CanCodeToStr(MesgBufLayOut.CODE));
        snprintf(temp, sizeof(temp), "%s %2s " TSEP, temp, CanEDLToStr(MesgBufLayOut.EDL));
        snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanIDEToStr(MesgBufLayOut.IDE));
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, CanDlcToSize(MesgBufLayOut.DLC));
        snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanBRSToStr(MesgBufLayOut.BRS));
        snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, MesgBufLayOut.TIME_STAMP);
        snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanESItoStr(MesgBufLayOut.ESI));
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.RTR);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.SRR);     // Substitute Remote Request
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.ID.PRIO); // Only valid for Tx mailboxes.
        snprintf(temp, sizeof(temp), "%s 0x%s " TSEP, temp, ArrayToStr(MesgBufLayOut.data, 8));
        // snprintf(temp, sizeof(temp), "%s %s " TSEP, temp,  MesgBufLayOut.data );
        // if(MesgBufLayOut.TIME_STAMP) {
        cli_printf("%s" CRLF, temp);
        //}
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    // cli_printf(CRLF);

    return res;
}

static bool can_diag_message_buffer_16(CanHandle_t* Node) {
    bool res = false;
    CanMessageBuffer_t* MessageBuffer = (CanMessageBuffer_t*)(Node->CANx->RAM);
    cli_printf(CRLF);
    uint32_t i = 0;
    for(i = 0; i < 42; i++) {
        cli_printf("%2u:%s" CRLF, i, ArrayToStr(MessageBuffer->MbPayload16[i].buff, 24));
    }
    cli_printf(CRLF);
    return res;
}

static bool can_diag_message_buffer_32(CanHandle_t* Node) {
    bool res = false;
    CanMessageBuffer_t* MessageBuffer = (CanMessageBuffer_t*)(Node->CANx->RAM);
    cli_printf(CRLF);
    uint32_t i = 0;
    for(i = 0; i < 24; i++) {
        cli_printf("%2u:%s" CRLF, i, ArrayToStr(MessageBuffer->MbPayload32[i].buff, 40));
    }
    cli_printf(CRLF);
    return res;
}

static bool can_diag_message_buffer_64(CanHandle_t* Node) {
    bool res = false;
    CanMessageBuffer_t* MessageBuffer = (CanMessageBuffer_t*)(Node->CANx->RAM);
    cli_printf(CRLF);
    uint32_t i = 0;
    static const table_col_t cols[] = {
        {7, "timeStamp"}, {12, "IDstd"}, {12, "IDext"}, {9, "CODE"}, {4, "Size"}, {4, "RTR"},  {4, "SRR"},
        {4, "BRS"},       {4, "IDE"},    {4, "ESI"},    {4, "EDL"},  {4, "PRIO"}, {64, "DAT"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(i = 0; i < 7; i++) {
        CanMessageBufferLayOut_t MesgBufLayOut = {0};
        memcpy(MesgBufLayOut.buf, MessageBuffer->MbPayload64[i].buff, 8);
        uint32_t j = 0;
        for(j = 2; j < 16; j++) {
            MesgBufLayOut.dword[j] = reverse_byte_order_uint32(MessageBuffer->MbPayload64[i].dword[j]);
        }

        char temp[300] = {0};
        strcpy(temp, TSEP);
        snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, MesgBufLayOut.TIME_STAMP);
        snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, MesgBufLayOut.ID.STANDARD);
        snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, MesgBufLayOut.ID.EXTENDED);
        snprintf(temp, sizeof(temp), "%s %7s " TSEP, temp, CanCodeToStr(MesgBufLayOut.CODE));
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, CanDlcToSize(MesgBufLayOut.DLC));
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.RTR);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.SRR);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.BRS);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.IDE);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.ESI);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.EDL);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, MesgBufLayOut.ID.PRIO); // Only valid for Tx mailboxes.
        snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, MesgBufLayOut.data);
        // snprintf(temp, sizeof(temp), "%s %s " TSEP, temp,  ArrayToStr(MesgBufLayOut.data,32) );
        // if(MesgBufLayOut.TIME_STAMP) {
        cli_printf("%s" CRLF, temp);
        //}
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    // cli_printf(CRLF);

    return res;
}

static bool can_diag_message_buffer(CanHandle_t* Node, uint32_t mbdsr0) {
    bool res = false;
    switch(mbdsr0) {
    case CAN_MESG_BUFF_DATA_SIZE_8_BYTE: {
        res = can_diag_message_buffer_8(Node);
    } break;
    case CAN_MESG_BUFF_DATA_SIZE_16_BYTE: {
        res = can_diag_message_buffer_16(Node);
    } break;
    case CAN_MESG_BUFF_DATA_SIZE_32_BYTE: {
        res = can_diag_message_buffer_32(Node);
    } break;
    case CAN_MESG_BUFF_DATA_SIZE_64_BYTE: {
        res = can_diag_message_buffer_64(Node);
    } break;
    default:
        res = false;
        break;
    }
    return res;
}

/*
 *

  The address range from offset 0x80 to 0x87F (2048 Byte) allocates
  the one-hundred-twenty-eight 128-bit (16 byte)
  message buffers (MBs).
  0x87F-0x80+1 =

  The memory area from 0x80 to 0x87F is used by the mailboxes.

  0x17FF-0x1000 +1 = 2048 byte
  The address range from offset 0x1000 to 0x17FF allocates an extra
  message buffer space that can   be used for CAN FD operation.
 */
bool can_diag_ram(const uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        LOG_INFO(CAN, "FLEXCAN_RAM_COUNT:%u", FLEXCAN_RAM_COUNT);
        uint32_t ram_offset = ((uint32_t)Node->CANx->RAM) - ((uint32_t)Node->CANx);
        LOG_INFO(CAN, "CAN%u->RAM,Offset:0x%X", num, ram_offset);
        cli_printf(CRLF);
#if 0
        uint32_t i = 0;
        for(i = 0; i < FLEXCAN_RAM_COUNT; i++) {
            cli_printf("%08x", Node->CANx->RAM[i]);
        }
        cli_printf(CRLF);

        res = array_u32_print(Node->CANx->RAM, FLEXCAN_RAM_COUNT);
#endif

        CanRegFDCTRL_t Reg;
        Reg.dword = Node->CANx->FDCTRL;
        res = can_diag_message_buffer(Node, Reg.MBDSR0);
    }
    return res;
}

const char* FlexCanMbSettingToStr(const FLEXCAN_MbSettingType* const Node) {
    memset(text, 0, sizeof(text));
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sDir:%u,", text, Node->bIsTxMB);
        snprintf(text, sizeof(text), "%sInt:%u,", text, Node->bEnMBInt);
        snprintf(text, sizeof(text), "%sRxID:0x%x,", text, Node->u32RxCanId);
        snprintf(text, sizeof(text), "%sRxIdMask:%u,", text, Node->u32RxCanIdMask);
        snprintf(text, sizeof(text), "%sRxFrameType:%u", text, Node->eRxFrameType);
    }
    return text;
}


bool can_diag_mail_box(const uint8_t num, char* key_word1, char* key_word2) {
    bool res = false;
    LOG_INFO(CAN, "CAN%u,DiagMailBox", num);

    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        static const table_col_t cols[] = {
            {6, "CAN"}, {5, "MBi"}, {5, "Dir"}, {6, "Flag"}, {5, "Int"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t mb_idx = 0;
        for(mb_idx = 0; mb_idx < 32; mb_idx++) {
            uint32_t flag = FLEXCAN_HWA_GetFlag1NoFifoFlag(Node->CANx, mb_idx);
            bool interrupt_mask = can_mailbox_interrupt_mask_get(num, (uint8_t)mb_idx);
            ConnectivitDir_t dir = can_mailbox_direction_get(num, mb_idx);

            char temp[150] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s CAN%u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, mb_idx);
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, ConnectivityDirectionToStr(dir));
            snprintf(temp, sizeof(temp), "%s %4u " TSEP, temp, flag);
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, OnOffToStr(interrupt_mask));

            res = is_contain(temp, key_word1, key_word2);
            if(res) {
                cli_printf("%s" CRLF, temp);
                res = true;
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        CanRegFDCTRL_t Reg;
        Reg.dword = Node->CANx->FDCTRL;
        res = can_diag_message_buffer(Node, Reg.MBDSR0);
    }

    return res;
}

const char* CanTxMessageToStr(const FLEXCAN_TxMsgType* const TxMsg) {
    memset(text, 0, sizeof(text));
    strcpy(text, "");
    if(TxMsg) {
        snprintf(text, sizeof(text), "%sID:0x%04x,", text, TxMsg->u32CanId);
        snprintf(text, sizeof(text), "%sMB:%u,", text, TxMsg->u8TxHandle);
        snprintf(text, sizeof(text), "%sSize:%u,", text, TxMsg->u32DataLen);
        snprintf(text, sizeof(text), "%sData:%s,", text, ArrayToStr(TxMsg->aData, TxMsg->u32DataLen));
        snprintf(text, sizeof(text), "%sFdEn:%u,", text, TxMsg->bEnFd);
        snprintf(text, sizeof(text), "%sBrs:%u,", text, TxMsg->bEnBrs);
    }
    return text;
}
