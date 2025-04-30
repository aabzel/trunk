#include "sd_card_diag.h"

#include <stdio.h>

#include "byte_utils.h"
#include "common_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "sd_card_config.h"
#include "sd_card_drv.h"
#include "sd_card_types.h"
#include "time_diag.h"
#include "utils_math.h"


bool sd_parse_r1(uint8_t byte) {
    bool res = false;
    LOG_DEBUG(SD_CARD, "ParseR1 0x%02x=0b%s", byte, utoa_bin8(byte));
    R1_t R1;
    R1.byte = byte;

    if(R1.msb_zero) {
        LOG_ERROR(SD_CARD, "R1FormatErr");
        res = false;
    } else {
        LOG_DEBUG(SD_CARD, "NormalR1Response 0x%02x=0b%s", byte, utoa_bin8(byte));
        if(TOKEN_BUSY == R1.byte) {
            LOG_DEBUG(SD_CARD, "Busy..");
            res = false;
        }
        if(R1.idle) {
            LOG_WARNING(SD_CARD, "Bit0 IdleState");
        }
        if(R1.erase_reset) {
            LOG_INFO(SD_CARD, "Bit1 EraseReset");
        }
        if(R1.illegal_cmd) {
            LOG_ERROR(SD_CARD, "Bit2 IllegalCommand");
        }
        if(R1.com_crc_err) {
            LOG_ERROR(SD_CARD, "Bit3 CRCError");
        }
        if(R1.errase_sec_err) {
            LOG_ERROR(SD_CARD, "Bit4 EraseError");
        }
        if(R1.addr_err) {
            LOG_ERROR(SD_CARD, "Bit5 AddressError");
        }
        if(R1.param_err) {
            LOG_ERROR(SD_CARD, "Bit6 ArgError");
        }
        res = true;
    }
    return res;
}

void parse_write_flag(uint8_t flags) {
    if(flags & 1) {
        LOG_ERROR(SD_CARD, "error");
    }
    if(flags & (1 << 1)) {
        LOG_ERROR(SD_CARD, "CRC error");
    }
    if(flags & (1 << 2)) {
        LOG_ERROR(SD_CARD, "ECC error");
    }
    if(flags & (1 << 3)) {
        LOG_ERROR(SD_CARD, "range error");
    }
    if(flags & (1 << 4)) {
        LOG_ERROR(SD_CARD, "write protected error");
    }
}

bool sd_parse_r7(R7_t* pR7) {
    bool res = false;
    LOG_DEBUG(SD_CARD, "ParseR7");
    if(pR7) {
        print_hex(pR7->buff, 4);
        LOG_INFO(SD_CARD, "EchoBack: %u=%x", pR7->echo_back, pR7->echo_back);
        LOG_INFO(SD_CARD, "VoltAccep: %u=%x", pR7->voltage_accepted, pR7->voltage_accepted);
        LOG_INFO(SD_CARD, "CmdVer: %u=%x", pR7->cmd_version, pR7->cmd_version);
        res = true;
    }
    return res;
}

char* XxxxxXx2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case 0:
        name = "xxxx";
        break;
    case 1:
        name = "yyyyy";
        break;
    }
    return name;
}

char* SdLock2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case 0:
        name = "UnLocked";
        break;
    case 1:
        name = "Locked";
        break;
    }
    return name;
}

char* WpEraseSkip2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case 0:
        name = "EraseAllowed";
        break;
    case 1:
        name = "EraseProtected";
        break;
    }
    return name;
}

char* CardControllerErr2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case 0:
        name = "Ok";
        break;
    case 1:
        name = "InternalErr";
        break;
    }
    return name;
}

char* CardEcc2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case 0:
        name = "EccOk";
        break;
    case 1:
        name = "EccFailed";
        break;
    }
    return name;
}

char* WriteProt2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case 0:
        name = "Ok";
        break;
    case 1:
        name = "TryToWrProtBlock";
        break;
    }
    return name;
}

char* EraseParam2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case 0:
        name = "Ok";
        break;
    case 1:
        name = "InvalSel";
        break;
    }
    return name;
}

char* Error2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case 0:
        name = "Ok";
        break;
    case 1:
        name = "Error!";
        break;
    }
    return name;
}

char* OutOfRange2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case 0:
        name = "Ok";
        break;
    case 1:
        name = "OutOf";
        break;
    }
    return name;
}

bool sd_parse_r2(uint16_t word) {
    bool res = false;
    LOG_INFO(SD_CARD, "ParseR2: 0x%04x", word);
    R2_t R2;
    R2.word = word;
    LOG_INFO(SD_CARD, "Lock %u=%s", R2.card_is_locked, SdLock2Str(R2.card_is_locked));
    LOG_INFO(SD_CARD, "Wp %u=%s", R2.wp_erase_skip, WpEraseSkip2Str(R2.wp_erase_skip));
    LOG_INFO(SD_CARD, "Status %u=%s", R2.error, Error2Str(R2.error));
    LOG_INFO(SD_CARD, "CardController %u=%s", R2.cc_error, CardControllerErr2Str(R2.cc_error));
    LOG_INFO(SD_CARD, "CardEcc %u=%s", R2.card_ecc_failed, CardEcc2Str(R2.card_ecc_failed));
    LOG_INFO(SD_CARD, "WrProt %u=%s", R2.wp_violation, WriteProt2Str(R2.wp_violation));
    LOG_INFO(SD_CARD, "EraseParam %u=%s", R2.erase_param, EraseParam2Str(R2.erase_param));
    LOG_INFO(SD_CARD, "Range %u=%s", R2.out_of_range, OutOfRange2Str(R2.out_of_range));
    res = sd_parse_r1(R2.R1.byte);
    return res;
}

static const char* ScdStructure2Str(uint8_t csd_structure) {
    const char* name = "?";
    switch(csd_structure) {
    case CSD_VERSION_1_0:
        name = "CSD Version 1.0";
        break;
    case CSD_VERSION_2_0:
        name = "CSD Version 2.0";
        break;
    }
    return name;
}

bool sd_parse_csd_v1(CSD_t* pCSD) {
    bool res = false;
    if(pCSD) {
        LOG_WARNING(SD_CARD, "Parse CSD V1");
        LOG_INFO(SD_CARD, "CSD_STRUCT: %u=%s", pCSD->V1.csd_structure, ScdStructure2Str(pCSD->V1.csd_structure));
        LOG_INFO(SD_CARD, "C_SIZE %u", pCSD->V1.c_size);
        LOG_INFO(SD_CARD, "C_SIZE_MULT %u", pCSD->V1.c_size_mult);
        LOG_INFO(SD_CARD, "CardCommandClasses %u", pCSD->V1.ccc);
        LOG_INFO(SD_CARD, "Crc %u", pCSD->V1.crc);
        LOG_INFO(SD_CARD, "READ_BL_LEN %u", pCSD->V1.read_bl_len);
        LOG_INFO(SD_CARD, "EraseSectorSize %u", pCSD->V1.sector_size);

        SdCardInstance.mult = ipow(2, pCSD->V1.c_size_mult + 2);
        SdCardInstance.block_number = (pCSD->V1.c_size + 1) * SdCardInstance.mult;
        SdCardInstance.block_len = ipow(2, pCSD->V1.read_bl_len);

        SdCardInstance.memory_capacity = SdCardInstance.block_number * SdCardInstance.block_len;
        LOG_WARNING(SD_CARD, "MemoryCapacity %u", SdCardInstance.memory_capacity);
        LOG_INFO(SD_CARD, "BlockNumber %u", SdCardInstance.block_number);
        LOG_INFO(SD_CARD, "BlockLen %u", SdCardInstance.block_len);
        LOG_INFO(SD_CARD, "MULT %u", SdCardInstance.mult);
        res = true;
    }
    return res;
}

bool sd_parse_csd_v2(CSD_t* pCSD) {
    bool res = false;
    if(pCSD) {
        LOG_WARNING(SD_CARD, "Parse CSD V2");
        LOG_INFO(SD_CARD, "CSD_STRUCT: %u=%s", pCSD->V2.csd_structure, ScdStructure2Str(pCSD->V2.csd_structure));
        LOG_INFO(SD_CARD, "C_SIZE %u", pCSD->V2.c_size);
        LOG_INFO(SD_CARD, "CardCommandClasses %u", pCSD->V2.ccc);
        LOG_INFO(SD_CARD, "CRC %u", pCSD->V2.crc);
        LOG_INFO(SD_CARD, "ERASE_BLK_EN %u", pCSD->V2.erase_blk_en);
        LOG_INFO(SD_CARD, "READ_BL_LEN %u", pCSD->V2.read_bl_len);
        LOG_INFO(SD_CARD, "READ_BL_PARTIAL %u", pCSD->V2.read_bl_partial);
        LOG_INFO(SD_CARD, "TRAN_SPEED 0x%x", pCSD->V2.tran_speed);
        LOG_INFO(SD_CARD, "TAAC %u", pCSD->V2.taac);
        LOG_INFO(SD_CARD, "SECTOR_SIZE %u", pCSD->V2.sector_size);

        SdCardInstance.memory_capacity = (pCSD->V2.c_size + 1) * 512;
        LOG_WARNING(SD_CARD, "MemoryCapacity %u", SdCardInstance.memory_capacity);

        res = true;
    }
    return res;
}

bool sd_parse_ocr(OCR_t* pOCR) {
    bool res = false;
    if(pOCR) {
        LOG_WARNING(SD_CARD, "Parse OCR 0x%08x", pOCR->dword);
        LOG_INFO(SD_CARD, "UHS II %u", pOCR->uhs_ii_card_status);
        LOG_INFO(SD_CARD, "SwTo 1.8V %u", pOCR->sw_1_8_accep);
        LOG_INFO(SD_CARD, "CCS %u", pOCR->card_capacity_status);
        LOG_INFO(SD_CARD, "CardPowerUpStatus: %u", pOCR->card_power_up_status);
        res = true;
    }
    return res;
}

bool sd_parse_csd(CSD_t* pCSD) {
    bool res = false;
    if(pCSD) {
        LOG_WARNING(SD_CARD, "Parse CSD");
        if(pCSD->V1.csd_structure == pCSD->V2.csd_structure) {
            switch(pCSD->V1.csd_structure) {
            case CSD_VERSION_1_0:
                res = sd_parse_csd_v1(pCSD);
                break;
            case CSD_VERSION_2_0:
                res = sd_parse_csd_v2(pCSD);
                break;
            }
        }
    }
    return res;
}

bool sd_card_diag(SdCardHandle_t* Node) {
    bool res = false;
    if(Node) {
        res = true;
        res = sd_parse_cid(&Node->CID);
        res = sd_parse_csd(&Node->CSD);
        res = sd_parse_ocr(&Node->OCR);
        LOG_INFO(SD_CARD, "Lock %s", OnOff2Str(Node->locked));
    }
    return res;
}

const char* Mid2Str(uint8_t mid) {
    const char* name = "?";
/*TODO: make enums for vendor codes*/
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
        name = "ProGrade, Samsung";
        break;
    case 0x1d:
        name = "AData";
        break;
    case 0x27:
        name = "(Transcend) AgfaPhoto, Delkin, Integral, Lexar,"
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
        name = "Sony";
        break;
    case 0x9c:
        name = "Angelbird (V60), Hoodman";
        break;
    default:
        name = "Undef MID";

        break;
    }
    return name;
}

const char* SdMonth2Str(SdMonth_t month) {
    const char* name = "?";
    switch((uint8_t) month) {
    case SD_MONTH_JANUARY:
        name = "January";
        break;
    case SD_MONTH_FEBRUARY:
        name = "February";
        break;
    case SD_MONTH_MARCH:
        name = "March";
        break;
    case SD_MONTH_APRIL:
        name = "April";
        break;
    case SD_MONTH_MAY:
        name = "May";
        break;
    case SD_MONTH_JUNE:
        name = "June";
        break;
    case SD_MONTH_JULY:
        name = "July";
        break;
    case SD_MONTH_AUGUST:
        name = "August";
        break;
    case SD_MONTH_SEPTEMBER:
        name = "September";
        break;
    case SD_MONTH_OCTOBER:
        name = "October";
        break;
    case SD_MONTH_NOVEMBER:
        name = "November";
        break;
    case SD_MONTH_DECEMBER:
        name = "December";
        break;
    }
    return name;
}

char* Mdt2Str(uint16_t mdt) {
    static char name[40];
    Mdt_t Mdt;
    Mdt.word = mdt;
    snprintf(name, sizeof(name), "%s %u", SdMonth2Str(Mdt.month), Mdt.year + 2000);
    return name;
}

bool sd_parse_cid(CID_t* pCID) {
    bool res = false;
    LOG_WARNING(SD_CARD, "Explore CID");
    if(pCID) {
        print_hex(pCID->byte, sizeof(CSD_t));
        cli_printf(CRLF);
        if(pCID->one) {
            LOG_INFO(SD_CARD, "CRC7: 0x%02x", pCID->crc);                            /*CRC7 checksum*/
            LOG_INFO(SD_CARD, "ManufDate 0x%04x %s", pCID->mdt, Mdt2Str(pCID->mdt)); /*manufacturing date*/
            LOG_INFO(SD_CARD, "SerialNum: 0x%08x", pCID->psn);                       /*pruduct serial number*/
            LOG_INFO(SD_CARD, "Revision 0x%02x", pCID->prv);                         /*Producat revision*/
            cli_printf(CRLF "ProdName: ");
            res = reverse_byte_order_array(pCID->pnm, 5);
            print_mem(pCID->pnm, 5, true, true, true, true);                       /*Product Name*/
            LOG_INFO(SD_CARD, "AppId: 0x%04x", pCID->oid);                         /*Application ID*/
            LOG_INFO(SD_CARD, "ManufId 0x%02x=%s", pCID->mid, Mid2Str(pCID->mid)); /*Manufacturer ID*/
            res = true;
        } else {
            LOG_ERROR(SD_CARD, "InvalidCID");
        }
    }
    return res;
}

const char* Cmd2Str(uint8_t cmd) {
    const char* name = "?";
    const SdCommandInfo_t* Node = SdCmdGetNode(cmd);
    if(Node) {
        name = Node->name;
    }
    return name;
}
