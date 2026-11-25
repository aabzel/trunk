#include "can_custom_commands.h"

#include "can_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "can_custom_diag.h"
#include "can_mcal.h"
#include "common_diag.h"
#include "convert.h"
#include "debug_info.h"
#include "log.h"


bool can_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    char keyword[80] = {0};
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CAN, "ParseErr CAN Number [1-%d]", CAN_COUNT);
        }
    }

    if(2 <= argc) {
        strcpy(keyword, argv[1]);
    }

    if(res) {
        res = can_diag_low_level(num, keyword);
    } else {
        LOG_ERROR(CAN, "Usage candl Num");
    }

    return res;
}

bool can_diag_mail_box_command(int32_t argc, char* argv[]) {
    uint8_t num = 2;
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CAN, "ParseErr CAN Number [1-%d]", CAN_COUNT);
        }
    }

    if(res) {
        res = can_diag_mail_box(num, "", "");
    } else {
        LOG_ERROR(CAN, "Usage cdmb Num");
    }

    return res;
}

bool can_raw_reg_command(int32_t argc, char* argv[]) {
    uint8_t num = 2;
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CAN, "ParseErr CAN Number [1-%d]", CAN_COUNT);
        }
    }

    if(res) {
        res = can_raw_reg_diag(num);
    } else {
        LOG_ERROR(CAN, "Usage canrr Num");
    }

    return res;
}

bool can_diag_wakeup_message_buffers_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CAN, "ParseErr CAN Number [1-%d]", CAN_COUNT);
        }
    }

    if(res) {
        res = can_diag_wakeup_message_buffers(num);
    } else {
        LOG_ERROR(CAN, "Usage cdwmb Num");
    }

    return res;
}

bool can_diag_ram_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CAN, "ParseErr CAN Number [1-%d]", CAN_COUNT);
        }
    }

    if(res) {
        res = can_diag_ram(num);
    } else {
        LOG_ERROR(CAN, "Usage cdr Num");
    }

    return res;
}
