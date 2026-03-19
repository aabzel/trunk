#include "trng_commands.h"

#include "convert.h"
#include "log.h"
#include "trng_mcal.h"

bool trng_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(TRNG, res, "Num");
    }

    if(res) {
        res = trng_diag_one(num);
        log_info_res(TRNG, res, "Diag");

        res = trng_diag();
        log_info_res(TRNG, res, "Diag");
    } else {
        LOG_ERROR(TRNG, "Usage: fdat");
    }

    return res;
}

bool trng_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(TRNG, res, "Num");
    }

    if(0 == argc) {
        res = trng_mcal_init();
        log_info_res(TRNG, res, "Init");
    }
    return res;
}
