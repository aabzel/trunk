#include "can_custom_diag.h"

#include "macro_utils.h"
#include "array_diag.h"
#include "shared_array.h"
#include "diag_inc.h"
#include "can_mcal.h"
#include "interfaces_diag.h"
#include "can_misc.h"
#include "num_to_str.h"

const char* CanSRRToStr(const CanSRRCode_t srr) {
    char* name = "?";
    switch(srr) {
    case CAN_SRR_DOMINANT_NO_VALID:        name = "DV";        break;
    case CAN_SRR_RECESSIVE_COMPULSORY:     name = "RC";        break;
    default:        name = "?";        break;
    }
    return name;
}


const char* CanESItoStr(const CanESICode_t error_ind) {
    char* name = "?";
    switch(error_ind) {
    case CAN_ESI_PASSIVE:        name = "Pass";        break;
    case CAN_ESI_ACTIVE:        name = "Acti";        break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanBRSToStr(const CanBRSCode_t bit_rate_sw) {
    char* name = "?";
    switch(bit_rate_sw) {
    case CAN_BRS_NO:        name = "BrC";        break;
    case CAN_BRS_YES:        name = "BrS";        break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanRTRToStr(const CanRTRCode_t remote_tx_req) {
    char* name = "?";
    switch(remote_tx_req) {
    case CAN_RTR_TX:        name = "TX";        break;
    case CAN_RTR_REM_REQ:        name = "RQ";        break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanFrameRTRToStr(const CanFrameRTR_t rtr) {
    char* name = "?";
    switch(rtr) {
    case CAN_RTR_REMOTE_REJECTED:        name = "DAT";        break;
    case CAN_RTR_REMOTE_ACCEPTED:        name = "RMT";        break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanEDLToStr(CanEDLCode_t extended_data_length) {
    char* name = "?";
    switch(extended_data_length) {
    case CAN_EDL_CLASSIC:        name = "CS";        break;
    case CAN_EDL_FD:        name = "FD";        break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanIDEToStr(const CanIDECode_t id_ext_bit) {
    char* name = "?";
    switch(id_ext_bit) {
    case CAN_IDE_STANDARD:        name = "Std";        break;
    case CAN_IDE_EXTENDED:        name = "Ext";        break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanFlexErrorToStr(const FLEXCAN_ErrorType error) {
    char* name = "?";
    switch(error) {
    case FLEXCAN_E_OK:        name = "Ok";        break;
    case FLEXCAN_E_INVALID_VERSION:        name = "VerErr";        break;
    case FLEXCAN_E_FAILED:        name = "Failed";        break;
    case FLEXCAN_E_INVALID_PARAM:        name = "paramErr";        break;
    case FLEXCAN_E_INVALID_SIZE:        name = "SizeErr";        break;
    case FLEXCAN_E_INVALID_SEQUENCE:        name = "SeqErr";        break;
    case FLEXCAN_E_NULL_POINT:        name = "NullPrtErr";        break;
    case FLEXCAN_E_TIMEOUT:        name = "TimeOutErr";        break;
    case FLEXCAN_E_BUSY:        name = "Busy";        break;
    case FLEXCAN_E_MB_OUTOFRANGE:        name = "OutOfRange";        break;
    default:        name = "?";        break;
    }
    return name;
}


const char* CanErrorToStr(const FLEXCAN_ErrorType error) {
    char* name = "?";
    switch(error) {
    case FLEXCAN_E_OK:
        name = "Ok";
        break;
    case FLEXCAN_E_INVALID_VERSION:
        name = "VerErr";
        break;
    case FLEXCAN_E_FAILED:
        name = "Failed";
        break;
    case FLEXCAN_E_INVALID_PARAM:
        name = "paramErr";
        break;
    case FLEXCAN_E_INVALID_SIZE:
        name = "SizeErr";
        break;
    case FLEXCAN_E_INVALID_SEQUENCE:
        name = "SeqErr";
        break;
    case FLEXCAN_E_NULL_POINT:
        name = "NullPrtErr";
        break;
    case FLEXCAN_E_TIMEOUT:
        name = "TimeOutErr";
        break;
    case FLEXCAN_E_BUSY:
        name = "Busy";
        break;
    case FLEXCAN_E_MB_OUTOFRANGE:
        name = "OutOfRange";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* CanInfoToStr(const CanInfo_t* const Info) {
    if(Info) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sCAN%u,", text, Info->num);
        snprintf(text, sizeof(text), "%sInst:%u,", text, Info->e_instance);
        snprintf(text, sizeof(text), "%sNVRAM_ID:%u,", text, Info->nvram_id);
        snprintf(text, sizeof(text), "%sMAC:%p,", text, Info->CANx);
        snprintf(text, sizeof(text), "%sClkName:0x%x,", text, Info->e_clock_name);
        snprintf(text, sizeof(text), "%sNVIC:%d", text, Info->irq_n);
    }
    return text;
}

const char* FlexCanBaudRegToStr(const FLEXCAN_BaudRegType* const TimeSeg) {
    static char temp[150] = {0};
    if(TimeSeg) {
        uint32_t prescaler = CanBitrateToPreScaler(TimeSeg);
        strcpy(temp, "");
        snprintf(temp, sizeof(temp), "%sBitPsc:%u,", temp, prescaler);
        snprintf(temp, sizeof(temp), "%spreDiv:%u,", temp, TimeSeg->u32Presdiv);
        snprintf(temp, sizeof(temp), "%sJumpWidth:%u,", temp, TimeSeg->u32Rjw);
        snprintf(temp, sizeof(temp), "%sPropSeg:%u,", temp, TimeSeg->u32Propseg);
        snprintf(temp, sizeof(temp), "%sPhaSeg1:%u,", temp, TimeSeg->u32Pseg1);
        snprintf(temp, sizeof(temp), "%sPhaSeg2:%u,", temp, TimeSeg->u32Pseg2);
    }
    return temp;
}


static bool can_handle_status_mask_diag(uint32_t dword, char* name) {
    bool res = true;
    cli_printf("%19s : 0x%08x = 0b%s " CRLF, name, dword, utoa_bin32(dword));
    return res;
}

static bool can_diag_handle_tStatus(const FLEXCAN_HandleType* const pHandle) {
    bool res = false;
    if(pHandle) {
        LOG_INFO(CAN, "eStatusSeq,%u", pHandle->tStatus.eStatusSeq);
        LOG_INFO(CAN, "u8MbStart,%u", pHandle->tStatus.u8MbStart);
        LOG_INFO(CAN, "aMbDataWidth,%u", pHandle->tStatus.aMbDataWidth[0]);

        can_handle_status_mask_diag(pHandle->tStatus.aInterruptMask[0], "aInterruptMask");
        can_handle_status_mask_diag(pHandle->tStatus.aRxInterruptMask[0], "aRxInterruptMask");
        can_handle_status_mask_diag(pHandle->tStatus.aTxInterruptMask[0], "aTxInterruptMask");

        can_handle_status_mask_diag(pHandle->tStatus.aPollingMask[0], "aPollingMask");
        can_handle_status_mask_diag(pHandle->tStatus.aRxPollingMask[0], "aRxPollingMask");
        can_handle_status_mask_diag(pHandle->tStatus.aTxPollingMask[0], "aTxPollingMask");

        res = true;
    }
    return res;
}

static bool can_diag_handle_tSettings(const FLEXCAN_HandleType* const pHandle) {
    bool res = false;
    if(pHandle) {
        LOG_INFO(CAN, "pRxBuf,0x%p", pHandle->tSettings.pRxBuf);
        LOG_INFO(CAN, "pWakeMsg,0x%p", pHandle->tSettings.pWakeMsg);
        LOG_INFO(CAN, "pErrorNotify,0x%p", pHandle->tSettings.pErrorNotify);
        LOG_INFO(CAN, "pFifoIssueNotify,0x%p", pHandle->tSettings.pFifoIssueNotify);
        LOG_INFO(CAN, "pTxNotify,0x%p", pHandle->tSettings.pTxNotify);
        LOG_INFO(CAN, "pRxNotify,0x%p", pHandle->tSettings.pRxNotify);
        LOG_INFO(CAN, "pWakeNotify,0x%p", pHandle->tSettings.pWakeNotify);
        res = true;
    }
    return res;
}

bool can_diag_handle(const FLEXCAN_HandleType* const pHandle) {
    bool res = false;
    if(pHandle) {
        LOG_INFO(CAN, "CAN%u", pHandle->eInstance);
        res = can_diag_handle_tStatus(pHandle);
        res = can_diag_handle_tSettings(pHandle);
    }
    return res;
}


