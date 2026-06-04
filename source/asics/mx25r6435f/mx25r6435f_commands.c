#include "mx25r6435f_commands.h"

#include <stdio.h>

#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "mx25r6435f_diag.h"
#include "mx25r6435f_drv.h"
#include "mx25r6435f_types.h"

bool mx25r6435f_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = mx25r6435f_diag();
    res = mx25r6435f_diag_high_level();
    return res;
}

bool mx25r6435f_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}
bool mx25r6435f_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool mx25r6435f_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = mx25r6435f_init();
    return res;
}

bool mx25r6435f_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool mx25r6435f_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = mx25r6435f_reset();
    return res;
}

bool mx25r6435f_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool mx25r6435f_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t address = 0;
    uint8_t byte = 0;
    uint32_t array_len = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(MX25R6435F, "ParseErr block_numb  %s", argv[0]);
        }
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[1], &array_len);
        if(false == res) {
            LOG_ERROR(MX25R6435F, "ParseErr size %s", argv[1]);
        }
    }

    if(res && array_len) {
        cli_printf(CRLF "0x" CRLF);
        uint32_t i = 0;
        for(i = 0; i < array_len; i++) {
            res = mx25r6435f_read(address + i, &byte, 1);
            if(res) {
                cli_printf("%02x", byte);
            } else {
                LOG_ERROR(MX25R6435F, "ReadErr Addr:0x%x Size:%u", address, 1);
            }
        }
        cli_printf(CRLF);
    }
    return res;
}

bool mx25r6435f_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t buff[MX25R6435F_PAGE_SIZE + 1];
    memset(buff, 0xFF, sizeof(buff));
    uint32_t array_len = 0;
    uint32_t address = 0;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(MX25R6435F, "ParseErr block_numb  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], buff, sizeof(buff), &array_len);
        if(false == res) {
            LOG_WARNING(MX25R6435F, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)buff, sizeof(buff), "%s", argv[1]);
            array_len = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = mx25r6435f_page_program(address, buff, MX25R6435F_PAGE_SIZE);
        if(res) {
            LOG_INFO(MX25R6435F, "Ok 0x%x", address);
        } else {
            LOG_ERROR(MX25R6435F, "Err  0x%x", address);
        }
    }
    return res;
}

bool mx25r6435f_write_enable_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    if(1 <= argc) {
        res = try_str2bool(argv[0], &on_off);
        if(false == res) {
            LOG_ERROR(MX25R6435F, "ParseErr OnOff  %s", argv[0]);
        }
    }
    if(res) {
        res = mx25r6435f_write_enable(on_off);
        if(res) {
            LOG_INFO(MX25R6435F, "WrEnOk");
        } else {
            LOG_ERROR(MX25R6435F, "WrEnErr");
        }
    }
    return res;
}

bool mx25r6435f_analyze_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t piece_size = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &piece_size);
        if(false == res) {
            LOG_ERROR(MX25R6435F, "ParseErr piece_size  %s", argv[0]);
        }
    }

    if(res) {
        res = mx25r6435f_usage(piece_size);
    }
    return res;
}
