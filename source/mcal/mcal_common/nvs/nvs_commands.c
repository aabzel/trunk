#include "nvs_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "convert.h"
#include "crc16_ccitt.h"
#include "crc32.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "nvs_drv.h"
#include "str_utils.h"
#include "table_utils.h"

bool nvs_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = nvs_init();
    } else {
        LOG_ERROR(NVS, "Usage: nvsi");
    }

    return res;
}

bool nvs_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = nvs_diag();
        log_info_res(NVS, res, "Diag");
    } else {
        LOG_ERROR(NVS, "Usage: nvsd");
    }

    return res;
}

bool nvs_erase_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t flash_addr = 0;
    if(1 == argc) {
        res = true;
        if(res) {
            res = try_str2uint32(argv[0], &flash_addr);
            if(false == res) {
                LOG_ERROR(NVS, "Unable to parse FlashAddr %s", argv[0]);
            }
        }
    }

    if(res) {
        res = nvs_erase_page(flash_addr);
        log_info_res(NVS, res, "Erase");
    } else {
        LOG_ERROR(NVS, "Usage: nvse FlashAddr");
    }

    return res;
}

bool nvs_mcal_readcommand(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t num_bytes = 0;
    uint32_t flash_addr = 0;
    if(2 == argc) {
        res = true;
        if(res) {
            res = try_str2uint32(argv[0], &flash_addr);
            if(false == res) {
                LOG_ERROR(NVS, "Unable to parse flash_addr %s", argv[0]);
            }
        }
        if(res) {
            res = try_str2uint32(argv[1], &num_bytes);
            if(false == res) {
                LOG_ERROR(NVS, "Unable to parse num_bytes %s", argv[1]);
            }
        }
    }

    if(res) {
        LOG_INFO(NVS, "Read Addr %u Size %u", flash_addr, num_bytes);
        cli_printf(CRLF);
        uint8_t read_val = 0;
        uint32_t i = 0;
        for(i = 0; i < num_bytes; i++) {
            read_val = 0;
            res = nvs_mcal_read(flash_addr + i, &read_val, 1);
            if(res) {
                cli_printf("%02X", read_val);
            }
        }
        cli_printf(CRLF);
    } else {
        LOG_ERROR(NVS, "Usage: nvsr flash_addr num_bytes");
    }
    return res;
}

bool nvs_mcal_writecommand(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint32_t flash_addr = 0;
        uint8_t array[256] = {0};
        memset(array, 0xFF, sizeof(array));
        uint32_t num_bytes = 0;
        if(res) {
            res = try_str2uint32(argv[0], &flash_addr);
            if(false == res) {
                LOG_ERROR(NVS, "Unable to parse FlashAddr %s", argv[0]);
            }
        }

        if(res) {
            res = try_str2array(argv[1], array, sizeof(array), &num_bytes);
            if(false == res) {
                LOG_ERROR(NVS, "Unable to extract array %s", argv[1]);
            }
        }
        if(res) {
            LOG_INFO(NVS, "Write Addr %u Size %u", flash_addr, num_bytes);
            res = nvs_mcal_write(flash_addr, array, num_bytes);
            log_info_res(NVS, res, "Write");
        }
    } else {
        LOG_ERROR(NVS, "Usage: nvsw addr hex_string");
        LOG_INFO(NVS, "addr");
        LOG_INFO(NVS, "hex_string 0x[0...F]+");
    }
    return res;
}

bool nvs_dump_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = print_mem((uint8_t*)NvsConfig.start, NvsConfig.size, true, true, true, true);
    return res;
}
