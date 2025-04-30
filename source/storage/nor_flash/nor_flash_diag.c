#include "nor_flash_diag.h"

#include <stdio.h>

#include "array_diag.h"
#include "common_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "none_blocking_pause.h"
#include "nor_flash_drv.h"
#include "table_utils.h"
#include "writer_config.h"
#ifdef HAS_LOG
#include "log.h"
#endif

bool nor_flash_diag(uint8_t flash_num) {
    bool res = false;

    return res;
}

bool nor_flash_usage(uint8_t flash_num, uint32_t piece_size) {
    bool res = false;
    char line_str[120];
    uint32_t busy = 0;
    double usage_pec = 0.0f;
    uint32_t spare = 0;
    uint32_t num = 0;
    NorFlashItem_t* Node = NorFlashGetNode(flash_num);
    if(Node) {

        uint32_t piece_cnt = Node->size / piece_size;
        LOG_WARNING(NOR_FLASH, "%u PieceCnt %u", flash_num, piece_cnt);

        static const table_col_t cols[] = {{6, "num"}, {11, "Start"}, {11, "End"}, {7, "Cont"}, {8, "Use"}};

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t flash_addr = 0;
        for(flash_addr = Node->start; flash_addr < (Node->start + Node->size); flash_addr += piece_size) {
            strcpy(line_str, TSEP);
            snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr);
            snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr + piece_size);

            nor_flash_scan(flash_num, flash_addr, piece_size, &usage_pec, &spare, &busy);
            snprintf(line_str, sizeof(line_str), "%s %6s" TSEP, line_str, (piece_size == spare) ? "spare" : "busy");
            snprintf(line_str, sizeof(line_str), "%s %6.2f " TSEP, line_str, usage_pec);

            wait_in_loop_ms(2);
            cli_printf(TSEP " %4u ", num);
            cli_printf("%s" CRLF, line_str);
            num++;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}

const char* NorFlashOption2Str(NorFlashOption_t code) {
    const char* name = "UndefNorFlash";
    switch((uint8_t)code) {
    case NOR_FLASH_OPTION_SW:
        name = "NorFlashSW";
        break;
    case NOR_FLASH_OPTION_ON_CHIP:
        name = "NorFlashOnChip";
        break;
    case NOR_FLASH_OPTION_OFF_CHIP:
        name = "NorFlashOffChip";
        break;
    default:
        break;
    }
    return name;
}

const char* NorFlashNum2Option(uint8_t flash_num) {
    const char* name = "UndefNode";
    LOG_INFO(NOR_FLASH, "FindNode %u", flash_num);
    NorFlashItem_t* Node = NorFlashGetNode(flash_num);
    if(Node) {
        name = NorFlashOption2Str(Node->option);
    } else {
        LOG_ERROR(NOR_FLASH, "LackOfNode %u", flash_num);
    }
    return name;
}

bool nor_flash_mem_diag(uint8_t flash_num, uint32_t phy_address, uint32_t size, char* name) {
    bool res = false;
    uint8_t buff[64];
    memset(buff, 0, sizeof(buff));
    if(size < sizeof(buff)) {
        LOG_INFO(NOR_FLASH, "%s:", name);
        res = nor_flash_read(flash_num, phy_address, buff, size);
        if(res) {
            print_hex(buff, size);
        }
    }
    return res;
}
