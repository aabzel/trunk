#include "timer_custom_commands.h"

#include <inttypes.h>

#include "clock.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "timer_diag.h"
#include "timer_mcal.h"
#include "writer_config.h"

bool timer_raw_reg_command(int32_t argc, char* argv[]) {
    uint8_t num = 3;
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr TIMER Number [1-%d]", TIMER_COUNT);
        }
    }

    if(res) {
        res = timer_raw_reg_diag(num);
    } else {
        LOG_ERROR(TIMER, "Usage timra Num");
    }

    return res;
}

bool timer_reg_parse_command(int32_t argc, char* argv[]) {
    uint8_t num = 2;
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr TIMER Number [1-%d]", TIMER_COUNT);
        }
    }

    if(res) {
        res = timer_reg_parse(num);
    } else {
        LOG_ERROR(TIMER, "Usage timra Num");
    }

    return res;
}
