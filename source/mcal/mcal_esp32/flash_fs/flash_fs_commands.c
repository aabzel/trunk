#include "flash_fs_commands.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <nvs.h>

#include "bit_utils.h"
#include "convert.h"
#include "crc8_autosar.h"
#include "data_utils.h"
#include "debug_info.h"
#include "flash_fs.h"
#include "io_utils.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"


bool cmd_flash_fs_diag(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        nvs_stats_t nvs_stats;
        esp_err_t ret=nvs_get_stats(STORAGE_NAMESPACE, &nvs_stats);
        if(ESP_OK==ret){
            res = true;
            printf("usedEntries: %u" CRLF, nvs_stats.used_entries);
            printf("freeEntries: %u" CRLF, nvs_stats.free_entries);
            printf("totalEntries: %u" CRLF, nvs_stats.total_entries);
            printf("namespaceCnt: %u" CRLF, nvs_stats.namespace_count);
        }
        size_t used_entries=0;
        ret = nvs_get_used_entry_count( FsHandle, &used_entries);
        if(ESP_OK==ret){
            res = true;
            printf("usedEntries: %u" CRLF, used_entries);
        }
    } else {
        LOG_ERROR(FLASH_FS, "Usage: ffd");
    }
    return res;
}

bool cmd_flash_fs_get(int32_t argc, char* argv[]) {
    bool res = false;
    unsigned char array[100] = "";
    uint16_t file_id = 0;
    uint16_t file_len = 0;
    if(1 == argc) {
        res = true;

        res = try_str2uint16(argv[0], &file_id);
        if(false == res) {
            LOG_ERROR(FLASH_FS, "Unable to extract sector_num %s", argv[0]);
        }

        if(true == res) {
            res = mm_get(file_id, array, sizeof(array), &file_len);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "mm_get error");
            } else {
                print_mem((uint8_t*)array, (uint16_t)file_len, true, true, false, true);
                io_printf(CRLF);
            }
        }
    } else if(0 == argc) {
        static const table_col_t cols[] = {{7, "id"}, {12, "addr"}, {5, "data"}};
        table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

        for(file_id = 0; file_id < 0xFFFF; file_id++) {
            file_len = 0;

            res = mm_get((uint16_t)file_id, array, sizeof(array), &file_len);

            if((true == res) && (0 < file_len)) {
                io_printf("| %5u | ", file_id);
                print_bin(array, file_len, 0);
                print_ascii_line((char*)array, file_len, 1);
                io_printf(CRLF);
                res = true;
            }
        }
        table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    } else {
        LOG_ERROR(FLASH_FS, "Usage: ffg");
    }
    return res;
}

bool cmd_flash_fs_set(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        uint32_t write_len = 0;
        res = true;
        bool is_text = false;
        Type32Union_t union_data = {0};
        uint8_t text[80] = "";
        uint16_t file_id = 0;
        if(true == res) {
            res = try_str2uint16(argv[0], &file_id);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "Unable to extract file_id %s", argv[0]);
            }
        }

        if(0 == write_len) {
            res = try_str2uint8(argv[1], &union_data.u8[0]);
            if(true == res) {
                LOG_INFO(FLASH_FS, "Spot uint8");
                write_len = 1;
            }
        }

        if(0 == write_len) {
            res = try_str2uint16(argv[1], &union_data.u16[0]);
            if(true == res) {
                LOG_INFO(FLASH_FS, "Spot uint16");
                write_len = 2;
            }
        }

        if(0 == write_len) {
            res = try_str2uint32(argv[1], &union_data.u32);
            if(true == res) {
                LOG_INFO(FLASH_FS, "Spot uint32");
                write_len = 4;
            }
        }
        if(0 == write_len) {
            strncpy((char*)text, argv[1], sizeof(text));
            write_len = strlen((char*)text) + 1;
            LOG_INFO(FLASH_FS, "Spot text");
            is_text = true;
        }

        if(0 < write_len) {
            if(is_text) {
                res = mm_set(file_id, (uint8_t*)&text, write_len);
            } else {
                res = mm_set(file_id, (uint8_t*)&union_data, write_len);
            }
            if(false == res) {
                LOG_ERROR(FLASH_FS, "mm_set error");
            } else {
                LOG_INFO(FLASH_FS, "mm_set OK");
            }
        } else {
            LOG_ERROR(FLASH_FS, "mm_set len error");
        }
    } else {
        LOG_ERROR(FLASH_FS, "Usage: ffs id val");
    }
    return res;
}

bool cmd_flash_fs_format(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        res = mm_flash_format();
        if(false == res) {
            LOG_ERROR(FLASH_FS, "mmi flash format error");
        } else {
            LOG_INFO(FLASH_FS, "mmi flash format OK");
        }
    } else {
        LOG_ERROR(FLASH_FS, "Usage: fff");
    }
    return res;
}

bool cmd_flash_fs_inval(int32_t argc, char* argv[]) {
    bool res = false;

    if(1 == argc) {
        res = true;
        uint16_t file_id = 0;
        if(true == res) {
            res = try_str2uint16(argv[0], &file_id);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "Unable to extract sector_num %s", argv[0]);
            }
        }
        if(true == res) {
            res = mm_invalidate(file_id);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "invalidate error");
            } else {
                io_printf("id %u invalidate OK" CRLF, file_id);
            }
        }
    } else {
        LOG_ERROR(FLASH_FS, "Usage: ffi id");
    }
    return res;
}

bool cmd_flash_fs_init(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = flash_fs_init();
        if(false == res) {
            LOG_ERROR(FLASH_FS, "InitErr");
        } else {
            LOG_INFO(FLASH_FS, "InitOk");
        }
    }
    return res;
}
