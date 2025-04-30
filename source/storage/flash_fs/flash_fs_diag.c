#include "flash_fs_diag.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bit_utils.h"
#include "common_diag.h"
#include "convert.h"
#include "crc8_autosar.h"
#include "data_utils.h"
#include "debug_info.h"
#include "flash_fs.h"
#include "flash_fs_config.h"
#include "flash_fs_ll.h"
#include "log.h"
#include "log_utils.h"
#include "none_blocking_pause.h"
#include "nvs_const.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool flash_fs_diag(void) {
    bool res = false;
    uint8_t page_num = 0;
    static const table_col_t cols[] = {
        {5, "page"}, {12, "base"}, {7, "active"}, {7, "size"}, {6, "files"}, {7, "spare"}, {8, "usage"},
    };
    uint32_t spare_cnt = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char log_line[120];
    for(page_num = 1; page_num <= 2; page_num++) {
        spare_cnt = 0;
        uint32_t page_base_addr = flash_fs_get_page_base_addr(page_num);
        uint32_t page_len = flash_fs_get_page_size(page_num);
        uint32_t files = flash_fs_cnt_files(page_base_addr, page_len, &spare_cnt);
        double usage_pre_cent = 100.0 - ((100.0 * ((double)spare_cnt)) / ((double)page_len));
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, page_num);
        snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, page_base_addr);
        snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, OnOff2Str(flash_fs_is_active(page_num)));
        snprintf(log_line, sizeof(log_line), "%s %u " TSEP, log_line, page_len);
        snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, files);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, spare_cnt);
        snprintf(log_line, sizeof(log_line), "%s %6.2f " TSEP, log_line, usage_pre_cent);

        cli_printf("%s" CRLF, log_line);

        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

#ifdef HAS_FLASH_FS_EXT_COMMANDS
bool flash_fs_scan(uint32_t start_page_addr, uint32_t page_len, char* key_word1, char* key_word2) {
    bool res = false;
    bool out_res = false;
    FlashFsHeader_t* item = NULL;
    uint32_t rem_size = 0;
    uint16_t num = 0;
    uint32_t cur_offset = start_page_addr;
    uint32_t file_cnt = 0;
    char temp_str[120];
    LOG_INFO(FLASH_FS, "Page 0x%08x...0x%08x", start_page_addr, start_page_addr + page_len);
    uint8_t* payload = NULL;
    static const table_col_t cols[] = {{5, "num"}, {7, "id"}, {7, "len"}, {6, "crc"}, {10, "addr"}, {8, "data"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t data[50] = "";
    for(cur_offset = start_page_addr; cur_offset <= (start_page_addr + page_len - MIN_FILE_LEN); cur_offset++) {
        /* reference item */
        res = true;
        item = (FlashFsHeader_t*)cur_offset;

        /*is valid id*/
        if(item->id != (MASK_16BIT ^ item->nid)) {
            res = false;
        }

        if(res) {
            rem_size = start_page_addr + page_len - cur_offset;
            /*is data with that length can be fitted in flash page?*/
            if(rem_size < item->length) {
                res = false;
            }
            if(0 == item->length) {
                res = false;
            }
        }

        if(res) {
            payload = (uint8_t*)(cur_offset + ITEM_HEADER_SZ);
            uint8_t calc_crc8 = crc8_autosar_calc((void*)(payload), item->length);
            if(calc_crc8 != item->crc8) {
                res = false;
            }
        }

        if(res) {
            /*spot data file valid item */
            file_cnt++;
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, item->id);
            snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, item->length);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%02x " TSEP, temp_str, item->crc8);
            snprintf(temp_str, sizeof(temp_str), "%s %08p " TSEP, temp_str, item);
            res = hex2ascii(payload, item->length, data, sizeof(data));
            if(res) {
                snprintf(temp_str, sizeof(temp_str), "%s 0x%s ", temp_str, data);
            }
            snprintf(temp_str, sizeof(temp_str), "%s", temp_str);
            if(is_contain(temp_str, key_word1, key_word2)) {
                res = true;
            }
        }
        if(res) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);
            num++;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    if(0 < file_cnt) {
        out_res = true;
    }
    return out_res;
}
#endif
