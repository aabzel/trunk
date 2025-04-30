#include "systick_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "systick_custom.h"
#include "systick_general.h"
#include "timer_utils.h"

bool systick_nrf53_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    return res;
}

bool systick_set_period_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t period_ms=0;
    if(1 == argc){
        res = try_str2uint32(argv[0], &period_ms);
        if(false == res) {
            LOG_ERROR(LG_SYSTICK, "Unable to extract period %s", argv[0]);
        }
    }
    if(res){
        res = systick_set_period_ms( period_ms);
    }else {
        LOG_ERROR(LG_SYSTICK, "Usage: stksp PeriodMs");
    }
    return res;
}



