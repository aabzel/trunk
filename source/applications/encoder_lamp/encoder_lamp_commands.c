#include "encoder_lamp_commands.h"

#include "convert.h"
#include "encoder_lamp_mcal.h"
#include "log.h"

bool encoder_lamp_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ENCODER_LAMP, res, "Num");
    }

    if(res) {
        res = encoder_lamp_raw_reg_diag(num);
        log_info_res(ENCODER_LAMP, res, "RegMap");
    } else {
        LOG_ERROR(ENCODER_LAMP, "Usage: encoder_lamprr num");
    }
    return res;
}

bool encoder_lamp_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ENCODER_LAMP, res, "Num");
    }

    if(res) {
        res = encoder_lamp_diag_one(num);
        log_info_res(ENCODER_LAMP, res, "Diag");

        res = encoder_lamp_diag();
        log_info_res(ENCODER_LAMP, res, "Diag");
    } else {
        LOG_ERROR(ENCODER_LAMP, "Usage: fdat");
    }

    return res;
}

bool encoder_lamp_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ENCODER_LAMP, res, "Num");
    }

    if(0 == argc) {
        res = encoder_lamp_mcal_init();
        log_info_res(ENCODER_LAMP, res, "Init");
    }
    return res;
}
