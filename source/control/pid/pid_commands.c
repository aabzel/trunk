#include "pid_commands.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "pid.h"
#include "pid_diag.h"
#include "str_utils.h"

bool pid_diag_command(int32_t argc, char* argv[]) {
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
        LOG_ERROR(PID, "Usage: pidd keyWord");
    }
    if(res) {
        res = pid_diag(keyWord1, keyWord2);
    }
    return res;
}

bool pid_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = pid_mcal_init();
    return res;
}

bool pid_target_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double target = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PID, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &target);
        res = true;
    }

    if(res) {
        res = pid_target_set(num, target);
    } else {
        LOG_ERROR(PID, "Usage: pidp Num target");
    }
    return res;
}

bool pid_p_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double p = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PID, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &p);
        res = true;
    }

    if(res) {
        res = pid_set_p(num, p);
    } else {
        LOG_ERROR(PID, "Usage: pidp Num Pro");
    }
    return res;
}

bool pid_i_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double i = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PID, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &i);
        res = true;
    }

    if(res) {
        res = pid_set_i(num, i);
    } else {
        LOG_ERROR(PID, "Usage: pidi Num Integral");
    }
    return res;
}

bool pid_d_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double d = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PID, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &d);
    }

    if(res) {
        res = pid_set_d(num, d);
    } else {
        LOG_ERROR(PID, "Usage: pidd Num Differential");
    }
    return res;
}

bool pid_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    bool on_off = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PID, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
    }

    if(res) {
        res = pid_ctrl(num, on_off);
        if(res) {
            LOG_INFO(PID, "PID:%u,%s", num, OnOffToStr(on_off));
        } else {
            LOG_ERROR(PID, "PID:%u,Err,Num %u", num, on_off);
        }
    } else {
        LOG_ERROR(PID, "Usage: pidd Num OmOff");
    }
    return res;
}
