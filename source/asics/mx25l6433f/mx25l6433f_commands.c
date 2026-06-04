#include "mx25l6433f_commands.h"

#include "convert.h"
#include "log.h"
#include "mx25l6433f_mcal.h"

bool mx25l6433f_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MX25L6433F, res, "Num");
    }

    if(res) {
        res = mx25l6433f_raw_reg_diag(num);
        log_info_res(MX25L6433F, res, "RegMap");
    } else {
        LOG_ERROR(MX25L6433F, "Usage: mx25l6433frr num");
    }
    return res;
}

bool mx25l6433f_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MX25L6433F, res, "Num");
    }

    if(res) {
        res = mx25l6433f_diag_one(num);
        log_info_res(MX25L6433F, res, "Diag");

        res = mx25l6433f_diag();
        log_info_res(MX25L6433F, res, "Diag");
    } else {
        LOG_ERROR(MX25L6433F, "Usage: fdat");
    }

    return res;
}

bool mx25l6433f_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MX25L6433F, res, "Num");
    }

    if(0 == argc) {
        res = mx25l6433f_mcal_init();
        log_info_res(MX25L6433F, res, "Init");
    }
    return res;
}
