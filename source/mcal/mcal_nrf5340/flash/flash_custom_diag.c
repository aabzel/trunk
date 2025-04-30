#include "flash_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "flash_mcal.h"
#include "flash_custom_const.h"
#include "data_utils.h"
#include "log_utils.h"
#include "writer_config.h"
#include "table_utils.h"
#include "none_blocking_pause.h"
#include "str_utils.h"


bool diag_flash_usage(char* key_word1, char* key_word2) {
    bool res = false;
    uint32_t flash_addr = ON_CHIP_NOR_FLASH_START, num = 0;
    char line_str[120];
    uint32_t spare = 0;
    bool is_print = false;
    uint32_t busy = 0;
    float usage_pec = 0.0f;
    static const table_col_t cols[] = {{5, "num"},   {11, "Start"}, {11, "End"},
                                        {7, "cont"},   {8, "Use"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(flash_addr = 0; flash_addr < ON_CHIP_NOR_FLASH_SIZE; flash_addr += ON_CHIP_NOR_FLASH_PAGE_SIZE) {
        strcpy(line_str, TSEP);
        snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr);
        snprintf(line_str, sizeof(line_str), "%s 0x%08x" TSEP, line_str, flash_addr + ON_CHIP_NOR_FLASH_PAGE_SIZE);
        flash_scan((uint8_t*)flash_addr, ON_CHIP_NOR_FLASH_PAGE_SIZE, &usage_pec, &spare, &busy);
        snprintf(line_str, sizeof(line_str), "%s %6s" TSEP, line_str, (ON_CHIP_NOR_FLASH_PAGE_SIZE == spare) ? "spare" : "busy");
        snprintf(line_str, sizeof(line_str), "%s %6.2f " TSEP, line_str, usage_pec);
        // snprintf(line_str, sizeof(line_str), "%s", line_str);
        is_print = is_contain(line_str, key_word1, key_word2);
        if(is_print) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s"CRLF, line_str);
            wait_in_loop_ms(2);
            num++;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

