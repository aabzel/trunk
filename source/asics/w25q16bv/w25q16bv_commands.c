#include "w25q16bv_commands.h"

#include <stdio.h>

#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "w25q16bv_diag.h"
#include "w25q16bv_drv.h"
#include "w25q16bv_types.h"

bool w25q16bv_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = w25q16bv_diag(1);
    res = w25q16bv_diag_high_level(1);
    return res;
}

bool w25q16bv_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}
bool w25q16bv_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool w25q16bv_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = w25q16bv_init_one(1);
    return res;
}

bool w25q16bv_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool w25q16bv_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = w25q16bv_reset(1);
    return res;
}

bool w25q16bv_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool w25q16bv_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t address = 0;
    uint8_t byte = 0;
    uint32_t array_len = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(W25Q16BV, "ParseErr block_numb  %s", argv[0]);
        }
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[1], &array_len);
        if(false == res) {
            LOG_ERROR(W25Q16BV, "ParseErr size %s", argv[1]);
        }
    }

    if(res && array_len) {
        cli_printf(CRLF "0x" CRLF);
        uint32_t i = 0;
        for(i = 0; i < array_len; i++) {
            res = w25q16bv_read(1,address + i, &byte, 1);
            if(res) {
                cli_printf("%02x", byte);
            } else {
                LOG_ERROR(W25Q16BV, "ReadErr Addr:0x%x Size:%u", address, 1);
            }
        }
        cli_printf(CRLF);
    }
    return res;
}

bool w25q16bv_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t buff[W25Q16BV_PAGE_SIZE + 1];
    memset(buff, 0xFF, sizeof(buff));
    uint32_t array_len = 0;
    uint32_t address = 0;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(W25Q16BV, "ParseErr block_numb  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], buff, sizeof(buff), &array_len);
        if(false == res) {
            LOG_WARNING(W25Q16BV, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)buff, sizeof(buff), "%s", argv[1]);
            array_len = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = w25q16bv_page_program(1,address, buff, W25Q16BV_PAGE_SIZE);
        if(res) {
            LOG_INFO(W25Q16BV, "Ok 0x%x", address);
        } else {
            LOG_ERROR(W25Q16BV, "Err  0x%x", address);
        }
    }
    return res;
}

bool w25q16bv_write_enable_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    if(1 <= argc) {
        res = try_str2bool(argv[0], &on_off);
        if(false == res) {
            LOG_ERROR(W25Q16BV, "ParseErr OnOff  %s", argv[0]);
        }
    }
    if(res) {
        res = w25q16bv_write_enable(1,on_off);
        if(res) {
            LOG_INFO(W25Q16BV, "WrEnOk");
        } else {
            LOG_ERROR(W25Q16BV, "WrEnErr");
        }
    }
    return res;
}

