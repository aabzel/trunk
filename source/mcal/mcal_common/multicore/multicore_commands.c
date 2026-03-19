#include "multicore_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "multicore_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

bool multicore_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = multicore_diag();
    return res;
}

bool multicore_control_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    bool on_off = 0;
    if(1 <= argc) {
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(MULTICORE, res, "Num");
        res = try_str2bool(argv[1], &on_off);
        log_res(MULTICORE, res, "OnOff");
    }

    if(res) {
        res = multicore_control(num, on_off);
        log_res(MULTICORE, res, "Ctrl");
    } else {
        LOG_ERROR(MULTICORE, "Usage: mcc Num OnOff");
    }
    return res;
}

bool multicore_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t snum = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &snum);
        log_res(MULTICORE, res, "Num");
    }
    if(res) {
        res = multicore_init_one(snum);
    } else {
        LOG_ERROR(MULTICORE, "Usage: mci Num");
    }
    return res;
}
