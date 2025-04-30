#include "systick_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "log.h"
#include "systick_mcal.h"
#include "time_mcal.h"

bool systick_set_load_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t load = 0;
    if(1 == argc) {
        if(res) {
            res = try_str2uint32(argv[0], &load);
            if(false == res) {
                LOG_ERROR(LG_SYSTICK, "Unable to extract period %s", argv[0]);
            }
        }
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: sts load");
    }
    if(res) {
        res = systick_general_set_load(load);
    }
    return res;
}

bool systick_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = true;

    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stkd");
    }

    if(res) {
        LOG_INFO(LG_SYSTICK, "Enable %s", OnOffToStr(systick_general_is_run()));
        LOG_INFO(LG_SYSTICK, "Err %u", SysTickItem.err_cnt);
        uint32_t up_time_ms = systick_general_get_ms();
        LOG_INFO(LG_SYSTICK, "up_time_ms %llu ms", up_time_ms);
        LOG_INFO(LG_SYSTICK, "IntCnt %llu ms", SysTickItem.up_time_ms);
        LOG_INFO(LG_SYSTICK, "up_time_ms %f s", MSEC_2_SEC(up_time_ms));
        LOG_INFO(LG_SYSTICK, "up_time_ms %f m", MSEC_2_MIN(up_time_ms));
    }
    return res;
}

bool systick_stop_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = systick_general_stop();
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stkp");
    }
    return res;
}

bool systick_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = systick_general_start();
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stks");
    }
    return res;
}
