#include "ext_int_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "ext_int_mcal.h"
#include "log.h"

bool ext_int_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = ext_int_diag();
    log_info_res(EXT_INT, res, "Diag");
    return res;
}

bool ext_int_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 == argc) {
        res = ext_int_mcal_init();
        log_info_res(EXT_INT, res, "Init");
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(EXT_INT, res, "Num");
        res = ext_int_init_one(num);
        log_info_res(EXT_INT, res, "ExtIntOne");
    }

    if(res) {
    }
    return res;
}
