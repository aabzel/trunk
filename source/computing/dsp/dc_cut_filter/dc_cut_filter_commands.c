#include "dc_cut_filter_commands.h"

#include "convert.h"
#include "dc_cut_filter_mcal.h"
#include "log.h"

bool dc_cut_filter_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(DC_CUT_FILTER, res, "Num");
    }

    if(res) {
        res = dc_cut_filter_diag_one(num);
        log_info_res(DC_CUT_FILTER, res, "Diag");

        res = dc_cut_filter_diag();
        log_info_res(DC_CUT_FILTER, res, "Diag");
    } else {
        LOG_ERROR(DC_CUT_FILTER, "Usage: fdat");
    }

    return res;
}

bool dc_cut_filter_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(DC_CUT_FILTER, res, "Num");
    }

    if(0 == argc) {
        res = dc_cut_filter_mcal_init();
        log_info_res(DC_CUT_FILTER, res, "Init");
    }
    return res;
}
