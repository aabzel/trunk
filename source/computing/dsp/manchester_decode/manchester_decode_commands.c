#include "manchester_decode_commands.h"

#include "convert.h"
#include "log.h"
#include "manchester_decode_mcal.h"



bool manchester_decode_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MANCHESTER_DECODE, res, "Num");
    }

    if(res) {
        res = manchester_decode_diag_one(num);
        log_info_res(MANCHESTER_DECODE, res, "Diag");

        res = manchester_decode_diag();
        log_info_res(MANCHESTER_DECODE, res, "Diag");
    } else {
        LOG_ERROR(MANCHESTER_DECODE, "Usage: fdat");
    }

    return res;
}

bool manchester_decode_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MANCHESTER_DECODE, res, "Num");
    }

    if(0 == argc) {
        res = manchester_decode_mcal_init();
        log_info_res(MANCHESTER_DECODE, res, "Init");
    }
    return res;
}
