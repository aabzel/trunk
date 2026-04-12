#include "time_commands.h"

#include <stdio.h>
#include <time.h>

#include "convert.h"
#include "log.h"
#include "time_diag.h"
#include "time_mcal.h"

bool time_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = time_diag();
#ifdef HAS_RTC
    struct tm time_date;
    res = time_get_cur_utc(&time_date);
    if(res) {
        res = print_time_date("UTC:", &time_date, true);
    } else {
        LOG_ERROR(TIME, "GetUTCTimeErr");
    }
#endif
    return res;
}

bool time_synchronize_command(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_TIME_SYNCHRONIZE
    res = time_synchronize();
#endif
    return res;
}

bool time_time_command(int32_t argc, char* argv[]) {
    bool res = true;

    time_t seconds;
    struct tm* cur_time;
    seconds = time(NULL);
    cur_time = localtime(&seconds);

    LOG_INFO(TIME, "Current time : %d:%d:%d\n", cur_time->tm_hour, cur_time->tm_min, cur_time->tm_sec);
    print_time(cur_time);
    print_time_date("TIME", cur_time, true);
    return res;
}

bool time_wait_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t delay_in_ms = 1000;
    if(0 <= argc) {
        delay_in_ms = 1000;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &delay_in_ms);
        if(false == res) {
            LOG_ERROR(TIME, "ParseErr DelayMs");
        }
    }

    if(res) {
        LOG_INFO(TIME, "Delay %u Ms", delay_in_ms);
        res = wait_in_loop_ms(delay_in_ms);
    }
    return res;
}

bool time_wait_loop_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t delay_in_ms = 1000;
    if(0 <= argc) {
        delay_in_ms = 0;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &delay_in_ms);
        if(false == res) {
            LOG_ERROR(TIME, "ParseErr DelayMs");
        }
    }

    if(res) {
        LOG_DEBUG(TIME, "DelayInLoop %u Ms", delay_in_ms);
        res = wait_in_loop_ms(delay_in_ms);
        log_debug_res(TIME, res, "WaitLoop");
    } else {
        LOG_ERROR(TIME, "Usage: twl ms");
    }
    return res;
}

bool time_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = time_mcal_init();
    log_info_res(TIME, res, "Init");
    return res;
}
