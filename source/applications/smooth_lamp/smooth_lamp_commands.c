#include "smooth_lamp_commands.h"

#include "convert.h"
#include "log.h"
#include "smooth_lamp.h"

bool smooth_lamp_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SMOOTH_LAMP, res, "Num");
    }

    if(res) {
        // res = smooth_lamp_diag_one(num);
        // log_info_res(SMOOTH_LAMP, res, "Diag");

        res = smooth_lamp_diag();
        log_info_res(SMOOTH_LAMP, res, "Diag");
    } else {
        LOG_ERROR(SMOOTH_LAMP, "Usage: sld");
    }

    return res;
}

bool smooth_lamp_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SMOOTH_LAMP, res, "Num");
    }

    if(res) {
        res = smooth_lamp_mcal_init();
        log_info_res(SMOOTH_LAMP, res, "Init");
    }
    return res;
}

/*
 ll SmoothLamp info
  ll SmoothLamp debug
 slm 1 0.001; slc 1 1;  slc 1 0
  slm 1 0.05;  slc 1 1
  slm 1 0.05;  slc 1 0
  slm 1 0.01; slc 1 1;
 slm 1 0.01; slc 1 0
 slc 1 0
 slc 1 1
 */
bool smooth_lamp_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    bool on_off = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SMOOTH_LAMP, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        log_info_res(SMOOTH_LAMP, res, "OnOff");
    }

    if(res) {
        res = smooth_lamp_ctrl(num, on_off);
        log_info_res(SMOOTH_LAMP, res, "Ctrl");
    } else {
        LOG_ERROR(SMOOTH_LAMP, "Usage: slc N En");
    }
    return res;
}

/*
 slls 1 5
 */
bool smooth_lamp_logistic_shift_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    float logistic_shift = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SMOOTH_LAMP, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &logistic_shift);
        log_info_res(SMOOTH_LAMP, res, "logistic_shift");
    }

    if(res) {
        res =  smooth_lamp_logistic_shift(num, logistic_shift);
        log_info_res(SMOOTH_LAMP, res, "SetlogisticShift");
    } else {
        LOG_ERROR(SMOOTH_LAMP, "Usage: slls N logistic_shift");
    }
    return res;
}
/*
slm 1 0.001
slm 1 0.01
slm 1 0.4
slm 1 0.95
 * */
bool smooth_lamp_mult_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float mult = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SMOOTH_LAMP, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &mult);
        log_info_res(SMOOTH_LAMP, res, "mult");
    }

    if(res) {
        res = smooth_lamp_mult(num, mult);
        log_info_res(SMOOTH_LAMP, res, "SetMult");
    } else {
        LOG_ERROR(SMOOTH_LAMP, "Usage: slm N Mult");
    }
    return res;
}

/*
 sllf 1 0.03
 sllf 1 0.5
 sllf 1 0.75
sllf 1 0.8

sllf 1 0.4

sllf 1 0.85
sllf 1 0.855
sllf 1 0.85

sllf 1 0.86
sllf 1 0.87
sllf 1 0.9
 sllf 1 1
 * */
bool smooth_lamp_limit_off_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    float limit_down = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SMOOTH_LAMP, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &limit_down);
        log_info_res(SMOOTH_LAMP, res, "limit_down");
    }

    if(res) {
        res = smooth_lamp_limit_down(num, limit_down);
        log_info_res(SMOOTH_LAMP, res, "Setlimit_down");
    } else {
        LOG_ERROR(SMOOTH_LAMP, "Usage: sllf N limit_down");
    }
    return res;
}
