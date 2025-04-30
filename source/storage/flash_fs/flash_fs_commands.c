#include "flash_fs_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array_diag.h"
#include "bit_utils.h"
#include "common_diag.h"
#include "convert.h"
#include "crc8_autosar.h"
#include "data_utils.h"
#include "debug_info.h"
#include "flash_fs.h"
#include "flash_fs_ll.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "std_includes.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_FLASH_FS_DIAG
#include "flash_fs_diag.h"
#endif

#ifdef HAS_NVS
#include "nvs_const.h"
#endif

bool cmd_flash_fs_diag(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        FlashFsPage_t page_num = 0;

        page_num = flash_fs_get_active_page_num();
        LOG_INFO(FLASH_FS, "PageNum %u", page_num);

        double rem = flash_fs_get_remaining_space_percent();
        LOG_INFO(FLASH_FS, "RemSpace %6.2f %%", rem);

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
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, page_len);
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, files);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, spare_cnt);
            snprintf(log_line, sizeof(log_line), "%s %6.2f " TSEP, log_line, usage_pre_cent);

            cli_printf("%s" CRLF, log_line);

            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    } else {
        LOG_ERROR(FLASH_FS, "Usage: ffd");
    }
    return res;
}
#ifdef HAS_FLASH_FS_EXT_COMMANDS
bool cmd_flash_fs_get(int32_t argc, char* argv[]) {
    bool res = false;
    unsigned char array[100] = "";
    uint16_t file_id = 0;
    uint16_t file_len = 0;
    if(1 == argc) {
        res = true;

        res = try_str2uint16(argv[0], &file_id);
        if(false == res) {
            LOG_ERROR(FLASH_FS, "ParseErr sector_num %s", argv[0]);
        }

        if(res) {
            res = flash_fs_get(file_id, array, sizeof(array), &file_len);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "_get error");
            } else {
#ifdef HAS_ARRAY_DIAG
                print_mem((uint8_t*)array, (uint16_t)file_len, true, true, false, true);
                cli_printf(CRLF);
#endif
            }
        }
    } else if(0 == argc) {
        static const table_col_t cols[] = {{7, "id"}, {12, "addr"}, {5, "data"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        for(file_id = 0; file_id < 0xFFFF; file_id++) {
            file_len = 0;
            uint32_t* file_Address = NULL;
            res = flash_fs_get((uint16_t)file_id, array, sizeof(array), &file_len);
            if(res) {
                res = flash_fs_get_address(file_id, (uint8_t**)&file_Address, &file_len);
            }
            if((res) && (0 < file_len)) {
#ifdef HAS_ARRAY_DIAG
                cli_printf("| %5u | 0x%08p | ", file_id, file_Address);
                print_bin(array, file_len, 0);
                print_ascii_line((char*)array, file_len, 1);
                cli_printf(CRLF);
                res = true;
#endif
            }
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    } else {
        LOG_ERROR(FLASH_FS, "Usage: ffg");
    }
    return res;
}
#endif

#ifdef HAS_FLASH_FS_EXT_COMMANDS
bool cmd_flash_fs_get_addr(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
        uint16_t file_id = 0;
        if(res) {
            res = try_str2uint16(argv[0], &file_id);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "ParseErr sector_num %s", argv[0]);
            }
        }
        if(res) {
            uint16_t file_len = 0;
            uint32_t* file_Address = NULL;
            res = flash_fs_get_address(file_id, (uint8_t**)&file_Address, &file_len);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "get error");
            } else {
                cli_printf("Addr: %p Len: %u" CRLF, file_Address, file_len);
            }
        }
    } else {
        LOG_ERROR(FLASH_FS, "Usage: ffg");
    }
    return res;
}
#endif

#ifdef HAS_FLASH_FS_EXT_COMMANDS
bool cmd_flash_fs_set(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        uint32_t write_len = 0;
        res = true;
        bool is_text = false;
        Type32Union_t union_data = {0};
        uint8_t lText[80] = {0};
        uint16_t file_id = 0;
        if(res) {
            res = try_str2uint16(argv[0], &file_id);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "ParseErr file_id %s", argv[0]);
            }
        }

        if(0 == write_len) {
            res = try_str2uint8(argv[1], &union_data.u8[0]);
            if(res) {
                LOG_INFO(FLASH_FS, "Spot uint8");
                write_len = 1;
            }
        }

        if(0 == write_len) {
            res = try_str2uint16(argv[1], &union_data.u16[0]);
            if(res) {
                LOG_INFO(FLASH_FS, "Spot uint16");
                write_len = 2;
            }
        }

        if(0 == write_len) {
            res = try_str2uint32(argv[1], &union_data.u32);
            if(res) {
                LOG_INFO(FLASH_FS, "Spot uint32");
                write_len = 4;
            }
        }
        if(0 == write_len) {
            strncpy((char*)lText, argv[1], sizeof(lText));
            write_len = strlen((char*)lText) + 1;
            LOG_INFO(FLASH_FS, "Spot text");
            is_text = true;
        }

        if(0 < write_len) {
            if(is_text) {
                res = flash_fs_set(file_id, (uint8_t*)&lText, write_len);
            } else {
                res = flash_fs_set(file_id, (uint8_t*)&union_data, write_len);
            }
            log_info_res(FLASH_FS, res, "Set");
        } else {
            LOG_ERROR(FLASH_FS, "set len error");
        }
    } else {
        LOG_ERROR(FLASH_FS, "Usage: ffs id val");
    }
    return res;
}
#endif

bool cmd_flash_fs_format(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = flash_fs_format();
        log_info_res(FLASH_FS, res, "Format");
    } else {
        LOG_ERROR(FLASH_FS, "Usage: fff");
    }
    return res;
}

bool cmd_flash_fs_toggle_page(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = flash_fs_turn_page();
        log_info_res(FLASH_FS, res, "TurnPage");
    } else {
        LOG_ERROR(FLASH_FS, "Usage: fft");
    }
    return res;
}

bool cmd_flash_fs_inval(int32_t argc, char* argv[]) {
    bool res = false;

    if(1 == argc) {
        res = true;
        uint16_t file_id = 0;
        if(res) {
            res = try_str2uint16(argv[0], &file_id);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "ParseErr FileId %s", argv[0]);
            }
        }
        if(res) {
            res = flash_fs_invalidate(file_id);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "invalidate error");
            } else {
                LOG_INFO(FLASH_FS, "ID %u InvalOk!", file_id);
            }
        }
    } else {
        LOG_ERROR(FLASH_FS, "Usage: ffi id");
    }
    return res;
}

#ifdef HAS_FLASH_FS_EXT_COMMANDS
bool cmd_flash_fs_scan(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(FLASH_FS, "Usage: ffc");
    }

    if(res) {
        res = false;
#ifdef HAS_FLASH_FS_DIAG
        uint32_t i = 0;
        for(i = 0; i < 2; i++) {
            res = flash_fs_scan(FlashFsConfig.page[i].offset, FlashFsConfig.page[i].size, keyWord1, keyWord2);
            if(false == res) {
                LOG_ERROR(FLASH_FS, "scan error");
            }
        }
#endif
    }

    return res;
}
#endif

#ifdef HAS_FLASH_FS_EXT_COMMANDS
bool cmd_flash_fs_init(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = flash_fs_init();
        log_info_res(FLASH_FS, res, "Init");
    }
    return res;
}
#endif

bool flash_dump_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t i = 0;
    for(i = 0; i < 2; i++) {
        LOG_INFO(FLASH_FS, "Page%u", i + 1);
#ifdef HAS_ARRAY_DIAG
        res = print_mem((uint8_t*)FlashFsConfig.page[i].offset, FlashFsConfig.page[i].size, true, true, true, true);
#endif
    }
    return res;
}
