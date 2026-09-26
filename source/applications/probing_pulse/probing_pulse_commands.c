#include "probing_pulse_commands.h"

#include "convert.h"
#include "log.h"
#include "probing_pulse_mcal.h"


bool probing_pulse_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(PROBING_PULSE, res, "Num");
    }

    if(res) {
        res = probing_pulse_diag_one(num);
        log_info_res(PROBING_PULSE, res, "Diag");

        res = probing_pulse_diag();
        log_info_res(PROBING_PULSE, res, "Diag");
    } else {
        LOG_ERROR(PROBING_PULSE, "Usage: fdat");
    }

    return res;
}

bool probing_pulse_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(PROBING_PULSE, res, "Num");
    }

    if(0 == argc) {
        res = probing_pulse_mcal_init();
        log_info_res(PROBING_PULSE, res, "Init");
    }
    return res;
}
