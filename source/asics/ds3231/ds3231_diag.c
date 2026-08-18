#include "ds3231_diag.h"

#include <stdbool.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "ds3231_drv.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool diag_ds3231(uint8_t num, char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"}, {6, "addr"}, {6, "valHex"}, {13, "valBin"}, {14, "name"}};
    uint16_t cnt = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint8_t i = 0;
    char temp_str[120];
    uint16_t reg_cnt = ds3231_get_reg_cnt();
    for(i = 0; i < reg_cnt; i++) {
        uint8_t reg_val = 0;
        res = ds3231_get_reg(num, Ds3231RegMapStatic[i].reg_addr, &reg_val);
        if(res) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%02x " TSEP, temp_str, Ds3231RegMapStatic[i].reg_addr);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%02x " TSEP, temp_str, reg_val);
            snprintf(temp_str, sizeof(temp_str), "%s 0b%9s " TSEP, temp_str, utoa_bin8(reg_val));
            snprintf(temp_str, sizeof(temp_str), "%s %12s " TSEP, temp_str, Ds3231RegMapStatic[i].name);

            if(is_contain(temp_str, key_word1, key_word2)) {
                cli_printf(TSEP " %3u ", cnt);
                cli_printf("%s" CRLF, temp_str);
                cnt++;
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

const char* HourModeToStr(HourMode_t hour_mode) {
    const char* name = "?";
    switch((uint8_t)hour_mode) {
    case HOUR_MODE_24H:
        name = "24H";
        break;
    case HOUR_MODE_12H:
        name = "12H";
        break;
    default:
        break;
    }
    return name;
}
