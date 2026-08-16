#include "back_count_commands.h"

#include "convert.h"
#include "log.h"
#include "back_count_mcal.h"

bool back_count_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BACK_COUNT, res, "Num");
    }

    if(res) {
        res = back_count_raw_reg_diag(num);
        log_info_res(BACK_COUNT, res, "RegMap");
    } else {
        LOG_ERROR(BACK_COUNT, "Usage: back_countrr num");
    }
    return res;
}

bool back_count_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BACK_COUNT, res, "Num");
    }

    if(res) {
        res = back_count_diag_one(num);
        log_info_res(BACK_COUNT, res, "Diag");

        res = back_count_diag();
        log_info_res(BACK_COUNT, res, "Diag");
    } else {
        LOG_ERROR(BACK_COUNT, "Usage: fdat");
    }

    return res;
}

bool back_count_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BACK_COUNT, res, "Num");
    }

    if(0 == argc) {
        res = back_count_mcal_init();
        log_info_res(BACK_COUNT, res, "Init");
    }
    return res;
}
