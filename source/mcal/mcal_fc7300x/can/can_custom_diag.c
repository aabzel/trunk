#include "can_custom_diag.h"

#include "array_diag.h"
#include "can_mcal.h"
#include "common_diag.h"
#include "data_utils.h"
#include "debugger.h"
#include "diag_includes.h"
#include "byte_utils.h"
#include "num_to_str.h"
#include "std_includes.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"
#include "fc7300x_misc.h"

const Reg32_t CanReg[] = {
    {
        .num = 1,
        .offset = 0,
        .name = "MCR",
        .valid = true,
    },
    {
        .num = 2,
        .offset = 4,
        .name = "CTRL1",
        .valid = true,
    },
    {
        .num = 3,
        .offset = 8,
        .name = "TIMER",
        .valid = true,
    },
    {
        .num = 6,
        .offset = 0x18,
        .name = "RX15MASK",
        .valid = true,
    },
    {
        .num = 7,
        .offset = 0x1c,
        .name = "ECR",
        .valid = true,
    },
    {
        .num = 8,
        .offset = 0x20,
        .name = "ESR1",
        .valid = true,
    },
    {
        .num = 9,
        .offset = 0x24,
        .name = "IMASK2",
        .valid = true,
    },
    {
        .valid = true,
        .num = 10,
        .offset = 0x24,
        .name = "IMASK2",
    },
    {
        .valid = true,
        .num = 11,
        .offset = 0x28,
        .name = "IMASK1",
    },
    {
        .valid = true,
        .num = 12,
        .offset = 0x2c,
        .name = "IFLAG2",
    },
    {
        .valid = true,
        .num = 13,
        .offset = 0x30,
        .name = "IFLAG1",
    },
    {
        .valid = true,
        .num = 14,
        .offset = 0x34,
        .name = "CTRL2",
    },
    {
        .valid = true,
        .num = 15,
        .offset = 0x38,
        .name = "ESR2",
    },
    {
        .valid = true,
        .num = 16,
        .offset = 0x44,
        .name = "CRCR",
    },
    {
        .valid = true,
        .num = 17,
        .offset = 0x48,
        .name = "RXFGMASK",
    },
    {
        .valid = true,
        .num = 18,
        .offset = 0x4c,
        .name = "RXFIR",
    },
    {
        .valid = true,
        .num = 19,
        .offset = 0x50,
        .name = "CBT",
    },

    {
        .valid = true,
        .num = 24,
        .offset = 0xae0,
        .name = "MECR",
    },
    {
        .valid = true,
        .num = 25,
        .offset = 0xae4,
        .name = "ERRIAR",
    },
    {
        .valid = true,
        .num = 26,
        .offset = 0xae8,
        .name = "ERRIDPR",
    },
    {
        .valid = true,
        .num = 27,
        .offset = 0xaec,
        .name = "ERRIPPR",
    },
    {
        .valid = true,
        .num = 28,
        .offset = 0xaf0,
        .name = "RERRAR",
    },
    {
        .valid = true,
        .num = 29,
        .offset = 0xaf4,
        .name = "RERRDR",
    },
    {
        .valid = true,
        .num = 30,
        .offset = 0xaf8,
        .name = "RERRSYNR",
    },
    {
        .valid = true,
        .num = 31,
        .offset = 0xafc,
        .name = "ERRSR",
    },
    {
        .valid = true,
        .num = 32,
        .offset = 0xb00,
        .name = "CTRL1_PN",
    },
    {
        .valid = true,
        .num = 33,
        .offset = 0xb04,
        .name = "CTRL2_PN",
    },
    {
        .valid = true,
        .num = 34,
        .offset = 0xb08,
        .name = "WU_MTC",
    },
    {
        .valid = true,
        .num = 35,
        .offset = 0xb0c,
        .name = "FLT_ID1",
    },
    {
        .valid = true,
        .num = 36,
        .offset = 0xb10,
        .name = "FLT_DLC",
    },
    {
        .valid = true,
        .num = 37,
        .offset = 0xb14,
        .name = "PL1_LO",
    },
    {
        .valid = true,
        .num = 38,
        .offset = 0xb18,
        .name = "PL1_HI",
    },
    {
        .valid = true,
        .num = 39,
        .offset = 0xb1c,
        .name = "FLT_ID2_IDMASK",
    },
    {
        .valid = true,
        .num = 40,
        .offset = 0xb20,
        .name = "PL2_PLMASK_LO",
    },
    {
        .valid = true,
        .num = 41,
        .offset = 0xb24,
        .name = "PL2_PLMASK_HI",
    },
    {
        .valid = true,
        .num = 42,
        .offset = 0xbf0,
        .name = "EPRS",
    },
    {
        .valid = true,
        .num = 43,
        .offset = 0xbf4,
        .name = "ENCBT",
    },
    {
        .valid = true,
        .num = 44,
        .offset = 0xbf8,
        .name = "EDCBT",
    },
    {
        .valid = true,
        .num = 45,
        .offset = 0xbfc,
        .name = "ETDC",
    },
    {
        .valid = true,
        .num = 46,
        .offset = 0xc00,
        .name = "FDCTRL",
    },
    {
        .valid = true,
        .num = 47,
        .offset = 0xc04,
        .name = "FDCBT",
    },
    {
        .valid = true,
        .num = 48,
        .offset = 0xc08,
        .name = "FDCRC",
    },
    {
        .valid = true,
        .num = 49,
        .offset = 0xc0c,
        .name = "ERFCR",
    },
    {
        .valid = true,
        .num = 50,
        .offset = 0xc10,
        .name = "ERFIER",
    },
    {
        .valid = true,
        .num = 51,
        .offset = 0xc14,
        .name = "ERFSR",
    },
    {
        .num = 4,
        .offset = 0x10,
        .name = "RXMGMASK",
        .valid = true,
    },
    {
        .num = 5,
        .offset = 0x14,
        .name = "RX14MASK",
        .valid = true,
    },
    {
        .valid = true,
        .num = 20,
        .offset = 0x68,
        .name = "IMASK4",
    },
    {
        .valid = true,
        .num = 21,
        .offset = 0x6c,
        .name = "IMASK3",
    },
    {
        .valid = true,
        .num = 22,
        .offset = 0x70,
        .name = "IFLAG4",
    },
    {
        .valid = true,
        .num = 23,
        .offset = 0x74,
        .name = "IFLAG3",
    },
};

uint32_t can_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(CanReg);
    return cnt;
}

bool CanDiagRegCBT(uint8_t num, CAN_Type* const CANx) {
    bool res = false;
    if(CANx) {
        CanRegCBT_t Reg;
        Reg.qword = CANx->CBT;
        LOG_WARNING(CAN, "CAN%u,CBT:0x%x=%s", num, CANx->CBT, utoa_bin32(CANx->CBT));
        LOG_INFO(CAN, "EPROPSEG:%u %u", Reg.EPROPSEG, Reg.EPROPSEG + 1);
        LOG_INFO(CAN, "EPSEG1:%u %u", Reg.EPSEG1, Reg.EPSEG1 + 1);
        LOG_INFO(CAN, "EPSEG2:%u %u", Reg.EPSEG2, Reg.EPSEG2 + 1);
        LOG_INFO(CAN, "ERJW:%u %u", Reg.ERJW, Reg.ERJW + 1);
        LOG_INFO(CAN, "EPRESDIV:%u", Reg.EPRESDIV);
        LOG_INFO(CAN, "BTF:%u", Reg.BTF);
        res = true;
    }
    return res;
}

bool CanDiagRegCAN_FDCTRL(uint8_t num, const CAN_Type* const CANx) {
    bool res = false;
    if(CANx) {
        CanRegCAN_FDCTRL_t Reg;
        Reg.qword = CANx->FDCTRL;
        LOG_WARNING(CAN, "CAN%u,FDCTRL:0x%x=%s", num, CANx->FDCTRL, utoa_bin32(CANx->FDCTRL));
        LOG_INFO(CAN, "TDCVAL:%u", Reg.TDCVAL);
        LOG_INFO(CAN, "TDCOFF:%u", Reg.TDCOFF);
        LOG_INFO(CAN, "TDCFAIL:%u", Reg.TDCFAIL);
        LOG_INFO(CAN, "TDCEN:%u", Reg.TDCEN);
        LOG_INFO(CAN, "MBDSR0:%u", Reg.MBDSR0);
        LOG_INFO(CAN, "FDRATE:%u", Reg.FDRATE);
        res = true;
    }
    return res;
}

bool CanDiagRegCTRL1(uint8_t num, CAN_Type* const CANx) {
    bool res = false;
    if(CANx) {
        uint32_t one_bit_diration_quant = 0;
        CanRegCTRL1_t Reg;
        Reg.qword = CANx->CTRL1;

        one_bit_diration_quant += Reg.PROPSEG + 1;
        one_bit_diration_quant += Reg.PSEG1 + 1;
        one_bit_diration_quant += Reg.PSEG2 + 1;
        one_bit_diration_quant += Reg.RJW + 1;

        LOG_WARNING(CAN, "CAN%u,CTRL1:0x%x=%s", num, CANx->CTRL1, utoa_bin32(CANx->CTRL1));
        LOG_INFO(CAN, "PRESDIV:%u,PrescDivFact:%u", Reg.PRESDIV, Reg.PRESDIV + 1);
        LOG_INFO(CAN, "RJW:%u,ResyncJumpWidth:%u quant", Reg.RJW, Reg.RJW + 1);
        LOG_INFO(CAN, "PSEG1:%u,PhaSeg1:%u quant", Reg.PSEG1, Reg.PSEG1 + 1);
        LOG_INFO(CAN, "PSEG2:%u,PhaSeg2:%u quant", Reg.PSEG2, Reg.PSEG2 + 1);
        LOG_INFO(CAN, "PROPSEG:%u, PropSeg:%u", Reg.PROPSEG, Reg.PROPSEG + 1);

        LOG_INFO(CAN, "LOM:%u", Reg.LOM);
        LOG_INFO(CAN, "LBUF:%u", Reg.LBUF);
        LOG_INFO(CAN, "TSYN:%u", Reg.TSYN);
        LOG_INFO(CAN, "BOFFREC:%u", Reg.BOFFREC);
        LOG_INFO(CAN, "SMP:%u", Reg.SMP);
        LOG_INFO(CAN, "RWRNMSK:%u", Reg.RWRNMSK);
        LOG_INFO(CAN, "TWRNMSK:%u", Reg.TWRNMSK);
        LOG_INFO(CAN, "LPB:%u", Reg.LPB);
        LOG_INFO(CAN, "CLKSRC:%u", Reg.CLKSRC);
        LOG_INFO(CAN, "ERRMSK:%u", Reg.ERRMSK);
        LOG_INFO(CAN, "BOFFMSK:%u", Reg.BOFFMSK);
        LOG_WARNING(CAN, "Prescaler:%u", Reg.PRESDIV + 1);
        LOG_WARNING(CAN, "OneBitTime:%u quant", one_bit_diration_quant);
        res = true;
    }
    return res;
}

static const char* CanMoveInfoToStr(bool status) {
    const char* name = "?";
    switch((uint8_t)status) {
    case false:
        name = "-";
        break;
    case true:
        name = "Done";
        break;
    }
    return name;
}

/*Wakeup Message Buffers (WMBs)
 Pretended Networking Enable
 PNET_EN must be 1
 in CAN MCR Register
 */
bool can_diag_wakeup_message_buffers(uint8_t num) {
    bool res = false;
    LOG_INFO(CAN, "CAN%u,DiagMailBox", num);

    static const table_col_t cols[] = {
        {6, "CAN"}, {5, "BfNum"}, {12, "ID"}, {5, "DLC"}, {5, "IDE"}, {5, "SRR"}, {5, "RTR"}, {20, "data"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t i = 0;
    for(i = 0; i < 4; i++) {
        const CanInfo_t* Info = CanGetInfo(num);
        if(Info) {
            uint32_t id = MASK_28BIT & Info->CANx->WMB[i].WMBn_ID;
            uint8_t data[8] = {0};
            uint32_t wmbn_dxx = Info->CANx->WMB[i].WMBn_D03;
            data[0] = 0x000000FF & (wmbn_dxx >> 24);
            data[1] = 0x000000FF & (wmbn_dxx >> 16);
            data[2] = 0x000000FF & (wmbn_dxx >> 8);
            data[3] = 0x000000FF & (wmbn_dxx >> 0);

            wmbn_dxx = Info->CANx->WMB[i].WMBn_D47;

            data[4] = 0x000000FF & (wmbn_dxx >> 24);
            data[5] = 0x000000FF & (wmbn_dxx >> 16);
            data[6] = 0x000000FF & (wmbn_dxx >> 8);
            data[7] = 0x000000FF & (wmbn_dxx >> 0);
            char text[150] = {0};

            strcpy(text, TSEP);
            CanRegWMB_CS_t Reg;
            Reg.qword = Info->CANx->WMB[i].WMBn_CS;
            snprintf(text, sizeof(text), "%s CAN%u " TSEP, text, num);
            snprintf(text, sizeof(text), "%s %3u " TSEP, text, i);
            snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, id);
            snprintf(text, sizeof(text), "%s %5u " TSEP, text, Reg.DLC);
            snprintf(text, sizeof(text), "%s %5u " TSEP, text, Reg.IDE);
            snprintf(text, sizeof(text), "%s %5u " TSEP, text, Reg.SRR);
            snprintf(text, sizeof(text), "%s %5u " TSEP, text, Reg.RTR);
            snprintf(text, sizeof(text), "%s %18s " TSEP, text, ArrayToStr(data, 8));
            cli_printf("%s" CRLF, text);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool can_diag_mail_box(uint8_t num, char* key_word1, char* key_word2) {
    bool res = false;
    LOG_INFO(CAN, "CAN%u,DiagMailBox", num);

    static const table_col_t cols[] = {
        {6, "CAN"}, {5, "idx"}, {8, "ret"}, {10, "state"}, {5, "Int"}, {6, "Mov"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t mb_idx = 0;
    for(mb_idx = 0; mb_idx < FEATURE_CAN_MAX_MB_NUM; mb_idx++) {
        char text[150] = {0};
        strcpy(text, TSEP);
        status_t ret = STATUS_ERROR;
        ret = FLEXCAN_DRV_GetTransferStatus(num, (uint8_t)mb_idx);
        bool mb_int = can_message_buffer_interrupt_get(num, mb_idx);
        bool move_info = can_move_info_get(num, mb_idx);

        snprintf(text, sizeof(text), "%s CAN%u " TSEP, text, num);
        snprintf(text, sizeof(text), "%s %3u " TSEP, text, mb_idx);

        snprintf(text, sizeof(text), "%s 0x%04x " TSEP, text, ret);
        snprintf(text, sizeof(text), "%s %8s " TSEP, text, RetToStr(ret));
        snprintf(text, sizeof(text), "%s %3s " TSEP, text, OnOffToStr(mb_int));
        snprintf(text, sizeof(text), "%s %4s " TSEP, text, CanMoveInfoToStr(move_info));

        res = is_contain(text, key_word1, key_word2);
        if(res) {
            cli_printf("%s" CRLF, text);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool can_diag_low_level(uint8_t num, char* const keyword) {
    bool res = false;

    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        res = CanDiagRegCTRL1(num, Info->CANx);
        res = CanDiagRegCBT(num, Info->CANx);
        res = CanDiagRegCAN_FDCTRL(num, Info->CANx);
    }

    uint32_t error_status = FLEXCAN_DRV_GetErrorStatus(num);
    LOG_INFO(CAN, "CAN%u,ESR1:0x%x=%s", num, error_status, ESR1ToStr(error_status));

    flexcan_time_segment_t time_segment = {0};
    FLEXCAN_DRV_GetBitrate(num, &time_segment);
    LOG_INFO(CAN, "CAN%u,BitRate:%s", num, FlaxCanBitRateStr(&time_segment));

    FLEXCAN_DRV_GetBitrateFD(num, &time_segment);
    LOG_INFO(CAN, "CAN_FD%u,BitRate:%s", num, FlaxCanBitRateStr(&time_segment));

    bool TDCFail = FLEXCAN_DRV_GetTDCFail(num);
    uint8_t TDC = FLEXCAN_DRV_GetTDCValue(num);
    LOG_INFO(CAN, "CAN%u,TDC:%u,TdcFail:%s", num, TDC, OnOffToStr(TDCFail));

    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        LOG_INFO(CAN, "CAN%u,Rx:%s", num, FlexCanMessageToStr(&Node->RxMsg));
    }
    return res;
}

bool can_raw_reg_diag(uint8_t num) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        LOG_INFO(CAN, "CAN%u,Base:0x%p", num, Info->CANx);
        uint32_t reg_cnt = can_reg_cnt();
        res = debug_raw_reg_diag(CAN, (uint32_t)Info->CANx, CanReg, reg_cnt);
    }
    return res;
}

const char* FlexCanMessageToStr(const flexcan_msgbuff_t* const MsgBuff) {
    static char text[300] = {0};
    if(MsgBuff) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sMsgId:0x%x,", text, MsgBuff->msgId);
        snprintf(text, sizeof(text), "%sDatLen:%u bytes,", text, MsgBuff->dataLen);
        snprintf(text, sizeof(text), "%sCS:0x%x,", text, MsgBuff->cs);
        snprintf(text, sizeof(text), "%sData:[%s],", text, MsgBuff->data);
        snprintf(text, sizeof(text), "%sDataHex:[%s],", text, ArrayToStr(MsgBuff->data, MsgBuff->dataLen));
    }
    return text;
}

const char* FlaxCanBitRateStr(const flexcan_time_segment_t* const bitrate) {
    static char text[150] = {0};
    if(bitrate) {
        uint32_t prescaler = 0;
        prescaler += bitrate->rJumpwidth;
        prescaler += bitrate->propSeg;
        prescaler += bitrate->phaseSeg1;
        prescaler += bitrate->phaseSeg2;
        prescaler *= (bitrate->preDivider + 1);
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sPsc:%u,", text, prescaler);
        // snprintf(text, sizeof(text), "%Divider:%u,", text, bitrate->preDivider+1);
        snprintf(text, sizeof(text), "%spreDiv:%u,", text, bitrate->preDivider);
        snprintf(text, sizeof(text), "%sPropSeg:%u,", text, bitrate->propSeg);
        snprintf(text, sizeof(text), "%sPhaSeg1:%u,", text, bitrate->phaseSeg1);
        snprintf(text, sizeof(text), "%sPhaSeg2:%u,", text, bitrate->phaseSeg2);
        snprintf(text, sizeof(text), "%sJumpWidth:%u", text, bitrate->rJumpwidth);
    }
    return text;
}

const char* ESR1ToStr(uint32_t error_status) {
    static char text[300] = {0};
    CanRegEsr_t Reg;
    Reg.qword = error_status;
    strcpy(text, "");
    if(error_status) {
        snprintf(text, sizeof(text), "%sESR1:0x%08x,", text, Reg.qword);
        snprintf(text, sizeof(text), "%sWAKINT:%u,", text, Reg.WAKINT);
        snprintf(text, sizeof(text), "%sERRINT:%u,", text, Reg.ERRINT);
        snprintf(text, sizeof(text), "%sBOFFINT:%u,", text, Reg.BOFFINT);
        snprintf(text, sizeof(text), "%sRX:%u,", text, Reg.RX);
        snprintf(text, sizeof(text), "%sFLTCONF:%u,", text, Reg.FLTCONF);
        snprintf(text, sizeof(text), "%sTX:%u,", text, Reg.TX);
        snprintf(text, sizeof(text), "%sIDLE:%u,", text, Reg.IDLE);
        snprintf(text, sizeof(text), "%sRXWRN:%u,", text, Reg.RXWRN);
        snprintf(text, sizeof(text), "%sTXWRN:%u,", text, Reg.TXWRN);
        snprintf(text, sizeof(text), "%sSTFERR:%u,", text, Reg.STFERR);
        snprintf(text, sizeof(text), "%sFRMERR:%u,", text, Reg.FRMERR);
        snprintf(text, sizeof(text), "%sCRCERR:%u,", text, Reg.CRCERR);
        snprintf(text, sizeof(text), "%sACKERR:%u,", text, Reg.ACKERR);
        snprintf(text, sizeof(text), "%sBIT0ERR:%u,", text, Reg.BIT0ERR);
        snprintf(text, sizeof(text), "%sBIT1ERR:%u,", text, Reg.BIT1ERR);
        snprintf(text, sizeof(text), "%sRWRNINT:%u,", text, Reg.RWRNINT);
        snprintf(text, sizeof(text), "%sTWRNINT:%u,", text, Reg.TWRNINT);
        snprintf(text, sizeof(text), "%sSYNCH:%u,", text, Reg.SYNCH);
        snprintf(text, sizeof(text), "%sBOFFDOENINT:%u,", text, Reg.BOFFDOENINT);
        snprintf(text, sizeof(text), "%sERRINT_FAST:%u,", text, Reg.ERRINT_FAST);
        snprintf(text, sizeof(text), "%sERROVR:%u,", text, Reg.ERROVR);
        snprintf(text, sizeof(text), "%sSTFERR_FAST:%u,", text, Reg.STFERR_FAST);
        snprintf(text, sizeof(text), "%sFRMERR_FAST:%u,", text, Reg.FRMERR_FAST);
        snprintf(text, sizeof(text), "%sCRCERR_FAST:%u,", text, Reg.CRCERR_FAST);
        snprintf(text, sizeof(text), "%sBIT0ERR_FAST:%u,", text, Reg.BIT0ERR_FAST);
        snprintf(text, sizeof(text), "%sBIT1ERR_FAST:%u,", text, Reg.BIT1ERR_FAST);
    }
    return text;
}

static const char* CanCodeToStr(CanCode_t code){
    char* name = "?";
    switch(code){
        case CAN_CODE_INACTIVE :name = "INACT"; break;
        case CAN_CODE_INACTIVE_2:name = "INACT"; break;
        case CAN_CODE_EMPTY: name = "EMPTY";break;
        case CAN_CODE_FULL:name = "FULL"; break;
        case CAN_CODE_OVERRUN :name = "OVERRUN"; break;
        case CAN_CODE_RANSWER:name = "RANSWER"; break;
        case CAN_CODE_BUSY : name = "BUSY";break;
        case CAN_CODE_ABORT :name = "ABORT"; break;
        case CAN_CODE_DATA: name = "DATA";break;
        case CAN_CODE_TANSWER :name = "TANSWER"; break;
        default: name = "?"; break;
    }
    return name ;
}



const char* CanMessageBufferToStr(const  CanMessageBufferLayOut_t* const LayOut){
    static char text[300] = {0};
    if(LayOut) {
        strcpy(text, "");
        if(LayOut->TIME_STAMP) {
            snprintf(text, sizeof(text), "%sTimeStamp:%u,", text, LayOut->TIME_STAMP);
            snprintf(text, sizeof(text), "%sID:0x%x,", text, LayOut->ID_EXTENDED);
            snprintf(text, sizeof(text), "%sCODE:%s,", text, CanCodeToStr(LayOut->CODE));
            snprintf(text, sizeof(text), "%sDLC:%u,", text, LayOut->DLC);
            snprintf(text, sizeof(text), "%sRTR:%u,", text, LayOut->RTR);
            snprintf(text, sizeof(text), "%sIDE:%u,", text, LayOut->IDE);
            snprintf(text, sizeof(text), "%sSRR:%u,", text, LayOut->SRR);
            snprintf(text, sizeof(text), "%sESI:%u,", text, LayOut->ESI);
            snprintf(text, sizeof(text), "%sBRS:%u,", text, LayOut->BRS);
            snprintf(text, sizeof(text), "%sEDL:%u,", text, LayOut->EDL);
            snprintf(text, sizeof(text), "%sPRIO:%u,", text, LayOut->PRIO);
            snprintf(text, sizeof(text), "%sDAT:%s,", text, ArrayToStr(LayOut->data,64));
        }
    }
    return text;
}

static uint8_t CanDlcToSize(CanDlc_t DLC) {
	uint8_t size = 0 ;
    switch(DLC){
        case CAN_DLC_0 :   size=  0   ; break;
        case CAN_DLC_1 :   size=  1   ; break;
        case CAN_DLC_2 :   size=  2   ; break;
        case CAN_DLC_3 :   size=  3   ; break;
        case CAN_DLC_4 :   size=  4   ; break;
        case CAN_DLC_5 :   size=  5   ; break;
        case CAN_DLC_6 :   size=  6   ; break;
        case CAN_DLC_7 :   size=  7   ; break;
        case CAN_DLC_8 :   size=  8   ; break;
        case CAN_DLC_12:   size = 12  ; break;
        case CAN_DLC_16:   size = 16   ; break;
        case CAN_DLC_20:   size = 20   ; break;
        case CAN_DLC_24:   size = 24   ; break;
        case CAN_DLC_32:   size = 32   ; break;
        case CAN_DLC_48:   size = 48  ; break;
        case CAN_DLC_64:   size = 64   ; break;

        default :size = 0 ;  break;
    }
    return size;
}

static bool can_diag_message_buffer_64(CanHandle_t* Node) {
    bool res = false;
    CanMessageBuffer_t* MessageBuffer = (CanMessageBuffer_t*)(Node->CANx->RAM);
    cli_printf(CRLF);
    uint32_t i = 0;
    static const table_col_t cols[] = {
        {7, "TimeStamp"},
        {12, "ID"},
        {9, "CODE"},
        {4, "Size"},
        {4, "RTR"},
        {4, "SRR"},
        {4, "BRS"},
        {4, "IDE"},
        {4, "ESI"},
        {4, "EDL"},
        {4, "PRIO"},
        {64, "DAT"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(i = 0; i < 14; i++) {
        CanMessageBufferLayOut_t MesgBufLayOut={0};
        memcpy(MesgBufLayOut.buf, MessageBuffer->MbPayload64[i].buff, 8);
        uint32_t j = 0;
        for(j=2;j<16;j++) {
        	MesgBufLayOut.qword[j] = reverse_byte_order_uint32(MessageBuffer->MbPayload64[i].qword[j]);
        }

        char text[300] = {0};
        strcpy(text, TSEP);
        snprintf(text, sizeof(text), "%s %5u " TSEP, text, MesgBufLayOut.TIME_STAMP);
        snprintf(text, sizeof(text), "%s 0x%08x " TSEP, text, MesgBufLayOut.ID_EXTENDED);
        snprintf(text, sizeof(text), "%s %7s " TSEP, text, CanCodeToStr(MesgBufLayOut.CODE));
        snprintf(text, sizeof(text), "%s %2u " TSEP, text, CanDlcToSize(MesgBufLayOut.DLC));
        snprintf(text, sizeof(text), "%s %2u " TSEP, text, MesgBufLayOut.RTR);
        snprintf(text, sizeof(text), "%s %2u " TSEP, text, MesgBufLayOut.SRR);
        snprintf(text, sizeof(text), "%s %2u " TSEP, text, MesgBufLayOut.BRS);
        snprintf(text, sizeof(text), "%s %2u " TSEP, text, MesgBufLayOut.IDE);
        snprintf(text, sizeof(text), "%s %2u " TSEP, text, MesgBufLayOut.ESI);
        snprintf(text, sizeof(text), "%s %2u " TSEP, text, MesgBufLayOut.EDL);
        snprintf(text, sizeof(text), "%s %2u " TSEP, text, MesgBufLayOut.PRIO);
        snprintf(text, sizeof(text), "%s %s " TSEP, text,  MesgBufLayOut.data );
        //snprintf(text, sizeof(text), "%s %s " TSEP, text,  ArrayToStr(MesgBufLayOut.data,32) );
        if(MesgBufLayOut.TIME_STAMP) {
            cli_printf("%s" CRLF, text);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    //cli_printf(CRLF);

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

static bool can_diag_message_buffer_8(CanHandle_t* Node) {
    bool res = false;
    CanMessageBuffer_t* MessageBuffer = (CanMessageBuffer_t*)(Node->CANx->RAM);
    cli_printf(CRLF);
    uint32_t i = 0;
    for(i = 0; i < 64; i++) {
        cli_printf("%2u:%s" CRLF, i, ArrayToStr(MessageBuffer->MbPayload8[i].buff, 16));
    }
    cli_printf(CRLF);
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
bool can_diag_ram(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        uint32_t ram_offset =((uint32_t) Node->CANx->RAM )- ((uint32_t) Node->CANx);
        LOG_INFO(CAN, "CAN%u->RAM, Offset:0x%08x", num, ram_offset);
#if 0
        cli_printf(CRLF);
        uint32_t i = 0;
        for(i = 0; i < 256; i++) {
            cli_printf("%08x", Node->CANx->RAM[i]);
        }
        cli_printf(CRLF);
#endif

        CanRegCAN_FDCTRL_t Reg;
        Reg.qword = Node->CANx->FDCTRL;
        res = can_diag_message_buffer(Node, Reg.MBDSR0);

        uint8_t* ExtraMessageBuffer = (uint8_t*)(((uint32_t)Node->CANx) + 0x1000);
        LOG_INFO(CAN, "CAN%u,ExtraMessageBuffer,PhyAddr:0x%p", num, ExtraMessageBuffer);
#if 0
        cli_printf(CRLF);
        for(i=0;i<2048;i++){
            uint8_t byte_data = *(ExtraMessageBuffer+i);
            cli_printf("%08x",byte_data);
        }
        cli_printf(CRLF);
#endif
    }
    return res;
}
