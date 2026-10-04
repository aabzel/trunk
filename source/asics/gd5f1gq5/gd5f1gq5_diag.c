#include "gd5f1gq5_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "gpio_diag.h"
#include "convert.h"
#include "diag_inc.h"
#include "gd5f1gq5_mcal.h"
#include "array_diag.h"


/*
 * @brief Convert GD5F1GQ5 command code to human-readable string (names only)
 * @param command Command code (from Gd5f1gq5Command_t enum)
 * @return Pointer to static string with command name, or "UNKNOWN" if unknown
 */
const char* Gd5f1gq5CommandToStr(const Gd5f1gq5Command_t command) {
    const char* name = "?";
    switch(command) {
        /* --- Write Operations (Section 7) --- */
        case GD5F_CMD_WRITE_ENABLE:     name = "WREN";      break;
        case GD5F_CMD_WRITE_DISABLE:    name = "WRDI";      break;

        /* --- Feature Operations (Section 12.1) --- */
        case GD5F_CMD_GET_FEATURES:     name = "GET_FTR";   break;
        case GD5F_CMD_SET_FEATURES:     name = "SET_FTR";   break;

        /* --- Read Operations (Section 8) --- */
        case GD5F_CMD_PAGE_READ_TO_CACHE:name = "PAGE_RD";   break;
        case GD5F_CMD_READ_FROM_CACHE:  name = "RD_CACHE";  break;
        case GD5F_CMD_READ_FROM_CACHE_ALT:name = "RD_CACHE_ALT"; break;
        case GD5F_CMD_READ_FROM_CACHE_X2:name = "RD_X2";     break;
        case GD5F_CMD_READ_FROM_CACHE_X4:name = "RD_X4";     break;
        case GD5F_CMD_READ_FROM_CACHE_DUAL_IO:name = "RD_DIO";    break;
        case GD5F_CMD_READ_FROM_CACHE_QUAD_IO:name = "RD_QIO";    break;
        case GD5F_CMD_READ_FROM_CACHE_QUAD_DTR:name = "RD_DTR";    break;

        /* --- Identification Commands (Section 8.9, 8.10, 8.11) --- */
        case GD5F_CMD_READ_ID:          name = "RD_ID";     break;
      //  case GD5F_CMD_READ_UID:         name = "RD_UID";    break;
      //  case GD5F_CMD_READ_PARAMETER_PAGE:name = "RD_PARAM";  break;

        /* --- Program Operations (Section 9) --- */
        case GD5F_CMD_PROGRAM_LOAD:     name = "PROG_LD";   break;
        case GD5F_CMD_PROGRAM_LOAD_X4:  name = "PROG_LD4";  break;
        case GD5F_CMD_PROGRAM_EXECUTE:  name = "PROG_EXE";  break;

        /* --- Program Random Data (Internal Data Move, Section 9.6, 9.7) --- */
        case GD5F_CMD_PROGRAM_LOAD_RANDOM:name = "RAND_LD";   break;
        case GD5F_CMD_PROGRAM_LOAD_RANDOM_X4:name = "RAND_LD4";  break;
        case GD5F_CMD_PROGRAM_LOAD_RANDOM_X4_ALT:name = "RAND_LD4A"; break;

        /* --- Erase Operations (Section 10) --- */
        case GD5F_CMD_BLOCK_ERASE:      name = "BLK_ERASE"; break;

        /* --- Reset Operations (Section 11) --- */
        case GD5F_CMD_SOFT_RESET:       name = "SOFT_RST";  break;
        case GD5F_CMD_ENABLE_POWER_ON_RESET:name = "EN_POR";    break;
        case GD5F_CMD_POWER_ON_RESET:   name = "POR";       break;

        default:                        name = "?";        break;
    }
    return name;
}

const char* Gd5f1gq5IdToStr(const Gd5f1gq5ID_t * const pID) {
    strcpy(text, "");
    if(pID) {
        snprintf(text, sizeof(text), "%sReg:0x%04x,", text, pID->word);
        snprintf(text, sizeof(text), "%sDevID:0x%x,", text, pID->device_id);
        snprintf(text, sizeof(text), "%sMfrID:0x%x", text, pID->manufacturer_id);
    }
    return text;
}


const char* Gd5f1gq5ConfigToStr(const Gd5f1gq5Config_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sSPI%u,", text, Config->spi_num);
        snprintf(text, sizeof(text), "%sCsPad:%s,", text, GpioPadToStr(Config->chip_select));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* Gd5f1gq5NodeToStr(const Gd5f1gq5Handle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

/*
 * ll GD5F1GQ5 debug
 * */
bool gd5f1gq5_diag_one(uint8_t num) {
    bool res = false;
    uint8_t uid[16]={0};
    memset(uid,0,sizeof(16));
    res = gd5f1gq5_read_uid(num, uid);
    if(res) {
        LOG_INFO(GD5F1GQ5, "UID:%s", ArrayToStr(uid,16));
    }
    return res;
}

bool gd5f1gq5_diag(void) {
    bool res = false;
    gd5f1gq5_init_custom() ;
    res=gd5f1gq5_diag_one(1);
    return res;
}

// Driver Strength Register (Feature Address D0h)
const char* Gd5f1gq5RegDriverStrengthToStr(const void * const memory){
    Gd5f1gq5RegDriverStrength_t *pReg=(Gd5f1gq5RegDriverStrength_t *)memory;
    strcpy(text, "");
    if(pReg) {
        snprintf(text, sizeof(text), "%sDS_IO:%u,", text, pReg->DS_IO);
    }
    return text;
}


const char* Gd5f1gq5RegProtectionToStr(const void * const memory){
    Gd5f1gq5RegProtection_t *pReg = (Gd5f1gq5RegProtection_t *)memory;
    strcpy(text, "");
    if(pReg) {
        snprintf(text, sizeof(text), "%sCMP:%u,", text, pReg->CMP);
        snprintf(text, sizeof(text), "%sINV:%u,", text, pReg->INV);
        snprintf(text, sizeof(text), "%sBP:%u,", text, pReg->BP);
        snprintf(text, sizeof(text), "%sBRWD:%u", text, pReg->BRWD);
    }
    return text;
}


const char* Gd5f1gq5RegFeatureB0ToStr(const void * const memory){
    Gd5f1gq5RegFeatureB0_t *pReg = (Gd5f1gq5RegFeatureB0_t *)memory;
    strcpy(text, "");
    if(pReg) {
        snprintf(text, sizeof(text), "%sQE:%u,", text, pReg->QE);
        snprintf(text, sizeof(text), "%sBPL:%u,", text, pReg->BPL);
        snprintf(text, sizeof(text), "%sECC_EN:%u,", text, pReg->ECC_EN);
        snprintf(text, sizeof(text), "%sOTP_EN:%u,", text, pReg->OTP_EN);
        snprintf(text, sizeof(text), "%sOTP_PRT:%u", text, pReg->OTP_PRT);
    }
    return text;
}

const char* Gd5f1gq5RowAddressToStr(const Gd5f1gq5RowAddress_t *const Node){
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sRowAddr:0x%04x,", text, Node->row_address);
        snprintf(text, sizeof(text), "%sBlock:%u,", text, Node->block);
        snprintf(text, sizeof(text), "%sPage:%u,", text, Node->page);
    }
    return text;
}

const char* Gd5f1gq5PhyAddrToStr(const Gd5f1gq5PhyAddress_t * const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sPhyAddr:0x%08x,", text, Node->phy_address);
        snprintf(text, sizeof(text), "%sBlock:%u,", text, Node->block_num);
        snprintf(text, sizeof(text), "%spageInBlock:%u,", text, Node->page_in_block);
        snprintf(text, sizeof(text), "%scolumnAddress:%u,", text, Node->column_address);
    }
    return text;
}

const char* Gd5f1gq5PhyAddressToStr(const uint32_t phy_address) {
    strcpy(text, "");
    Gd5f1gq5PhyAddress_t PhyAddress = { 0 };
    PhyAddress.phy_address = phy_address;
    const char *name = "?";
    name = Gd5f1gq5PhyAddrToStr(&PhyAddress);
    return name;
}

const char* Gd5f1gq5RegStatusC0ToStr(const void * const memory){
    Gd5f1gq5RegStatusC0_t *pReg = (Gd5f1gq5RegStatusC0_t *)memory;
    strcpy(text, "");
    if(pReg) {
        snprintf(text, sizeof(text), "%sOIP:%u,", text, pReg->OIP);
        snprintf(text, sizeof(text), "%sWEL:%u,", text, pReg->WEL);
        snprintf(text, sizeof(text), "%sE_FAIL:%u,", text, pReg->E_FAIL);
        snprintf(text, sizeof(text), "%sP_FAIL:%u,", text, pReg->P_FAIL);
        snprintf(text, sizeof(text), "%sECCS:%u,", text, pReg->ECCS);
    }
    return text;
}

const char* Gd5f1gq5RegStatusF0ToStr(const void * const memory) {
    Gd5f1gq5RegStatusF0_t *pReg = (Gd5f1gq5RegStatusF0_t *)memory;
    strcpy(text, "");
    if(pReg) {
        snprintf(text, sizeof(text), "%sBPS:%u,", text, pReg->BPS);
        snprintf(text, sizeof(text), "%sECCSE:%u,", text, pReg->ECCSE);
    }
    return text;
}

bool Gd5f1gq5DiagStatusF0( const Gd5f1gq5RegStatusF0_t* const Node) {
    bool res = true;
    LOG_WARNING(GD5F1GQ5,"Val:0x%02x",Node->byte);
    LOG_INFO(GD5F1GQ5,"BPS:%u",Node->BPS);
    LOG_INFO(GD5F1GQ5,"ECCSE:%u",Node->ECCSE);
    return res;
}

bool Gd5f1gq5DiagStatusC0(const Gd5f1gq5RegStatusC0_t* const Node) {
    bool res = true;
    LOG_WARNING(GD5F1GQ5, "Val:0x%02x", Node->byte);
    LOG_INFO(GD5F1GQ5, "OIP:%u", Node->OIP);
    LOG_INFO(GD5F1GQ5, "ECCS:%u", Node->ECCS);
    LOG_INFO(GD5F1GQ5, "WEL:%u", Node->WEL);
    LOG_INFO(GD5F1GQ5, "E_FAIL:%u", Node->E_FAIL);
    LOG_INFO(GD5F1GQ5, "P_FAIL:%u", Node->P_FAIL);
    LOG_INFO(GD5F1GQ5, "ECCS:%u", Node->ECCS);
    return res;
}

bool Gd5f1gq5DiagFeatureB0( const Gd5f1gq5RegFeatureB0_t* const  Node) {
    bool res = true;
    LOG_WARNING(GD5F1GQ5, "Val:0x%02x", Node->byte);
    LOG_INFO(GD5F1GQ5, "QE:%u", Node->QE);
    LOG_INFO(GD5F1GQ5, "BPL:%u", Node->BPL);
    LOG_INFO(GD5F1GQ5, "ECC_EN:%u", Node->ECC_EN);
    LOG_INFO(GD5F1GQ5, "OTP_EN:%u", Node->OTP_EN);
    LOG_INFO(GD5F1GQ5, "OTP_PRT:%u", Node->OTP_PRT);
    return res;
}


bool Gd5f1gq5DiagProtection( const Gd5f1gq5RegProtection_t* const  Node) {
    bool res = true;
    LOG_WARNING(GD5F1GQ5, "Val:0x%02x", Node->byte);
    LOG_INFO(GD5F1GQ5, "CMP:%u", Node->CMP);
    LOG_INFO(GD5F1GQ5, "INV:%u", Node->INV);
    LOG_INFO(GD5F1GQ5, "BP:%u", Node->BP);
    LOG_INFO(GD5F1GQ5, "BRWD:%u", Node->BRWD);
    return res;
}

bool Gd5f1gq5DiagDriverStrength( const Gd5f1gq5RegDriverStrength_t* const  Node) {
    bool res = true;
    LOG_WARNING(GD5F1GQ5, "Val:0x%02x", Node->byte);
    LOG_INFO(GD5F1GQ5, "DS_IO:%u", Node->DS_IO);
    return res;
}

bool gd5f1gq5_raw_reg_diag(uint8_t num) {
    bool res = false;
    Gd5f1gq5Handle_t* Node = Gd5f1gq5GetNode(num);
    if(Node) {
        res= gd5f1gq5_get_features(num,  GD5F1GQ5_REG_PROTECTION_A0H, &Node->Protection.byte) ;
        Gd5f1gq5DiagProtection(&Node->Protection);

        res= gd5f1gq5_get_features(num,  GD5F1GQ5_REG_FEATURE_B0H, &Node->FeatureB0.byte) ;
        Gd5f1gq5DiagFeatureB0(&Node->FeatureB0);

        res= gd5f1gq5_get_features(num,  GD5F1GQ5_REG_STATUS_C0H, &Node->StatusC0.byte) ;
        Gd5f1gq5DiagStatusC0(&Node->StatusC0);

        res= gd5f1gq5_get_features(num,  GD5F1GQ5_REG_FEATURE_D0H, &Node->DriverStrength.byte) ;
        Gd5f1gq5DiagDriverStrength(&Node->DriverStrength);

        res= gd5f1gq5_get_features(num,  GD5F1GQ5_REG_STATUS_F0H, &Node->StatusF0.byte) ;
        Gd5f1gq5DiagStatusF0(&Node->StatusF0);

    }
    return res;
}


const char* Gd5f1gq5ParameterPageToStr(const Gd5f1gq5ParameterPage_t * const Node){
    static char lText[512];
    strcpy(lText, "");
    if(Node){
        snprintf(lText, sizeof(lText), "%sVendorRev:0x%04x,", lText, Node->vendor_revision);
    }
    return lText;
}

bool gd5f1gq5_get_features_diag(uint8_t num) {
    bool res = false;
    static const table_col_t cols[] = {
            { 4, "No" },
            { 6, "addr" },
            { 6, "data" },
            { 13, "dataBin" },
            { 12, "RegName" },
            { 12, "ValueExplained" },
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t addr = 0;
    for (addr = 0; addr < 0xFF; addr++) {
        uint8_t data = 0;
        res = gd5f1gq5_get_features(num, (uint8_t) addr, &data);
        char temp[150] = "";
        strcpy(temp, TSEP);
        snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, num);
        snprintf(temp, sizeof(temp), "%s 0x%02x " TSEP, temp, (uint8_t) addr);
        snprintf(temp, sizeof(temp), "%s 0x%02x " TSEP, temp, data);
        snprintf(temp, sizeof(temp), "%s 0b%s " TSEP, temp, utoa_bin8(data));
        Gd5f1gq5RegInfo_t *Info = Gd5f1gq5RegAddrToInfo((uint8_t) addr);
        if(Info) {
            snprintf(temp, sizeof(temp), "%s %10s " TSEP, temp, Info->reg_name);
            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, Info->regParserCallBack(&data));
            cli_printf("%s" CRLF, temp);
            res = true;
        } else {
            LOG_DEBUG(GD5F1GQ5, "%s", temp);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}



bool Gd5f1gq5ParameterPageMemoryOrganizationDiag(const Gd5f1gq5ParameterPage_t* const Page) {
    bool res = true;
    LOG_INFO(GD5F1GQ5, "---------- Memory Organization ----------");

    // Memory organization (bytes 80-127)
    LOG_INFO(GD5F1GQ5, "spare_bytes_per_page:%u bytes", Page->spare_bytes_per_page);
    LOG_INFO(GD5F1GQ5, "data_bytes_per_partial_page:%u bytes", Page->data_bytes_per_partial_page);
    LOG_INFO(GD5F1GQ5, "spare_bytes_per_partial_page:%u bytes", Page->spare_bytes_per_partial_page);
    LOG_INFO(GD5F1GQ5, "bits_per_cell:%u", Page->bits_per_cell);
    LOG_INFO(GD5F1GQ5, "max_bad_blocks:%u blocks", Page->max_bad_blocks);
    LOG_INFO(GD5F1GQ5, "block_endurance:%u cycles", Page->block_endurance);
    LOG_INFO(GD5F1GQ5, "guaranteed_valid_blocks:%u", Page->guaranteed_valid_blocks);
    LOG_INFO(GD5F1GQ5, "endurance_guaranteed_blocks:%u", Page->endurance_guaranteed_blocks);
    LOG_INFO(GD5F1GQ5, "programs_per_page:%u", Page->programs_per_page);
    LOG_INFO(GD5F1GQ5, "partial_program_attrs:0x%02X", Page->partial_program_attrs);
    LOG_INFO(GD5F1GQ5, "ecc_correctability_bits:%u bits", Page->ecc_correctability_bits);
    LOG_INFO(GD5F1GQ5, "ECC capability:%u bits per page", Page->ecc_correctability_bits);
    LOG_INFO(GD5F1GQ5, "interleaved_addr_bits:0x%02X", Page->interleaved_addr_bits);
    LOG_INFO(GD5F1GQ5, "interleaved_attrs:0x%02X", Page->interleaved_attrs);
    return res;
}

bool Gd5f1gq5ParameterPageCapacityDiag(const Gd5f1gq5ParameterPage_t* const Page) {
    LOG_INFO(GD5F1GQ5, "---------- Capacity ----------");
    LOG_INFO(GD5F1GQ5, "bytes_per_page:%u bytes", Page->bytes_per_page);
    LOG_INFO(GD5F1GQ5, "pages_per_block:%u pages", Page->pages_per_block);
    LOG_INFO(GD5F1GQ5, "num_luns:%u", Page->num_luns);
    LOG_INFO(GD5F1GQ5, "blocks_per_lun:%u blocks", Page->blocks_per_lun);
    // Calculate total device size
    uint32_t total_bytes = (uint32_t) Page->bytes_per_page * Page->pages_per_block * Page->blocks_per_lun
            * Page->num_luns;
    uint32_t total_mbits = (total_bytes * 8) / (1024 * 1024);
    uint32_t total_mbytes = total_bytes / (1024 * 1024);

    LOG_INFO(GD5F1GQ5, "TotalDeviceSize:%u bytes (%u MB, %u Mbit)", total_bytes, total_mbytes, total_mbits);
    return true;
}

bool Gd5f1gq5ParameterPageVendorDiag(const Gd5f1gq5ParameterPage_t* const Page) {
    bool res = true;

    LOG_INFO(GD5F1GQ5, "---------- Vendor Block ----------");
    // Manufacturer (bytes 32-43)
    LOG_INFO(GD5F1GQ5, "manufacturer:[%s]", Page->manufacturer);
    // Device model (bytes 44-63)
    LOG_INFO(GD5F1GQ5, "device_model:[%s]", Page->device_model);
    // Revision (bytes 4-5)
    LOG_INFO(GD5F1GQ5, "revision:0x%04X", Page->revision);
    // JEDEC manufacturer ID (byte 64)
    LOG_INFO(GD5F1GQ5, "jedec_manufacturer_id:0x%02X", Page->jedec_manufacturer_id);

    // Vendor block (bytes 164-255)
    LOG_INFO(GD5F1GQ5, "vendor_revision:0x%04X", Page->vendor_revision);
    // Print first few bytes of vendor specific data (bytes 166-253)
    LOG_INFO(GD5F1GQ5, "vendor_specific (first 16 bytes):");
    LOG_INFO(GD5F1GQ5, "VendorSpecific:[%s]", ArrayToStr(Page->vendor_specific, 48));
    LOG_INFO(GD5F1GQ5, "date_code:0x%04X", Page->date_code);
    return res;
}

bool Gd5f1gq5ParameterPageElectricalDiag(const Gd5f1gq5ParameterPage_t* const Page) {

    LOG_INFO(GD5F1GQ5, "---------- Electrical Parameters ----------");

    // Electrical parameters (bytes 128-163)
    LOG_INFO(GD5F1GQ5, "io_capacitance:%u pF", Page->io_capacitance);
    LOG_INFO(GD5F1GQ5, "io_clock_support:0x%04X", Page->io_clock_support);
    LOG_INFO(GD5F1GQ5, "Maximum page program time:%u us", Page->tPROG_max_us);
    LOG_INFO(GD5F1GQ5, "Maximum block erase time:%u us", Page->tBERS_max_us);
    LOG_INFO(GD5F1GQ5, "Maximum page read time:%u us", Page->tR_max_us);
    return true;
}

bool Gd5f1gq5ParameterPageDiag(const Gd5f1gq5ParameterPage_t* const Page) {
    bool res = false;
    if(Page) {
        res = true;
        LOG_INFO(GD5F1GQ5, "========== GD5F1GQ5 Parameter Page Diagnostic ==========");
        LOG_INFO(GD5F1GQ5, "signature:[%c%c%c%c]",
                ((uint8_t*) &Page->signature)[0],
                ((uint8_t*) &Page->signature)[1],
                ((uint8_t*) &Page->signature)[2],
                ((uint8_t*) &Page->signature)[3]);
        Gd5f1gq5ParameterPageCapacityDiag(Page);
        Gd5f1gq5ParameterPageVendorDiag(Page);

        LOG_INFO(GD5F1GQ5, "features_supported:0x%04X", Page->features_supported);
        Gd5f1gq5ParameterPageMemoryOrganizationDiag(Page);
        Gd5f1gq5ParameterPageElectricalDiag(Page);
        LOG_INFO(GD5F1GQ5, "ReadCrc16:0x%04X", Page->crc16);
        LOG_INFO(GD5F1GQ5, "=========================================================");
    }
    return res;
}

bool gd5f1gq5_read_block(uint8_t num, uint32_t block_num) {
    bool res = false;
    LOG_WARNING(GD5F1GQ5, "ShowBlock:%u", block_num);
    uint32_t p = 0;
    uint32_t block_start_offset = num * GD5F1GQ5_PAGE_SIZE;
    for (p = 0; p < GD5F1GQ5_PAGES_PER_BLOCK; p++) {
        uint8_t pageData[GD5F1GQ5_PAGE_SIZE];
        memset(pageData, 0, sizeof(pageData));
        uint32_t page_address = block_start_offset + p * GD5F1GQ5_PAGE_SIZE;
        LOG_INFO(GD5F1GQ5, "Block:%u,Page:%u,Addr:0x%08x=%u", block_num, p, page_address, page_address);
        res = gd5f1gq5_read_page(num, block_start_offset + p * GD5F1GQ5_PAGE_SIZE, pageData, sizeof(pageData));
        if(res) {
            print_hex(pageData, sizeof(pageData));
        }
    }
    return res;
}
