#include "clock_divider_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "convert.h"
#include "clock_divider.h"
#include "log.h"

//psd 1
bool clock_divider_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;


    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CLOCK_DIVIDER , "Arg1 FreqErr %s", argv[0]);
        }
    }


    if(res) {
        res = clock_divider_diag(num);
        if(res) {
        } else {
            LOG_ERROR(CLOCK_DIVIDER , "GenerateErr");
        }
    } else {
        LOG_ERROR(CLOCK_DIVIDER , "Usage: psd Num");
    }
    return res;
}

/*
 * psn 1 1
 * psn 1 2
 * psn 1 3
 * psn 1 4
 */
bool clock_divider_n_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t divider = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &divider);
    }

    if(res) {
        LOG_INFO(CLOCK_DIVIDER , "divider:%u", divider);
        res = clock_divider_set(num,divider);
    }

    return res;
}
