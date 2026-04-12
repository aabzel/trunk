#include "dwt_commands.h"

#include "convert.h"
#include "dwt_mcal.h"
#include "log.h"

bool dwt_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_DWT, res, "Num");
    }

    if(res) {
        res = dwt_raw_reg_diag(num);
        log_info_res(LG_DWT, res, "RegMap");
    } else {
        LOG_ERROR(LG_DWT, "Usage: dwtrm num");
    }
    return res;
}

bool dwt_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_DWT, res, "Num");
    }

    if(res) {
        switch(argc) {
        case 0: {
            res = dwt_diag();
        } break;
        case 1: {
            res = dwt_diag_one(num);
        } break;
        default: {
        } break;
        }
        log_info_res(LG_DWT, res, "Diag");
    } else {
        LOG_ERROR(LG_DWT, "Usage: dwtd Num");
    }

    return res;
}

bool dwt_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_DWT, res, "Num");
    }

    if(0 == argc) {
        res = dwt_mcal_init();
        log_info_res(LG_DWT, res, "Init");
    } else {
        LOG_ERROR(LG_DWT, "Usage: dwti");
    }
    return res;
}
