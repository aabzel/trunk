#include "nvs_commands.h"

#include "array_diag.h"
#include "convert.h"
#include "log.h"
#include "nvs_mcal.h"
//#include "nvs_write.h"

bool nvs_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = nvs_diag();
        log_info_res(NVS, res, "Diag");
    } else {
        LOG_ERROR(NVS, "Usage: nd");
    }

    return res;
}

bool nvs_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = nvs_mcal_init();
        log_info_res(NVS, res, "Init");
    } else {
        LOG_ERROR(NVS, "Usage: ni");
    }

    return res;
}

bool nvs_erase_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t flash_addr = 0;
    uint32_t size = 0;
    if(2 == argc) {
        res = true;
        res = try_str2uint32(argv[0], &flash_addr);
        log_info_res(NVS, res, "addr");

        res = try_str2uint32(argv[1], &size);
        log_info_res(NVS, res, "Size");
    }

    if(res) {
#ifdef HAS_NVS_WRITE
        res = nvs_mcal_erase(1, flash_addr, size);
        log_info_res(NVS, res, "Erase");
#endif
    } else {
        LOG_ERROR(NVS, "Usage: nvse FlashAddr");
    }

    return res;
}

bool nvs_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size = 0;
    uint32_t flash_addr = 0;
    if(2 == argc) {
        res = true;
        if(res) {
            res = try_str2uint32(argv[0], &flash_addr);
            log_info_res(NVS, res, "Addr");
        }
        if(res) {
            res = try_str2uint32(argv[1], &size);
            log_info_res(NVS, res, "size");
        }
    }

    if(res) {
        LOG_INFO(NVS, "Read Addr %u Size %u", flash_addr, size);
        cli_printf(CRLF);
        uint8_t read_val = 0;
        uint32_t i = 0;
        for(i = 0; i < size; i++) {
            read_val = 0;
            res = nvs_mcal_read(1, flash_addr + i, &read_val, 1);
            if(res) {
                cli_printf("%02X", read_val);
            }
        }
        cli_printf(CRLF);
    } else {
        LOG_ERROR(NVS, "Usage: nvsr flash_addr size");
    }
    return res;
}

bool nvs_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(2 == argc) {
        res = true;
        uint32_t flash_addr = 0;
        uint8_t array[256] = {0};
        memset(array, 0xFF, sizeof(array));
        uint32_t size = 0;
        if(res) {
            res = try_str2uint32(argv[0], &flash_addr);
            log_info_res(NVS, res, "Addr");
        }

        if(res) {
            res = try_str2array(argv[1], array, sizeof(array), &size);
            log_info_res(NVS, res, "Data");
        }
        if(res) {
            LOG_INFO(NVS, "Write Addr %u Size %u", flash_addr, size);
#ifdef HAS_NVS_WRITE
            res = nvs_mcal_write(1, flash_addr, array, size);
            log_info_res(NVS, res, "Write");
#endif
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
    const NvsConfig_t* Config = NvsGetConfig(1);
    if(Config) {
        res = print_mem((uint8_t*)Config->start, Config->size, true, true, true, true);
        log_info_res(NVS, res, "Print");
    }
    return res;
}
