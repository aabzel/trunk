#include "mx25l6433f_diag.h"

#include <stdio.h>

#include "convert.h"
#include "common_diag.h"
#include "debug_info.h"
#include "mx25l6433f_mcal.h"
#include "none_blocking_pause.h"
#include "mx25l6433f_config.h"
#include "table_utils.h"
#include "writer_config.h"
#include "gpio_diag.h"

#ifdef HAS_LOG
#include "log.h"
#endif

const char* WipToStr(Mx25Wip_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case MX25_WIP_NOT_IN_WRITE_OPERATION:
        name = "NotWrOp";
        break;
    case MX25_WIP_WRITE_OPERATION:
        name = "WrOp";
        break;
    default:break;
    }
    return name;
}

const char* WelToStr(Mx25Wel_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case MX25_WEL_WRITE_ENABLE:
        name = "WrEnable";
        break;
    case MX25_WEL_NOT_WRITE_ENABLE:
        name = "WrDisable";
        break;
    default:break;
    }
    return name;
}

const char* BlockProtToStr(Mx25ProtAria_t code) {
    char* name = "?";
    switch(code) {
    case MX25_PROT_ARIA_NONE:
        name = "none";
        break;
    case MX25_PROT_ARIA_1BLOCK:
        name = "1";
        break;
    case MX25_PROT_ARIA_2BLOCKS:
        name = "2";
        break;
    case MX25_PROT_ARIA_4BLOCKS:
        name = "4";
        break;
    case MX25_PROT_ARIA_8BLOCKS:
        name = "8";
        break;
    case MX25_PROT_ARIA_16BLOCKS:
        name = "16";
        break;
    case MX25_PROT_ARIA_32BLOCKS:
        name = "32";
        break;
    case MX25_PROT_ARIA_64BLOCKS:
        name = "64";
        break;
    case MX25_PROT_ARIA_128BLOCKS_1:
        name = "128";
        break;
    case MX25_PROT_ARIA_128BLOCKS_2:
        name = "128";
        break;
    case MX25_PROT_ARIA_128BLOCKS_3:
        name = "128";
        break;
    case MX25_PROT_ARIA_128BLOCKS_4:
        name = "128";
        break;
    case MX25_PROT_ARIA_128BLOCKS_5:
        name = "128";
        break;
    case MX25_PROT_ARIA_128BLOCKS_6:
        name = "128";
        break;
    case MX25_PROT_ARIA_128BLOCKS_7:
        name = "128";
        break;
    case MX25_PROT_ARIA_128BLOCKS_8:
        name = "128";
        break;
    default:break;
    }
    return name;
}

const char* QuadToStr(Mx25Quad_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case MX25_QUAD_ENABLE:
        name = "QuadEnable";
        break;
    case MX25_NOT_QUAD_ENABLE:
        name = "QuadDisable";
        break;
    default:break;
    }
    return name;
}

const char* SrwdToStr(Mx25Srwd_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case MX25_STATUS_REG_WR_PROT_DISABLE:
        name = "disabled";
        break;
    case MX25_STATUS_REG_WR_PROT_ENABLE:
        name = "enabled";
        break;
    default:break;
    }
    return name;
}

bool mx25_diag_status(Mx25l6433fRegStatus_t* reg) {
    bool res = false;
    if(reg) {
        LOG_INFO(MX25L6433F, "Status 0x%x=%s", reg->byte, utoa_bin8(reg->byte));

        LOG_INFO(MX25L6433F, "writeProg %u=%s", reg->wip, WipToStr(reg->wip));
        LOG_INFO(MX25L6433F, "write %u=%s", reg->wel, WelToStr(reg->wel));
        LOG_INFO(MX25L6433F, "levelOfProtBlock %u=%s", reg->bp, BlockProtToStr(reg->bp));
        LOG_INFO(MX25L6433F, "Quad %u=%s", reg->qe, QuadToStr(reg->qe));
        LOG_INFO(MX25L6433F, "StatRegWrProt %u=%s", reg->srwd, SrwdToStr(reg->srwd));
    }
    return res;
}

bool mx25_diag_id( Mx25l6433fRegIdentification_t* reg) {
    bool res = false;
    if(reg) {
        LOG_INFO(MX25L6433F, "ManufId 0x%x", reg->manufacturer_id);
        LOG_INFO(MX25L6433F, "DevId 0x%x", reg->device_id.word);
        LOG_INFO(MX25L6433F, "MemoryDensity 0x%x", reg->device_id.memory_density);
        LOG_INFO(MX25L6433F, "MemoryType 0x%x", reg->device_id.memory_type);
    }
    return res;
}

bool mx25_diag_configuration(uint8_t num,Mx25l6433fRegConfiguration_t* configuration) {
    bool res = false;
    if(configuration) {
    }
    return res;
}

bool mx25l6433f_diag_one(uint8_t num) {
    bool res = false;

    mx25l6433f_status_reg_read(num);

    LOG_WARNING(MX25L6433F, "DiagLL");
    LOG_INFO(MX25L6433F, "ElectronicSignature 0x%x", Mx25l6433fInstance[0].electronic_signature);
    res = mx25_diag_id(&Mx25l6433fInstance[0].identification);
    res = mx25_diag_status(&Mx25l6433fInstance[0].status);
    res = mx25_diag_configuration(num,&Mx25l6433fInstance[0].configuration);

    res = min_max_diag(&Mx25l6433fInstance[0].write_time_ms, "WaitWrite");
    return res;
}

bool mx25l6433f_diag(void) {
    bool res = false;
    return res;
}

bool mx25l6433f_diag_high_level(uint8_t num) {
    bool res = false;
    LOG_WARNING(MX25L6433F, "DiagHL");

    return res;
}

bool mx25l6433f_usage(uint8_t num,uint32_t piece_size) {
    bool res = false;
    char line_str[120];
    uint32_t busy = 0;
    double usage_pec = 0.0f;
    uint32_t spare = 0;
    uint32_t num_c = 0;
    uint32_t piece_cnt = MX25L6433F_FLASH_SIZE / piece_size;
    LOG_WARNING(MX25L6433F, "PieceCnt %u", piece_cnt);

    static const table_col_t cols[] = {{6, "num"}, {11, "Start"}, {11, "End"}, {7, "cont"}, {8, "Use"}};

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t flash_addr = 0;
    for(flash_addr = 0; flash_addr < MX25L6433F_FLASH_SIZE; flash_addr += piece_size) {
        strcpy(line_str, TSEP);
        snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr);
        snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr + piece_size);

        mx25l6433f_scan(num, flash_addr, piece_size, &usage_pec, &spare, &busy);
        snprintf(line_str, sizeof(line_str), "%s %6s" TSEP, line_str, (piece_size == spare) ? "spare" : "busy");
        snprintf(line_str, sizeof(line_str), "%s %6.2f " TSEP, line_str, usage_pec);

        wait_in_loop_ms(2);
        cli_printf(TSEP " %4u ", num_c);
        cli_printf("%s" CRLF, line_str);
        num_c++;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}



const char* Mx25l6433fConfigToStr(const Mx25l6433fConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sSPI%u,", text, Config->spi_num);
        snprintf(text, sizeof(text), "%sCS:%s,", text, GpioPadToStr(Config->chip_select));
        snprintf(text, sizeof(text), "%sWP:%s,", text, GpioPadToStr(Config->write_protection));
        snprintf(text, sizeof(text), "%sRST:%s,", text, GpioPadToStr(Config->reset));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}


const char* Mx25l6433fNodeToStr(const Mx25l6433fHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}
