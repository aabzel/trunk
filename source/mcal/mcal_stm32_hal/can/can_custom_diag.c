#include "can_custom_diag.h"

#include "array_diag.h"
#include "byte_utils.h"
#include "can_mcal.h"
#include "can_misc.h"
#include "common_diag.h"
#include "connectivity_diag.h"
#include "data_utils.h"
#include "debugger.h"
#include "diag_inc.h"
#include "float_diag.h"
#include "log.h"
#include "num_to_str.h"
#include "std_includes.h"
#include "str_utils.h"
#include "can_core.h"
#include "table_utils.h"
#include "writer_config.h"

const char* CanStmModeToStr(const CanStmMode_t mode) {
    const char *name = "?";
    switch (mode) {
    case CAN_STM_MODE_NORMAL:
        name = "NORMAL";
        break;
    case CAN_STM_MODE_SLEEP:
        name = "SLEEP";
        break;
    case CAN_STM_MODE_FREEZE:
        name = "FREEZE";
        break;
    case CAN_STM_MODE_STANDBY:
        name = "STANDBY";
        break;
    case CAN_STM_MODE_SILENT:
        name = "SILENT";
        break;
    case CAN_STM_MODE_LOOPBACK:
        name = "LOOPBACK";
        break;
    case CAN_STM_MODE_LOOPBACK_SILENT:
        name = "LOOPBACK_SILENT";
        break;
    case CAN_STM_MODE_INITIALIZATION:
        name = "INITIALIZATION";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* CanFilterScaleToStr(const CanFilterScale_t scale) {
    const char *name = "?";
    switch (scale) {
    case CAN_FILTER_SCALE_16_BIT:
        name = "16";
        break;
    case CAN_FILTER_SCALE_32_BIT:
        name = "32";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* CanFilterModeToStr(const CanFilterMode_t mode) {
    const char *name = "?";
    switch (mode) {
    case CAN_FILTER_MODE_ID_MASK:
        name = "IdMask";
        break;
    case CAN_FILTER_MODE_LIST:
        name = "List";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* CanLastErrorCodeToStr(const CanLastErrorCode_t lec) {
    const char *token;
    switch (lec) {
    case CAN_LEC_OK:
        token = "NoError";
        break;
    case CAN_LEC_STUFF_ERROR:
        token = "Stuff";
        break;
    case CAN_LEC_FORM_ERROR:
        token = "Form";
        break;
    case CAN_LEC_ACKNOWLEDGMENT_ERROR:
        token = "AckError";
        break;
    case CAN_LEC_BIT_RECESSIVE_ERROR:
        token = "BitRecessive";
        break;
    case CAN_LEC_BIT_DOMINANT_ERROR:
        token = "BitDominant";
        break;
    case CAN_LEC_CRC_ERROR:
        token = "CrcError";
        break;
    case CAN_LEC_RESET:
        token = "None";
        break;
    default:
        token = "???";
        break;
    }
    return token;
}

bool can_diag_custom(void) {
    bool res = false;
    return res;
}

const char* CanInfoToToStr(const CanInfo_t *const Info) {
    memset(text, 0, sizeof(text));
    strcpy(text, "");
    if (Info) {
        snprintf(text, sizeof(text), "%sCAN%u,", text, Info->num);
        snprintf(text, sizeof(text), "%sPHY:0x%p,", text, Info->CANx);
        snprintf(text, sizeof(text), "%snvram_id:%u,", text, Info->nvram_id);
        snprintf(text, sizeof(text), "%sirq_n_tx:%u,", text, Info->irq_n_tx);
        snprintf(text, sizeof(text), "%sirq_n_rx0:%u,", text, Info->irq_n_rx0);
        snprintf(text, sizeof(text), "%sirq_n_rx1:%u,", text, Info->irq_n_rx1);
        snprintf(text, sizeof(text), "%sirq_n_sce:%u,", text, Info->irq_n_sce);
        snprintf(text, sizeof(text), "%sclock_bus:%u,", text, Info->clock_bus);
    }
    return text;
}

const char* HalCanErrorToStr(const uint32_t err){
    memset(text, 0, sizeof(text));
    if(err ) {
         strcpy(text, "Err");
     }

    if(HAL_CAN_ERROR_NOT_INITIALIZED==(err & HAL_CAN_ERROR_NOT_INITIALIZED)) {
        snprintf(text, sizeof(text), "%s,NotInited", text);
    }

    if(HAL_CAN_ERROR_TIMEOUT==(err & HAL_CAN_ERROR_TIMEOUT)) {
        snprintf(text, sizeof(text), "%s,Timeout", text);
    }

    if(HAL_CAN_ERROR_TX_TERR0==(err & HAL_CAN_ERROR_TX_TERR0)) {
        snprintf(text, sizeof(text), "%s,TERR0", text);
    }

    if(HAL_CAN_ERROR_EWG==(err & HAL_CAN_ERROR_EWG)) {
        snprintf(text, sizeof(text), "%s,Prot", text);
    }

    if(HAL_CAN_ERROR_EPV==(err & HAL_CAN_ERROR_EPV)) {
        snprintf(text, sizeof(text), "%s,EPV", text);
    }

    if(HAL_CAN_ERROR_BOF==(err & HAL_CAN_ERROR_BOF)) {
        snprintf(text, sizeof(text), "%s,BusOff", text);
    }

    if(HAL_CAN_ERROR_STF==(err & HAL_CAN_ERROR_STF)) {
        snprintf(text, sizeof(text), "%s,Stuff", text);
    }
    if(HAL_CAN_ERROR_FOR==(err & HAL_CAN_ERROR_FOR)) {
        snprintf(text, sizeof(text), "%s,Form", text);
    }

    if(HAL_CAN_ERROR_ACK==(err & HAL_CAN_ERROR_ACK)) {
        snprintf(text, sizeof(text), "%s,Ack", text);
    }

    if(HAL_CAN_ERROR_BR==(err & HAL_CAN_ERROR_BR)) {
        snprintf(text, sizeof(text), "%s,BitReces", text);
    }

    if(HAL_CAN_ERROR_BD==(err & HAL_CAN_ERROR_BD)) {
        snprintf(text, sizeof(text), "%s,BitDom", text);
    }

    if(HAL_CAN_ERROR_CRC==(err & HAL_CAN_ERROR_CRC)) {
        snprintf(text, sizeof(text), "%s,CRC15", text);
    }

    if(HAL_CAN_ERROR_RX_FOV0==(err & HAL_CAN_ERROR_RX_FOV0)) {
        snprintf(text, sizeof(text), "%s,RxFIFO0overrun", text);
    }

    if(HAL_CAN_ERROR_RX_FOV1==(err & HAL_CAN_ERROR_RX_FOV1)) {
        snprintf(text, sizeof(text), "%s,RxFIFO1overrun", text);
    }

    if(HAL_CAN_ERROR_TX_ALST0==(err & HAL_CAN_ERROR_TX_ALST0)) {
        snprintf(text, sizeof(text), "%s,TxMb0TxFailArbitLost", text);
    }

    if(HAL_CAN_ERROR_TX_TERR0==(err & HAL_CAN_ERROR_TX_TERR0)) {
        snprintf(text, sizeof(text), "%s,TxMb0Tx", text);
    }

    if(HAL_CAN_ERROR_TX_ALST1==(err & HAL_CAN_ERROR_TX_ALST1)) {
        snprintf(text, sizeof(text), "%s,TxMb1TxArb", text);
    }

    if(HAL_CAN_ERROR_TX_TERR1==(err & HAL_CAN_ERROR_TX_TERR1)) {
        snprintf(text, sizeof(text), "%s,TxMb1Tx", text);
    }

    if(HAL_CAN_ERROR_TX_ALST2==(err & HAL_CAN_ERROR_TX_ALST2)) {
        snprintf(text, sizeof(text), "%s,TxMb2TxArb", text);
    }

    if(HAL_CAN_ERROR_TX_TERR2==(err & HAL_CAN_ERROR_TX_TERR2)) {
        snprintf(text, sizeof(text), "%s,TxMb2Tx", text);
    }

    if(HAL_CAN_ERROR_NOT_READY==(err & HAL_CAN_ERROR_NOT_READY)) {
        snprintf(text, sizeof(text), "%s,NotReady", text);
    }

    if(HAL_CAN_ERROR_NOT_STARTED==(err & HAL_CAN_ERROR_NOT_STARTED)) {
        snprintf(text, sizeof(text), "%s,NotStart", text);
    }

    if(HAL_CAN_ERROR_PARAM==(err & HAL_CAN_ERROR_PARAM)) {
        snprintf(text, sizeof(text), "%s,Param", text);
    }
    return text;
}

bool CanDiagRegFA1R(const uint32_t dword) {
    bool res = false;
    CanReg_FA1R_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "FA1R:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    res = true;
    return res;
}

bool CanDiagRegBTR(const uint32_t dword) {
    bool res = false;
    CanReg_BTR_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "BTR:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "BRP:%u", Reg.BRP);
    LOG_INFO(CAN, "TS1:%u", Reg.TS1);
    LOG_INFO(CAN, "TS2:%u", Reg.TS2);
    LOG_INFO(CAN, "SJW:%u", Reg.SJW);
    LOG_INFO(CAN, "LBKM:%u", Reg.LBKM);
    LOG_INFO(CAN, "SILM:%u", Reg.SILM);

    res = true;
    return res;
}

bool CanDiagRegIER(const uint32_t dword) {
    bool res = false;
    CanReg_IER_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "CTRL1:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "TMEIE:%u", Reg.TMEIE);
    LOG_INFO(CAN, "FMPIE0:%u", Reg.FMPIE0);
    LOG_INFO(CAN, "FFIE0:%u", Reg.FFIE0);
    LOG_INFO(CAN, "FOVIE0:%u", Reg.FOVIE0);
    LOG_INFO(CAN, "FMPIE1:%u", Reg.FMPIE1);
    LOG_INFO(CAN, "FFIE1:%u", Reg.FFIE1);
    LOG_INFO(CAN, "FOVIE1:%u", Reg.FOVIE1);
    LOG_INFO(CAN, "EWGIE:%u", Reg.EWGIE);
    LOG_INFO(CAN, "EPVIE:%u", Reg.EPVIE);
    LOG_INFO(CAN, "BOFIE:%u", Reg.BOFIE);
    LOG_INFO(CAN, "LECIE:%u", Reg.LECIE);
    LOG_INFO(CAN, "ERRIE:%u", Reg.ERRIE);
    LOG_INFO(CAN, "WKUIE:%u", Reg.WKUIE);
    LOG_INFO(CAN, "SLKIE:%u", Reg.SLKIE);

    res = true;
    return res;
}

bool can_diag_low_level(uint8_t num, char *const keyword) {
    bool res = false;
    log_level_time_stamp(false);
    const CanInfo_t *Info = CanGetInfo(num);
    if (Info) {
        LOG_WARNING(CAN, "CAN%u,0x%08X", num, Info->CANx);
        res = CanDiagRegBTR(Info->CANx->BTR);
        res = CanDiagRegIER(Info->CANx->IER);
        res = CanDiagRegFA1R(Info->CANx->FA1R);
    }
    log_level_time_stamp(true);

    return res;
}

static bool can_get_data(const CanReg_TDLxR_t CAN_TDLxR, const CanReg_TDHxR_t CAN_TDHxR, uint8_t *const data) {
    bool res = true;
    data[0] = CAN_TDLxR.DATA0;
    data[1] = CAN_TDLxR.DATA1;
    data[2] = CAN_TDLxR.DATA2;
    data[3] = CAN_TDLxR.DATA3;

    data[4] = CAN_TDHxR.DATA4;
    data[5] = CAN_TDHxR.DATA5;
    data[6] = CAN_TDHxR.DATA6;
    data[7] = CAN_TDHxR.DATA7;
    return res;
}

bool can_diag_tx_mailbox(void) {
    bool res = false;
    static const table_col_t cols[] = {
            { 6, "CAN" },
            { 5, "sMB" },
            { 10, "IDE" },
            { 8, "StdID" },
            { 12, "ExtID" },
            { 7, "TIME" },
            { 4, "DLC" },
            { 18, "data" },
            { 5, "RTR" },
            { 5, "TXRQ" },
            { 5, "TGT" },
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t num = 0;
    for (num = 0; num <= 2; num++) {

        const CanInfo_t *Info = CanGetInfo(num);
        if (Info) {
            uint32_t i = 0;
            for (i = 0; i < 3; i++) {
                CanReg_TDHxR_t CAN_TDHxR;
                CanReg_TDLxR_t CAN_TDLxR;
                CanReg_TDTxR_t CAN_TDTxR;
                CanReg_TIxR_t CAN_TIxR;
                uint32_t spare_mail_box =0xfffffff;
#ifdef HAS_CAN_STM32
                spare_mail_box = can_get_spare_mail_box(num) ;
#endif

                CAN_TIxR.dword = Info->CANx->sTxMailBox[i].TIR;
                CAN_TDTxR.dword = Info->CANx->sTxMailBox[i].TDTR;
                CAN_TDLxR.dword = Info->CANx->sTxMailBox[i].TDLR;
                CAN_TDHxR.dword = Info->CANx->sTxMailBox[i].TDHR;

                CanExtId_t ExtId;
                ExtId.EXID_17_0 = CAN_TIxR.EXID_17_0;
                ExtId.EXTID_28_18 = CAN_TIxR.STID_EXT_28_18;

                uint8_t data[8] = { 0 };
                res = can_get_data(CAN_TDLxR, CAN_TDHxR, data);

                CanIdentifier_t can_identifier = CanIDEtoIdentifierType(CAN_TIxR.IDE);
                CanTxFrame_t frame_type = CanRTRtoFrameType(CAN_TIxR.RTR);

                char temp[300] = { 0 };
                strcpy(temp, TSEP);
                snprintf(temp, sizeof(temp), "%s CAN%u " TSEP, temp, num);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, spare_mail_box);
                snprintf(temp, sizeof(temp), "%s %8s " TSEP, temp, CanIdTypeToStr(can_identifier));
                snprintf(temp, sizeof(temp), "%s 0x%04x " TSEP, temp, CAN_TIxR.STID_EXT_28_18);
                snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, ExtId.EXTID);

                snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, CAN_TDTxR.TIME);
                snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, CAN_TDTxR.DLC);
                snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, ArrayToStr(data, 8));
                snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanFrameTypeToStr(frame_type));
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, CAN_TIxR.TXRQ);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, CAN_TDTxR.TGT);
                cli_printf("%s" CRLF, temp);
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}














static char cTemp[100]={0};

/*In mask mode the identifier registers are associated with mask registers specifying which
bits of the identifier are handled as “must match” or as “don’t care”. */
static const char*  CanStmFilter32ModeIdMaskToStr(uint32_t fxr0,
                                                  uint32_t fxr1) {
    strcpy(cTemp, "");
    CanRegFilter32Bit_t ID;
    ID.dword = fxr0;

    CanRegFilter32Bit_t MASK;
    MASK.dword = fxr1;

    if (CAN_IDE_EXT == ID.IDE) {
        snprintf(cTemp, sizeof(cTemp), "%sExID:0x%x," , cTemp, ID.EXT_ID);
        snprintf(cTemp, sizeof(cTemp), "%sExMask:0x%x" , cTemp, MASK.EXT_ID);
    } else {
        snprintf(cTemp, sizeof(cTemp), "%sStdID:0x%x," , cTemp, ID.STD_ID);
        snprintf(cTemp, sizeof(cTemp), "%sStdMask:0x%x" , cTemp, MASK.STD_ID);
    }
    return cTemp;
}

/*In identifier list mode, the mask registers are used as identifier registers. Thus instead of
defining an identifier and a mask, two identifiers are specified, doubling the number of single
identifiers. All bits of the incoming identifier must match the bits specified in the filter
registers.*/
static const char*  CanStmFilter32ModeListToStr(uint32_t fxr0,
        uint32_t fxr1){
    strcpy(cTemp,"");
    CanRegFilter32Bit_t ID1;
    ID1.dword = fxr0;

    CanRegFilter32Bit_t ID2;
    ID2.dword = fxr1;

    if (CAN_IDE_EXT == ID1.IDE) {
        snprintf(cTemp, sizeof(cTemp), "%sExID1:0x%x," , cTemp, ID1.EXT_ID);
        snprintf(cTemp, sizeof(cTemp), "%sExID2:0x%x" , cTemp, ID2.EXT_ID);
    } else {
        snprintf(cTemp, sizeof(cTemp), "%sStdID1:0x%x," , cTemp, ID1.STD_ID);
        snprintf(cTemp, sizeof(cTemp), "%sStdID1:0x%x" , cTemp, ID2.STD_ID);
    }

    return cTemp;
}

/*In mask mode the identifier registers are associated with mask registers specifying which
bits of the identifier are handled as “must match” or as “don’t care”. */
static const char*  CanStmFilter16ModeIdMaskToStr(uint32_t fxr0,
        uint32_t fxr1){
    strcpy(cTemp,"");


    CanRegFilter16DoubleIdMaskBit_t FLT1;
    memcpy(&FLT1,&fxr0,4);

    CanRegFilter16DoubleIdMaskBit_t FLT2;
    memcpy(&FLT2,&fxr1,4);

    snprintf(cTemp, sizeof(cTemp), "%s(StdID1:0x%04x," , cTemp, FLT1.FltID.STD);
    snprintf(cTemp, sizeof(cTemp), "%sMASK1:0x%04x);" , cTemp, FLT1.FltMask.STD);

    snprintf(cTemp, sizeof(cTemp), "%s(StdID2:0x%04x," , cTemp, FLT2.FltID.STD);
    snprintf(cTemp, sizeof(cTemp), "%sMASK2:0x%04x)" , cTemp, FLT2.FltMask.STD);

    return cTemp;
}

/*In identifier list mode, the mask registers are used as identifier registers. Thus instead of
defining an identifier and a mask, two identifiers are specified, doubling the number of single
identifiers. All bits of the incoming identifier must match the bits specified in the filter
registers.*/
static const char*  CanStmFilter16ModeListToStr(uint32_t fxr0,
        uint32_t fxr1) {
    strcpy(cTemp,"");

    CanRegFilter16QuadIdBit_t FLT1;
    memcpy(&FLT1,&fxr0,4);

    CanRegFilter16QuadIdBit_t FLT2;
    memcpy(&FLT2,&fxr1,4);

    snprintf(cTemp, sizeof(cTemp), "%sStdID1:0x%04x,", cTemp, FLT1.ID12.STD);
    snprintf(cTemp, sizeof(cTemp), "%sStdID2:0x%04x,", cTemp, FLT1.ID34.STD);
    snprintf(cTemp, sizeof(cTemp), "%sStdID3:0x%04x,", cTemp, FLT2.ID12.STD);
    snprintf(cTemp, sizeof(cTemp), "%sStdID4:0x%04x" , cTemp, FLT2.ID34.STD);


    return cTemp;
}



/* Two 16-bit filters for the STDID[10:0], RTR, IDE and EXTID[17:15] bits*/
static const char* CanStmFilter16ToStr(CanFilterMode_t mode,
                                     uint32_t fxr0,
                                     uint32_t fxr1) {
    char* name = "?";
    switch(mode){
        case CAN_FILTER_MODE_ID_MASK:{
            name = CanStmFilter16ModeIdMaskToStr(fxr0,fxr1);
        } break;
        case CAN_FILTER_MODE_LIST:{
            name = CanStmFilter16ModeListToStr(fxr0,fxr1);
        } break;
        default: break;
    }
    return name;
}

/*One 32-bit filter for the STDID[10:0], EXTID[17:0], IDE and RTR bits.*/
static const char* CanStmFilter32ToStr(CanFilterMode_t mode,
                                     uint32_t fxr0,
                                     uint32_t fxr1){
    char* name = "?";
    switch(mode){
        case CAN_FILTER_MODE_ID_MASK:
        {
            name = CanStmFilter32ModeIdMaskToStr(fxr0,fxr1);
        }
            break;
        case CAN_FILTER_MODE_LIST: {

            name = CanStmFilter32ModeListToStr(fxr0,fxr1);
        }
            break;
        default: break;
    }
    return name;
}



static const char* CanStmFilterToStr(CanFilterMode_t mode,
                                     CanFilterScale_t scale,
                                     uint32_t fxr0,
                                     uint32_t fxr1){
    char* name = "?";
    switch(scale){
    case CAN_FILTER_SCALE_16_BIT:
        name =CanStmFilter16ToStr( mode,fxr0,fxr1);
        break;
    case CAN_FILTER_SCALE_32_BIT:
        name =CanStmFilter32ToStr( mode,fxr0,fxr1);
        break;
    default: break;
    }

    return name;
}

bool can_diag_filters(const uint32_t num) {
    bool res = false;
    static const table_col_t cols[] = {
            { 6, "CAN" },
            { 5, "Flt" },
            { 4, "EN" },
            { 7, "FIFO" },
            { 5, "Scl" },
            { 8, "Mode" },
            { 12, "FxR1" },
            { 12, "FxR2" },
            { 43, "FilterCfg" },
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    const CanInfo_t *Info = CanGetInfo(num);
    if (Info) {
        uint32_t f = 0;
        for (f = 0; f < 28; f++) {
            CanReg_FxR0_t CAN_FxR0;
            CanReg_FxR1_t CAN_FxR1;

            CAN_FxR0.dword = Info->CANx->sFilterRegister[f].FR1;
            CAN_FxR1.dword = Info->CANx->sFilterRegister[f].FR2;

            bool en = can_filter_is_active(num, f);
            CanFFAxCode_t fifo = can_filter_fifo(num, f);
            CanFilterScale_t Scale = can_filter_scale(num, f);
            CanFilterMode_t mode = can_filter_mode(num, f);

            char temp[300] = { 0 };
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s CAN%u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, f);
            snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, en);
            snprintf(temp, sizeof(temp), "%s FIFO%1u " TSEP, temp, fifo);
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanFilterScaleToStr(Scale));
            snprintf(temp, sizeof(temp), "%s %6s " TSEP, temp, CanFilterModeToStr(mode));
            snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, CAN_FxR0.dword);
            snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, CAN_FxR1.dword);

            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, CanStmFilterToStr(mode,Scale,CAN_FxR0.dword,CAN_FxR1.dword));

            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

