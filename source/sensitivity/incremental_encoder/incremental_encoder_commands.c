#include "incremental_encoder_commands.h"

#include "convert.h"
#include "log.h"
#include "incremental_encoder_mcal.h"


bool incremental_encoder_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(INCREMENTAL_ENCODER, res, "Num");
    }

    if(res) {
        res = incremental_encoder_diag_one(num);
        log_info_res(INCREMENTAL_ENCODER, res, "Diag");

        res = incremental_encoder_diag();
        log_info_res(INCREMENTAL_ENCODER, res, "Diag");
    } else {
        LOG_ERROR(INCREMENTAL_ENCODER, "Usage: fdat");
    }

    return res;
}

bool incremental_encoder_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(INCREMENTAL_ENCODER, res, "Num");
    }

    if(0 == argc) {
        res = incremental_encoder_mcal_init();
        log_info_res(INCREMENTAL_ENCODER, res, "Init");
    }
    return res;
}


bool incremental_encoder_set_0_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(INCREMENTAL_ENCODER, res, "Num");
    }

    if(res) {
        res = incremental_encoder_set_0(num);
        log_info_res(INCREMENTAL_ENCODER, res, "Set0");
    } else {
        LOG_ERROR(INCREMENTAL_ENCODER, "Usage: iens0 N");
    }
    return res;
}
