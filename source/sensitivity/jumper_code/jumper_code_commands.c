#include "jumper_code_commands.h"

#include "convert.h"
#include "log.h"
#include "jumper_code_mcal.h"

bool jumper_code_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(JUMPER_CODE, res, "Num");
    }

    if(res) {
        res = jumper_code_raw_reg_diag(num);
        log_info_res(JUMPER_CODE, res, "RegMap");
    } else {
        LOG_ERROR(JUMPER_CODE, "Usage: jumper_coderr num");
    }
    return res;
}

bool jumper_code_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(JUMPER_CODE, res, "Num");
    }

    if(res) {
        res = jumper_code_diag_one(num);
        log_info_res(JUMPER_CODE, res, "Diag");

        res = jumper_code_diag();
        log_info_res(JUMPER_CODE, res, "Diag");
    } else {
        LOG_ERROR(JUMPER_CODE, "Usage: fdat");
    }

    return res;
}

bool jumper_code_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(JUMPER_CODE, res, "Num");
    }

    if(0 == argc) {
        res = jumper_code_mcal_init();
        log_info_res(JUMPER_CODE, res, "Init");
    }
    return res;
}
