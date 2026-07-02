#include "sdio_custom_diag.h"

#include <stdio.h>

#include "microcontroller.h"
//#include "stm32fx_hal_sd.h"

#include "array.h"
#include "bit_diag.h"
#include "data_types.h"
#include "debug_info.h"
#include "log.h"
#include "num_to_str.h"
#include "sdio_custom.h"
#include "sdio_mcal.h"
#include "stm32fx_hal.h"
#include "stm32f4xx_ll_sdmmc.h"

/* 31.9.16 SDIO register map */
const Reg32_t SdioReg[] = {
    {
        .name = "SDIO_POWER",
        .offset = 0x0,
        .access = ACCESS_READ_WRITE,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_CLKCR",
        .offset = 0x04,
        .access = ACCESS_READ_WRITE,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_ARG",
        .offset = 0x08,
        .access = ACCESS_READ_WRITE,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_CMD",
        .offset = 0x0C,
        .access = ACCESS_READ_WRITE,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_RESPCMD",
        .offset = 0x10,
        .access = ACCESS_READ_ONLY,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_RESP1",
        .offset = 0x14,
        .access = ACCESS_READ_ONLY,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_RESP2",
        .offset = 0x18,
        .access = ACCESS_READ_ONLY,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_RESP3",
        .offset = 0x1C,
        .access = ACCESS_READ_ONLY,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_RESP4",
        .offset = 0x20,
        .access = ACCESS_READ_ONLY,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_DTIMER",
        .offset = 0x24,
        .access = ACCESS_READ_WRITE,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_DLEN",
        .offset = 0x28,
        .access = ACCESS_READ_WRITE,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_DCTRL",
        .offset = 0x2C,
        .access = ACCESS_READ_WRITE,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_DCOUNT",
        .offset = 0x30,
        .access = ACCESS_READ_ONLY,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_STA",
        .offset = 0x34,
        .access = ACCESS_READ_ONLY,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_ICR",
        .offset = 0x38,
        .access = ACCESS_WRITE_ONLY,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_MASK",
        .offset = 0x3C,
        .access = ACCESS_READ_WRITE,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_FIFOCNT",
        .offset = 0x48,
        .access = ACCESS_READ_ONLY,
        .valid = true,
        .size = 4,
    },
    {
        .name = "SDIO_FIFO",
        .offset = 0x80,
        .access = ACCESS_READ_WRITE,
        .valid = true,
        .size = 4,
    },
};

uint32_t sdio_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(SdioReg);
    return cnt;
}

const char* HalSdioErrCode2Str(uint32_t ErrorCode) {
    const char* name = "?";
    switch(ErrorCode) {
    case SDMMC_ERROR_NONE:
        name = "Ok";
        break; /*  No error  */
    case SDMMC_ERROR_CMD_CRC_FAIL:
        name = "CMD_CRC_FAIL";
        break; /*  Command response received (but CRC check failed)*/
    case SDMMC_ERROR_DATA_CRC_FAIL:
        name = "DATA_CRC_FAIL";
        break; /*  Data block sent/received (CRC check failed) */
    case SDMMC_ERROR_CMD_RSP_TIMEOUT:
        name = "CMD_RSP_TIMEOUT";
        break; /*  Command response timeout*/
    case SDMMC_ERROR_DATA_TIMEOUT:
        name = "DATA_TIMEOUT";
        break; /*  Data timeout*/
    case SDMMC_ERROR_TX_UNDERRUN:
        name = "TX_UNDERRUN";
        break; /*  Transmit FIFO underrun*/
    case SDMMC_ERROR_RX_OVERRUN:
        name = "RX_OVERRUN";
        break; /*  Rx FIFO overrun*/
    case SDMMC_ERROR_ADDR_MISALIGNED:
        name = "ADDR_MISALIGNED";
        break; /*  Misaligned address*/
    case SDMMC_ERROR_BLOCK_LEN_ERR:
        name = "BLOCK_LEN_ERR";
        break; /*  Transferred block length is not allowed for the card or the
number of transferred bytes does not match the block length */
    case SDMMC_ERROR_ERASE_SEQ_ERR:
        name = "ERASE_SEQ_ERR";
        break; /*  An errorInthe sequence of erase command occurs*/
    case SDMMC_ERROR_BAD_ERASE_PARAM:
        name = "BAD_ERASE_PARAM";
        break; /*  An invalid selection for erase groups */
    case SDMMC_ERROR_WRITE_PROT_VIOLATION:
        name = "WRITE_PROT_VIOLATION";
        break; /*  Attempt to program a write protect block*/
    case SDMMC_ERROR_LOCK_UNLOCK_FAILED:
        name = "LOCK_UNLOCK_FAILED";
        break; /*  Sequence or password error has been detected in unlock
command or if there was an attempt to access a locked card*/
    case SDMMC_ERROR_COM_CRC_FAILED:
        name = "COM_CRC_FAILED";
        break; /*  CRC check of the previous command failed*/
    case SDMMC_ERROR_ILLEGAL_CMD:
        name = "ILLEGAL_CMD";
        break; /*  Command is not legal for the card state */
    case SDMMC_ERROR_CARD_ECC_FAILED:
        name = "CARD_ECC_FAILED";
        break; /*  Card internal ECC was applied but failed to correct the data*/
    case SDMMC_ERROR_CC_ERR:
        name = "CC_ERR";
        break; /*  Internal card controller error*/
    case SDMMC_ERROR_GENERAL_UNKNOWN_ERR:
        name = "GENERAL_UNKNOWN_ERR";
        break; /*  General or unknown error*/
    case SDMMC_ERROR_STREAM_READ_UNDERRUN:
        name = "STREAM_READ_UNDERRUN";
        break; /*  The card could not sustain data reading in stream rmode */
    case SDMMC_ERROR_STREAM_WRITE_OVERRUN:
        name = "STREAM_WRITE_OVERRUN";
        break; /*  The card could not sustain data programming in stream mode*/
    case SDMMC_ERROR_CID_CSD_OVERWRITE:
        name = "CID_CSD_OVERWRITE";
        break; /*  CID/CSD overwrite error */
    case SDMMC_ERROR_WP_ERASE_SKIP:
        name = "WP_ERASE_SKIP";
        break; /*  Only partial address space was erased */
    case SDMMC_ERROR_CARD_ECC_DISABLED:
        name = "CARD_ECC_DISABLED";
        break; /*  Command has been executed without using internal ECC*/
    case SDMMC_ERROR_ERASE_RESET:
        name = "ERASE_RESET";
        break; /*  Erase sequence was cleared before executing because an out
of erase sequence command was received*/
    case SDMMC_ERROR_AKE_SEQ_ERR:
        name = "AKE_SEQ_ERR";
        break; /*  Error in sequence of authentication */
    case SDMMC_ERROR_INVALID_VOLTRANGE:
        name = "INVALID_VOLTRANGE";
        break; /*  Error in case of invalid voltage range*/
    case SDMMC_ERROR_ADDR_OUT_OF_RANGE:
        name = "ADDR_OUT_OF_RANGE";
        break; /*  Error when addressed block is out of range*/
    case SDMMC_ERROR_REQUEST_NOT_APPLICABLE:
        name = "REQUEST_NOT_APPLICABLE";
        break; /*  Error when command request is not applicable*/
    case SDMMC_ERROR_INVALID_PARAMETER:
        name = "INVALID_PARAMETER";
        break; /*  the used parameter is not valid */
    case SDMMC_ERROR_UNSUPPORTED_FEATURE:
        name = "UNSUPPORTED_FEATURE";
        break; /*  Error when feature is not insupported */
    case SDMMC_ERROR_BUSY:
        name = "BUSY";
        break; /*  Error when transfer process is busy */
    case SDMMC_ERROR_DMA:
        name = "DMA";
        break; /*  Error while DMA transfer*/
    case SDMMC_ERROR_TIMEOUT:
        name = "TIMEOUT";
        break; /*  Timeout error */
    }

    return name;
}

const char* CardState2Str(HAL_SD_CardStateTypeDef code) {
    const char* name = "?";
    switch(code) {
    case HAL_SD_CARD_ERROR:
        name = "Err";
        break;
    case HAL_SD_CARD_DISCONNECTED:
        name = "DisCon";
        break;
    case HAL_SD_CARD_PROGRAMMING:
        name = "Prog";
        break;
    case HAL_SD_CARD_RECEIVING:
        name = "Rx";
        break;
    case HAL_SD_CARD_SENDING:
        name = "Send";
        break;
    case HAL_SD_CARD_TRANSFER:
        name = "Tx";
        break;
    case HAL_SD_CARD_STANDBY:
        name = "Standby";
        break;
    case HAL_SD_CARD_IDENTIFICATION:
        name = "Identify";
        break;
    case HAL_SD_CARD_READY:
        name = "Ready";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* SdState2Str(HAL_SD_StateTypeDef code) {
    const char* name = "?";
    switch(code) {
    case HAL_SD_STATE_RESET:
        name = "Reset";
        break;
    case HAL_SD_STATE_READY:
        name = "Ready";
        break;
    case HAL_SD_STATE_TIMEOUT:
        name = "TimeOut";
        break;
    case HAL_SD_STATE_BUSY:
        name = "Busy";
        break;
    case HAL_SD_STATE_PROGRAMMING:
        name = "Prog";
        break;
    case HAL_SD_STATE_RECEIVING:
        name = "Rx";
        break;
    case HAL_SD_STATE_TRANSFER:
        name = "Tx";
        break;
    case HAL_SD_STATE_ERROR:
        name = "Err";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* ManufaturerId2Str(uint8_t mid) {
    const char* name = "?";
    switch(mid) {
    case 0x01:
        name = "Panasonic";
        break;
    case 0x2:
        name = "Toshiba";
        break;
    case 0x3:
        name = "SanDisk";
        break;
    case 0x1b:
        name = "ProGrade,Samsung";
        break;
    case 0x1d:
        name = "AData";
        break;
    case 0x27:
        name = "Transcend AgfaPhoto, Delkin, Integral, Lexar, "
               "Patriot, PNY, Polaroid, Sony, Verbatim";
        break;
    case 0x28:
        name = "Lexar";
        break;
    case 0x31:
        name = "Silicon Power";
        break;
    case 0x41:
        name = "Kingston";
        break;
    case 0x74:
        name = "Transcend";
        break;
    case 0x76:
        name = "Patriot";
        break;
    case 0x82:
        name = "Sony)";
        break;
    case 0x9c:
        name = "Angelbird (V60), Hoodman";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

bool ParseSdCardStatus(const HAL_SD_CardStatusTypeDef* const Status) {
    bool res = false;
    LOG_WARNING(LG_SDIO, CRLF "SdCardStatus...");
    if(Status) {
        res = true;
        LOG_INFO(LG_SDIO, "DataBusWidth:%u", Status->DataBusWidth);
        LOG_INFO(LG_SDIO, "SecuredMode:%u", Status->SecuredMode);
        LOG_INFO(LG_SDIO, "CardType:%u", Status->CardType);
        LOG_INFO(LG_SDIO, "ProtectedAreaSize:%u", Status->ProtectedAreaSize);
        LOG_INFO(LG_SDIO, "SpeedClass:%u", Status->SpeedClass);
        LOG_INFO(LG_SDIO, "PerformanceMove:%u", Status->PerformanceMove);
        LOG_INFO(LG_SDIO, "AllocationUnitSize:%u", Status->AllocationUnitSize);
        LOG_INFO(LG_SDIO, "EraseSize:%u", Status->EraseSize);
        LOG_INFO(LG_SDIO, "EraseTimeout:%u", Status->EraseTimeout);
        LOG_INFO(LG_SDIO, "EraseOffset:%u", Status->EraseOffset);
    }
    return res;
}

bool ParseSdCardCID(const HAL_SD_CardCIDTypeDef* const CIDp) {
    bool res = false;
    LOG_WARNING(LG_SDIO, CRLF "CID...");
    if(CIDp) {
        res = true;
        LOG_INFO(LG_SDIO, "ManID:%u 0x%x %s", CIDp->ManufacturerID, CIDp->ManufacturerID,
                 ManufaturerId2Str(CIDp->ManufacturerID));
        U16_bit_t un16;
        un16.u16 = CIDp->OEM_AppliID;
        LOG_INFO(LG_SDIO, "OemAppId:%u 0x%04x %c%c", un16.u16, un16.u16, un16.u8[0], un16.u8[1]);
        U32_bit_t un32;
        un32.u32 = CIDp->ProdName1;
        LOG_INFO(LG_SDIO, "ProdName1:%u 0x%08x %c%c%c%c%c", un32.u32, un32.u32, un32.u8[3], un32.u8[2], un32.u8[1],
                 un32.u8[0], CIDp->ProdName2);
        ProdRev_t prv;
        prv.byte = CIDp->ProdRev;
        LOG_INFO(LG_SDIO, "ProdRev:0x%02x=%u.%u", prv.byte, prv.m, prv.n);
        LOG_INFO(LG_SDIO, "ProdSN:%u 0x%08x", CIDp->ProdSN, CIDp->ProdSN);
        ManufDate_t ManufDate;
        ManufDate.word = CIDp->ManufactDate;
        LOG_INFO(LG_SDIO, "ManufactDate: Month:%u Year:%u", ManufDate.month, ManufDate.year + 2000);
        LOG_INFO(LG_SDIO, "CID_CRC:%u=0x%x", CIDp->CID_CRC, CIDp->CID_CRC);
    }
    return res;
}

bool ParseSdCardCSD(const HAL_SD_CardCSDTypeDef* const pCSD) {
    bool res = false;
    LOG_WARNING(LG_SDIO, CRLF "CardCSD...");
    if(pCSD) {
        res = true;
        LOG_INFO(LG_SDIO, "CSD_CRC:%u", pCSD->CSD_CRC);
        LOG_INFO(LG_SDIO, "ECC:%u", pCSD->ECC);
        LOG_INFO(LG_SDIO, "FileFormat:%u", pCSD->FileFormat);
        LOG_INFO(LG_SDIO, "TempWrProtect:%u", pCSD->TempWrProtect);
        LOG_INFO(LG_SDIO, "PermWrProtect:%u", pCSD->PermWrProtect);
        LOG_INFO(LG_SDIO, "CopyFlag:%u", pCSD->CopyFlag);
        LOG_INFO(LG_SDIO, "FileFormatGroup:%u", pCSD->FileFormatGroup);
        LOG_INFO(LG_SDIO, "ContentProtectAppli:%u", pCSD->ContentProtectAppli);
        LOG_INFO(LG_SDIO, "WriteBlockPaPartial:%u", pCSD->WriteBlockPaPartial);
        LOG_INFO(LG_SDIO, "MaxWrBlockLen:%u", pCSD->MaxWrBlockLen);
        LOG_INFO(LG_SDIO, "WrSpeedFact:%u", pCSD->WrSpeedFact);
        LOG_INFO(LG_SDIO, "ManDeflECC:%u", pCSD->ManDeflECC);
        LOG_INFO(LG_SDIO, "WrProtectGrEnable:%u", pCSD->WrProtectGrEnable);
        LOG_INFO(LG_SDIO, "WrProtectGrSize:%u", pCSD->WrProtectGrSize);
        LOG_INFO(LG_SDIO, "EraseGrMul:%u", pCSD->EraseGrMul);
        LOG_INFO(LG_SDIO, "EraseGrSize:%u", pCSD->EraseGrSize);
        LOG_INFO(LG_SDIO, "DeviceSizeMul:%u", pCSD->DeviceSizeMul);
        LOG_INFO(LG_SDIO, "MaxWrCurrentVDDMax:%u", pCSD->MaxWrCurrentVDDMax);
        LOG_INFO(LG_SDIO, "MaxWrCurrentVDDMin:%u", pCSD->MaxWrCurrentVDDMin);
        LOG_INFO(LG_SDIO, "MaxRdCurrentVDDMax:%u", pCSD->MaxRdCurrentVDDMax);
        LOG_INFO(LG_SDIO, "MaxRdCurrentVDDMin:%u", pCSD->MaxRdCurrentVDDMin);
        LOG_INFO(LG_SDIO, "DeviceSize:%u", pCSD->DeviceSize);
        LOG_INFO(LG_SDIO, "DSRImpl:%u", pCSD->DSRImpl);
        LOG_INFO(LG_SDIO, "RdBlockMisalign:%u", pCSD->RdBlockMisalign);
        LOG_INFO(LG_SDIO, "WrBlockMisalign:%u", pCSD->WrBlockMisalign);
        LOG_INFO(LG_SDIO, "PartBlockRead:%u", pCSD->PartBlockRead);
        LOG_INFO(LG_SDIO, "RdBlockLen:%u", pCSD->RdBlockLen);
        LOG_INFO(LG_SDIO, "CardComdClasses:%u", pCSD->CardComdClasses);
        LOG_INFO(LG_SDIO, "MaxBusClkFrec:%u", pCSD->MaxBusClkFrec);
        LOG_INFO(LG_SDIO, "NSAC:%u", pCSD->NSAC);
        LOG_INFO(LG_SDIO, "TAAC:%u", pCSD->TAAC);
        LOG_INFO(LG_SDIO, "SysSpecVersion:%u", pCSD->SysSpecVersion);
        LOG_INFO(LG_SDIO, "CSDStruct:%u", pCSD->CSDStruct);
#if 0
#endif
    }
    return res;
}

bool ParseSdCardInfo(const HAL_SD_CardInfoTypeDef* const CardInfo) {
    bool res = false;
    LOG_WARNING(LG_SDIO, CRLF "CardInfo...");
    if(CardInfo) {
        res = true;
        LOG_INFO(LG_SDIO, "CardType:%u 0x%x %s", CardInfo->CardType, CardInfo->CardType);
        LOG_INFO(LG_SDIO, "CardVersion:%u", CardInfo->CardVersion);
        LOG_INFO(LG_SDIO, "Class:%u", CardInfo->Class);
        LOG_INFO(LG_SDIO, "RelCardAdd:%u", CardInfo->RelCardAdd);
        LOG_INFO(LG_SDIO, "BlockNbr:%u", CardInfo->BlockNbr);
        LOG_INFO(LG_SDIO, "BlockSize:%u", CardInfo->BlockSize);
        LOG_INFO(LG_SDIO, "LogBlockNbr:%u", CardInfo->LogBlockNbr);
        LOG_INFO(LG_SDIO, "LogBlockSize:%u", CardInfo->LogBlockSize);
    }
    return res;
}

char* size_of_prot_area2Str(uint32_t size_of_prot_area) {
    static char name[80] = "";
    snprintf(name, sizeof(name), "%u Byte", (unsigned int)size_of_prot_area);
    return name;
}

const char* au_size_str(uint8_t au_size) {
    const char* au_size_str_out = "?";

    switch(au_size) {
    case 9:
        au_size_str_out = "4 MByte";
        break;
    default:
        au_size_str_out = "?";
        break;
    }
    return au_size_str_out;
}

bool SdioStatusDiag(const uint32_t dword) {
    bool res = false;
    SdioRegSDIO_STA_t SDIO_STA;
    SDIO_STA.dword = dword;
    if(SDIO_STA.dword) {
        LOG_WARNING(LG_SDIO, "SDIO_STA:0x%08X=%s", SDIO_STA.dword, utoa_bin32(SDIO_STA.dword));

#if 0
        bit_1val_diag(LOG_LEVEL_ERROR, LG_SDIO, SDIO_STA.TXUNDERR, "TxFIFOunderrun error");
        bit_1val_diag(LOG_LEVEL_ERROR, LG_SDIO, SDIO_STA.RXOVERR, "RxdFIFO overrun error");
        bit_1val_diag(LOG_LEVEL_ERROR, LG_SDIO, SDIO_STA.CTIMEOUT, "CmdResp timeout");
        bit_1val_diag(LOG_LEVEL_ERROR, LG_SDIO, SDIO_STA.DTIMEOUT, "DataTimeout");
        bit_1val_diag(LOG_LEVEL_ERROR, LG_SDIO, SDIO_STA.STBITERR,
                      "StartBit not detected on all data signalsInwide bus mode");

        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.CCRCFAIL, "Cmdresponse Rx");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.DCRCFAIL, "DataBlockTx/Rx");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.CMDREND, "CmdRespRx (CRC check passed)");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.CMDSENT, "CmdSent");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.DATAEND, "DataEnd (data counter, SDIDCOUNT, is zero)");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.DBCKEND, "DataBlockTx/Rx (CRC check passed)");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.CMDACT, "CmdTransferInprogress");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.TXACT, "DataTxInprogress");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.RXACT, "DataRxInprogress");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.TXFIFOHE,
                      "TxFIFOhalfEmpty: at least 8 words can be written into the FIFO");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.RXFIFOHF,
                      "RxFIFOhalfFull: there are at least 8 wordsInthe FIFO");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.RXFIFOE, "RxFIFOempty");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.TXFIFOF, "TxFIFOfull");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.RXFIFOF, "RxFIFOfull");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.TXFIFOE, "TxFIFOempty");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.TXDAVL, "DataAvailableInTxFIFO");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.RXDAVL, "DataAvailableInRxFIFO");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.SDIOIT, "SDIOinterruptRx");
        bit_1val_diag(LOG_LEVEL_DEBUG, LG_SDIO, SDIO_STA.CEATAEND, "CE-ATAcommandCompletionSignalRxForCMD61");
        res = true;
#endif
    }
    return res;
}

bool sdio_scan(uint8_t num) {
    bool res = false;
    LOG_DEBUG(LG_SDIO, "ScanNum:%u ", num);
    //set_log_level(LG_SDIO, LOG_LEVEL_NOTICE);
    SdioHandle_t* Node = SdioGetNode(num);
    if(Node) {
        HAL_StatusTypeDef ret;
        ret = HAL_SD_GetCardInfo(&Node->Handle, &Node->CardInfo);
        if(HAL_OK == ret) {
            LOG_INFO(LG_SDIO, "SDIO%u,GetCardInfo Ok", num);
            res = true;
        } else {
            LOG_ERROR(LG_SDIO, "GetCardInfoErr:%s", HalStatusToStr(ret));
        }
    }

    if(res) {
        uint32_t sum = 0;
        Node->busy_block_cnt = 0;
        Node->spare_block_cnt = 0;
        // uint8_t RxData[SDIO_BLOCK_SIZE + 1];
        LOG_INFO(LG_SDIO, "BlockNbr %u", Node->CardInfo.BlockNbr);
        uint32_t i = 0;
        for(i = 0; i < Node->CardInfo.BlockNbr; i++) {
            diag_progress_log(i, Node->CardInfo.BlockNbr, 200);
            res = sdio_read_sector(num, i, 1, Node->RxData);
            if(res) {
                sum = arr_sum(Node->RxData, SDIO_BLOCK_SIZE);
                if(0 < sum) {
                    Node->busy_block_cnt++;
                } else {
                    Node->spare_block_cnt++;
                }
            } else {
                LOG_ERROR(LG_SDIO, "Read err BlockNbr %u", i);
            }
        }
        LOG_INFO(LG_SDIO, "BlockNbr %u", Node->CardInfo.BlockNbr);
        LOG_INFO(LG_SDIO, "busy %u Blk", Node->busy_block_cnt);
        LOG_INFO(LG_SDIO, "spare %u Blk", Node->spare_block_cnt);
    }
    //set_log_level(LG_SDIO, LOG_LEVEL_DEBUG);
    return res;
}
