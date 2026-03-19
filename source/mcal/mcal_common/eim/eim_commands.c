#include "eim_commands.h"

#include "convert.h"
#include "eim_mcal.h"
#include "log.h"

#ifndef HAS_EIM_COMMANDS
#error "+HAS_EIM_COMMANDS"
#endif /*HAS_EIM_COMMANDS*/

bool eim_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(0 <= argc) {
        res = true;
        num = 0;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(LG_EIM, res, "Num");
    }

    if(res) {
        res = eim_diag_one(num);
        res = eim_diag();
        log_res(LG_EIM, res, "Diag");
    } else {
        LOG_ERROR(LG_EIM, "Usage: eimd Num");
    }
    return res;
}


bool eim_init_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(LG_EIM, res, "Num");
    }
    if(res) {
        res = eim_init_one(num);
        log_res(LG_EIM, res, "Init");
    }
    return res;
}

