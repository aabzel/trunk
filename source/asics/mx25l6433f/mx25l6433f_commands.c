#include "mx25l6433f_commands.h"

#include <stdio.h>

#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "mx25l6433f_diag.h"
#include "mx25l6433f_mcal.h"
#include "mx25l6433f_types.h"

bool mx25l6433f_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = mx25l6433f_diag();
    res = mx25l6433f_diag_high_level(1);
    return res;
}

bool mx25l6433f_reg_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}
bool mx25l6433f_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool mx25l6433f_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = mx25l6433f_init_one(1);
    return res;
}

bool mx25l6433f_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool mx25l6433f_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = mx25l6433f_reset(1);
    return res;
}

bool mx25l6433f_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool mx25l6433f_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t address = 0;
    uint8_t byte = 0;
    uint32_t array_len = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(MX25L6433F, "ParseErr block_numb  %s", argv[0]);
        }
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[1], &array_len);
        if(false == res) {
            LOG_ERROR(MX25L6433F, "ParseErr size %s", argv[1]);
        }
    }

    if(res && array_len) {
        cli_printf(CRLF "0x" CRLF);
        uint32_t i = 0;
        for(i = 0; i < array_len; i++) {
            res = mx25l6433f_read(1,address + i, &byte, 1);
            if(res) {
                cli_printf("%02x", byte);
            } else {
                LOG_ERROR(MX25L6433F, "ReadErr Addr:0x%x Size:%u", address, 1);
            }
        }
        cli_printf(CRLF);
    }
    return res;
}

bool mx25l6433f_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t buff[MX25L6433F_PAGE_SIZE + 1];
    memset(buff, 0xFF, sizeof(buff));
    uint32_t array_len = 0;
    uint32_t address = 0;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(MX25L6433F, "ParseErr block_numb  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], buff, sizeof(buff), &array_len);
        if(false == res) {
            LOG_WARNING(MX25L6433F, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)buff, sizeof(buff), "%s", argv[1]);
            array_len = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = mx25l6433f_page_program(1,address, buff, MX25L6433F_PAGE_SIZE);
        if(res) {
            LOG_INFO(MX25L6433F, "Ok 0x%x", address);
        } else {
            LOG_ERROR(MX25L6433F, "Err  0x%x", address);
        }
    }
    return res;
}

bool mx25l6433f_write_enable_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    if(1 <= argc) {
        res = try_str2bool(argv[0], &on_off);
        if(false == res) {
            LOG_ERROR(MX25L6433F, "ParseErr OnOff  %s", argv[0]);
        }
    }
    if(res) {
        res = mx25l6433f_write_enable(1,on_off);
        if(res) {
            LOG_INFO(MX25L6433F, "WrEnOk");
        } else {
            LOG_ERROR(MX25L6433F, "WrEnErr");
        }
    }
    return res;
}

bool mx25l6433f_analyze_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t piece_size = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &piece_size);
        if(false == res) {
            LOG_ERROR(MX25L6433F, "ParseErr piece_size  %s", argv[0]);
        }
    }

    if(res) {
        res = mx25l6433f_usage(1, piece_size);
    }
    return res;
}
