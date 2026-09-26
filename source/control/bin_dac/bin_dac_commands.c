#include "bin_dac_commands.h"

#include "convert.h"
#include "log.h"
#include "bin_dac_mcal.h"
#include "bin_dac_diag.h"



bool bin_dac_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BIN_DAC, res, "Num");
    }

    if(res) {
        res = bin_dac_diag_one(num);
        log_info_res(BIN_DAC, res, "Diag");

        res = bin_dac_diag();
        log_info_res(BIN_DAC, res, "Diag");
    } else {
        LOG_ERROR(BIN_DAC, "Usage: fdat");
    }

    return res;
}

bool bin_dac_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BIN_DAC, res, "Num");
    }

    if(0 == argc) {
        res = bin_dac_mcal_init();
        log_info_res(BIN_DAC, res, "Init");
    }
    return res;
}


bool bin_dac_show_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        num = 1;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BIN_DAC, res, "Num");
    }

    if(res) {
        res = bin_dac_show_sample(num);
        log_info_res(BIN_DAC, res, "showSample");
    }
    return res;
}

