#include "scr1_timer_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "scr1_timer.h"

#include "clock.h"
#include "clock_utils.h"
#include "common_diag.h"
#include "sys_config.h"
#include "time_mcal.h"
#include "timer_utils.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool scr1_timer_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = scr1_timer_diag();
        log_res(SCR_TIMER, res, "Diag");
    } else {
        LOG_ERROR(SCR_TIMER, "Usage: stkd");
    }
    return res;
}

bool scr1_timer_stop_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = scr1_timer_stop();
        log_res(SCR_TIMER, res, "Stop");
    } else {
        LOG_ERROR(SCR_TIMER, "Usage: stkp");
    }
    return res;
}

bool scr1_timer_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = scr1_timer_reset();
        log_res(SCR_TIMER, res, "Reset");
    } else {
        LOG_ERROR(SCR_TIMER, "Usage: str");
    }
    return res;
}

bool scr1_timer_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = scr1_timer_start();
        log_res(SCR_TIMER, res, "Start");
    } else {
        LOG_ERROR(SCR_TIMER, "Usage: stks");
    }
    return res;
}

bool scr1_timer_init_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = scr1_timer_init();
        log_res(SCR_TIMER, res, "Init");
    } else {
        LOG_ERROR(SCR_TIMER, "Usage: stks");
    }
    return res;
}

bool scr1_timer_set_cnt_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint64_t counter = 0;
    if(1 <= argc) {
        res = try_str2uint64(argv[0], &counter);
    }
    if(res) {
        res = scr1_timer_counter_set(&Scr1TimerInstance, counter);
        log_res(SCR_TIMER, res, "CntSet");
    }
    return res;
}
