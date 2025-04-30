#include "load_detect_commands.h"

#include <stdio.h>

#include "convert.h"
#include "gpio_diag.h"
#include "gpio_drv.h"
#include "load_detect_diag.h"
#include "load_detect_drv.h"
#include "log.h"

bool load_detect_diag_command(int32_t argc, char* argv[]) {
    bool res = true;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = load_detect_diag();
    }

    return res;
}

bool load_detect_pin_diag_command(int32_t argc, char* argv[]) {
    bool res = true;

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

    if(res) {
        res = load_detect_pin_diag(keyWord1, keyWord2);
    }

    return res;
}

bool load_detect_enable_command(int32_t argc, char* argv[]) {
    bool res = true;
    bool on_off = true;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(LOAD_DETECT, "ParseErr OnOff %s", argv[1]);
        }
    }

    if(res) {
        res = load_detect_enable(num, on_off);
        if(res) {
            LOG_INFO(LOAD_DETECT, "EnableOk %u", on_off);
        } else {
            LOG_ERROR(LOAD_DETECT, "EnableErr");
        }
    }
    return res;
}

bool load_detect_enable_pin_command(int32_t argc, char* argv[]) {
    bool res = true;
    bool on_off = true;
    uint8_t num = 0;
    Pad_t pad = {0};

    if(2 <= argc) {
        res = parse_pad(argv, &pad);
    }
    if(3 <= argc) {
        res = try_str2uint8(argv[2], &num);
    }

    if(4 <= argc) {
        res = try_str2bool(argv[3], &on_off);
        if(false == res) {
            LOG_ERROR(LOAD_DETECT, "ParseErr OnOff %s", argv[3]);
        }
    }

    if(res) {
        res = load_detect_enable_pad(num, pad, on_off);
        if(res) {
            LOG_INFO(LOAD_DETECT, "PinEnableOk");
        } else {
            LOG_ERROR(LOAD_DETECT, "PinEnableErr");
        }
    }

    return res;
}

bool load_detect_init_command(int32_t argc, char* argv[]) {
    bool res = true;
    uint8_t num = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = load_detect_init_one(num);
        if(res) {
            LOG_INFO(LOAD_DETECT, "InitOk");
        } else {
            LOG_ERROR(LOAD_DETECT, "InitErr");
        }
    }
    return res;
}
