#include "delta_sigma_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "convert.h"
#include "delta_sigma.h"
#include "log.h"

/*
dst 1 0.5
dst 1 1
dst 1 0.999
dst 1 0.99
dst 1 0.85
dst 1 0.9
dst 1 0.75
dst 1
tf 1 20000

tf 1 40000
 * */
bool delta_sigma_target_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    float target = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DELTA_SIGMA, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &target);
        if(false == res) {
            LOG_ERROR(DELTA_SIGMA, "Arg2 target %s", argv[1]);
        }
    }

    if(res) {
        switch(argc) {

        case 1: {
            target = delta_sigma_target_get(num);
            LOG_INFO(DELTA_SIGMA, "target:%f", target);
        } break;

        case 2: {
            res = delta_sigma_target_set(num, target);
        } break;

        default: {
        } break;
        }
    } else {
        LOG_ERROR(DELTA_SIGMA, "Usage: dst Num Target");
    }
    return res;
}

// dst 1
bool delta_sigma_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DELTA_SIGMA, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(res) {
        res = delta_sigma_diag(num);
        if(res) {
        } else {
            LOG_ERROR(DELTA_SIGMA, "GenerateErr");
        }
    } else {
        LOG_ERROR(DELTA_SIGMA, "Usage: dsd Num");
    }
    return res;
}
