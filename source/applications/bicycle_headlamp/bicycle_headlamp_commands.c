#include "bicycle_headlamp_commands.h"

#include "convert.h"
#include "log.h"
#include "bicycle_headlamp_mcal.h"


bool bicycle_headlamp_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BICYCLE_HEADLAMP, res, "Num");
    }

    if(res) {
        res = bicycle_headlamp_diag_one(num);
        log_info_res(BICYCLE_HEADLAMP, res, "Diag");

        res = bicycle_headlamp_diag();
        log_info_res(BICYCLE_HEADLAMP, res, "Diag");
    } else {
        LOG_ERROR(BICYCLE_HEADLAMP, "Usage: fdat");
    }

    return res;
}

bool bicycle_headlamp_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BICYCLE_HEADLAMP, res, "Num");
    }

    if(0 == argc) {
        res = bicycle_headlamp_mcal_init();
        log_info_res(BICYCLE_HEADLAMP, res, "Init");
    }
    return res;
}
