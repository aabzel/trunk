#include "lockstep_commands.h"

#include <stdio.h>

#include "convert.h"
#include "lockstep_mcal.h"
#include "log.h"

bool lockstep_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t num = 0;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        switch(argc) {
        case 0: {
            res = lockstep_diag();
            log_res(LOCKSTEP, res, "Diag");
        } break;
        case 1: {
            res = lockstep_diag_one(num);
            log_res(LOCKSTEP, res, "DiagN");
        } break;
        default:
            break;
        }
    } else {
        LOG_ERROR(LOCKSTEP, "Usage mbd Num");
    }

    return res;
}

bool lockstep_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }
    if(res) {
        res = lockstep_init_one(num);
        log_res(LOCKSTEP, res, "Init");
    }
    return res;
}
