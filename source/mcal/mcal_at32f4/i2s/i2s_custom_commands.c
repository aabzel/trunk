#include "i2s_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "i2s_custom_diag.h"
#include "i2s_mcal.h"
#include "log.h"

bool i2s_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    char keyword[80] = {0};
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2S Number [1-%d]", I2S_COUNT);
        }
    }

    if(2 <= argc) {
        strcpy(keyword, argv[1]);
    }

    if(res) {
        res = i2s_diag_low_level(num, keyword);
    } else {
        LOG_ERROR(I2S, "Usage i2sdl Num");
    }

    return res;
}

bool i2s_raw_reg_command(int32_t argc, char* argv[]) {
    uint8_t num = 2;
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(I2S, "ParseErr I2S Number [1-%d]", I2S_COUNT);
        }
    }

    if(res) {
        res = i2s_raw_reg_diag(num);
    } else {
        LOG_ERROR(I2S, "Usage i2srr Num");
    }

    return res;
}
