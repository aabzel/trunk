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
        log_info_res(PID, res, "Diag");
    }
    return res;
}

bool pid_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = pid_mcal_init();
    log_info_res(PID, res, "Init");
    return res;
}

bool pid_target_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float target = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(PID, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &target);
        log_info_res(PID, res, "Target");
        res = true;
    }

    if(res) {
        res = pid_target_set(num, target);
        log_info_res(PID, res, "TargetSet");
    } else {
        LOG_ERROR(PID, "Usage: pidp Num target");
    }
    return res;
}

// pidp 1 0.0
bool pid_p_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float p = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(PID, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &p);
        log_info_res(PID, res, "Prop");
        res = true;
    }

    if(res) {
        res = pid_set_p(num, p);
        log_info_res(PID, res, "PropSet");
    } else {
        LOG_ERROR(PID, "Usage: pidp Num Pro");
    }
    return res;
}

bool pid_i_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float i = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(PID, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &i);
        log_info_res(PID, res, "I");
        res = true;
    }

    if(res) {
        res = pid_set_i(num, i);
        log_info_res(PID, res, "IntegralSet");
    } else {
        LOG_ERROR(PID, "Usage: pidi Num Integral");
    }
    return res;
}

bool pid_d_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float diff = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(PID, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &diff);
        log_info_res(PID, res, "Diff");
    }

    if(res) {
        res = pid_set_d(num, diff);
        log_info_res(PID, res, "DiffSet");
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
        log_info_res(PID, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        log_info_res(PID, res, "En");
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


bool pid_manual_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    float value = 0;
    bool on_off = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(PID, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        log_info_res(PID, res, "En");
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &value);
        log_info_res(PID, res, "Value");
    }

    if(res) {
        res = pid_manual(num, on_off, value);
        log_info_res(PID, res, "ManualCtrlSet");
    }else{
        LOG_ERROR(PID, "Usage: pidm Num OnOff ConstValue");
    }
    return res;
}
