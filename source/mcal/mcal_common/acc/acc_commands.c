#include "acc_commands.h"

#include "acc_mcal.h"
#include "convert.h"
#include "log.h"

bool acc_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = acc_raw_reg_diag(1);
    log_info_res(LG_ACC, res, "RegMap");
    if(!res) {
        LOG_ERROR(LG_ACC, "Usage: acrm num");
    }

    return res;
}

bool acc_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = acc_diag();
    } else {
        LOG_ERROR(LG_ACC, "Usage: fdat");
    }

    return res;
}

bool acc_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = acc_mcal_init();
        if(false == res) {
            LOG_ERROR(LG_ACC, "Init" LOG_ER);
        } else {
            LOG_INFO(LG_ACC, "Init" LOG_OK);
        }
    }
    return res;
}
