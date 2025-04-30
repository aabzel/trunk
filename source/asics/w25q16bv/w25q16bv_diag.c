#include "w25q16bv_diag.h"

#include <stdio.h>

#include "convert.h"
#ifdef HAS_LOG
#include "log.h"
#endif
#include "common_diag.h"
#include "debug_info.h"
#include "w25q16bv_drv.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

const char* Wip2Str(W25Wip_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case W25_WIP_NOT_IN_WRITE_OPERATION:
        name = "NotWrOp";
        break;
    case W25_WIP_WRITE_OPERATION:
        name = "WrOp";
        break;
    }
    return name;
}

const char* Wel2Str(W25Wel_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case W25_WEL_WRITE_ENABLE:
        name = "WrEnable";
        break;
    case W25_WEL_NOT_WRITE_ENABLE:
        name = "WrDisable";
        break;
    }
    return name;
}

const char* BlockProt2Str(W25ProtAria_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case W25_PROT_ARIA_NONE:
        name = "none";
        break;
    case W25_PROT_ARIA_1BLOCK:
        name = "1";
        break;
    case W25_PROT_ARIA_2BLOCKS:
        name = "2";
        break;
    case W25_PROT_ARIA_4BLOCKS:
        name = "4";
        break;
    case W25_PROT_ARIA_8BLOCKS:
        name = "8";
        break;
    case W25_PROT_ARIA_16BLOCKS:
        name = "16";
        break;
    case W25_PROT_ARIA_32BLOCKS:
        name = "32";
        break;
    case W25_PROT_ARIA_64BLOCKS:
        name = "64";
        break;
    case W25_PROT_ARIA_128BLOCKS_1:
        name = "128";
        break;
    case W25_PROT_ARIA_128BLOCKS_2:
        name = "128";
        break;
    case W25_PROT_ARIA_128BLOCKS_3:
        name = "128";
        break;
    case W25_PROT_ARIA_128BLOCKS_4:
        name = "128";
        break;
    case W25_PROT_ARIA_128BLOCKS_5:
        name = "128";
        break;
    case W25_PROT_ARIA_128BLOCKS_6:
        name = "128";
        break;
    case W25_PROT_ARIA_128BLOCKS_7:
        name = "128";
        break;
    case W25_PROT_ARIA_128BLOCKS_8:
        name = "128";
        break;
    }
    return name;
}

const char* Quad2Str(W25Quad_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case W25_QUAD_ENABLE:
        name = "QuadEnable";
        break;
    case W25_NOT_QUAD_ENABLE:
        name = "QuadDisable";
        break;
    }
    return name;
}

const char* Srwd2Str(W25Srwd_t code) {
    char* name = "?";
    switch((uint8_t)code) {
    case W25_STATUS_REG_WR_PROT_DISABLE:
        name = "disabled";
        break;
    case W25_STATUS_REG_WR_PROT_ENABLE:
        name = "enabled";
        break;
    }
    return name;
}

bool mx25_diag_status(RegStatus_t* reg) {
    bool res = false;
    if(reg) {
        LOG_INFO(W25Q16BV, "Status 0x%x=%s", reg->byte, utoa_bin8(reg->byte));

        LOG_INFO(W25Q16BV, "writeProg %u=%s", reg->wip, Wip2Str(reg->wip));
        LOG_INFO(W25Q16BV, "write %u=%s", reg->wel, Wel2Str(reg->wel));
        LOG_INFO(W25Q16BV, "levelOfProtBlock %u=%s", reg->bp, BlockProt2Str(reg->bp));
        LOG_INFO(W25Q16BV, "Quad %u=%s", reg->qe, Quad2Str(reg->qe));
        LOG_INFO(W25Q16BV, "StatRegWrProt %u=%s", reg->srwd, Srwd2Str(reg->srwd));
    }
    return res;
}

bool mx25_diag_id(RegIdentification_t* reg) {
    bool res = false;
    if(reg) {
        LOG_INFO(W25Q16BV, "ManufId 0x%x", reg->manufacturer_id);
        LOG_INFO(W25Q16BV, "DevId 0x%x", reg->device_id.word);
        LOG_INFO(W25Q16BV, "MemoryDensity 0x%x", reg->device_id.memory_density);
        LOG_INFO(W25Q16BV, "MemoryType 0x%x", reg->device_id.memory_type);
    }
    return res;
}

bool mx25_diag_configuration(RegConfiguration_t* configuration) {
    bool res = false;
    if(configuration) {
    }
    return res;
}

bool w25q16bv_diag(void) {
    bool res = false;

    w25q16bv_status_reg_read();

    LOG_WARNING(W25Q16BV, "DiagLL");
    LOG_INFO(W25Q16BV, "ElectronicSignature 0x%x", W25q16bvItem.electronic_signature);
    res = mx25_diag_id(&W25q16bvItem.identification);
    res = mx25_diag_status(&W25q16bvItem.status);
    res = mx25_diag_configuration(&W25q16bvItem.configuration);

    res = min_max_diag(&W25q16bvItem.write_time_ms, "WaitWrite");
    return res;
}

bool w25q16bv_diag_high_level(void) {
    bool res = false;
    LOG_WARNING(W25Q16BV, "DiagHL");

    return res;
}

bool w25q16bv_usage(uint32_t piece_size) {
    bool res = false;
    char line_str[120];
    uint32_t busy = 0;
    double usage_pec = 0.0f;
    uint32_t spare = 0;
    uint32_t num = 0;
    uint32_t piece_cnt = W25Q16BV_FLASH_SIZE / piece_size;
    LOG_WARNING(W25Q16BV, "PieceCnt %u", piece_cnt);

    static const table_col_t cols[] = {{6, "num"}, {11, "Start"}, {11, "End"}, {7, "cont"}, {8, "Use"}};

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t flash_addr = 0;
    for(flash_addr = 0; flash_addr < W25Q16BV_FLASH_SIZE; flash_addr += piece_size) {
        strcpy(line_str, TSEP);
        snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr);
        snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr + piece_size);

        w25q16bv_scan(flash_addr, piece_size, &usage_pec, &spare, &busy);
        snprintf(line_str, sizeof(line_str), "%s %6s" TSEP, line_str, (piece_size == spare) ? "spare" : "busy");
        snprintf(line_str, sizeof(line_str), "%s %6.2f " TSEP, line_str, usage_pec);

        wait_in_loop_ms(2);
        cli_printf(TSEP " %4u ", num);
        cli_printf("%s" CRLF, line_str);
        num++;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
