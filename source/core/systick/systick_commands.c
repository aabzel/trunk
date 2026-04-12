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
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &load);
        if(false == res) {
            LOG_ERROR(LG_SYSTICK, "Unable to extract period %s", argv[0]);
        }
    }
    if(res) {
        res = systick_set_load(load);
        log_res(LG_SYSTICK, res, "SetLoad");
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: sts load");
    }
    return res;
}

bool systick_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = true;
    }

    if(res) {
#ifdef HAS_SYSTICK_DIAG
        res = systick_diag();
#endif
        log_res(LG_SYSTICK, res, "Diag");
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stkd");
    }
    return res;
}

bool systick_stop_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = systick_stop();
        log_res(LG_SYSTICK, res, "Stop");
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stkp");
    }
    return res;
}

bool systick_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = systick_start();
        log_res(LG_SYSTICK, res, "Start");
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stks");
    }
    return res;
}

bool systick_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;

    if(1 <= argc) {
        res = try_str2bool(argv[0], &on_off);
        log_res(LG_SYSTICK, res, "OnOff");
    }

    if(res) {
        res = systick_ctrl(on_off);
        log_res(LG_SYSTICK, res, "Ctrl");
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stkc OnOff");
    }
    return res;
}

bool systick_clksrc_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t clksrc = SYSTICK_CLK_SRC_UNDEF;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &clksrc);
        log_res(LG_SYSTICK, res, "ClkSrc");
    }

    if(res) {
        res = systick_clksrc_set(clksrc);
        log_write(ResToLogLevel(res), LG_SYSTICK, "SetClkSrc [%s]", SysTickClockSourceToStr(clksrc));
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage stkc ClkSrc");
    }
    return res;
}

bool systick_init_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = systick_mcal_init();
        log_res(LG_SYSTICK, res, "Init");
    } else {
        LOG_ERROR(LG_SYSTICK, "Usage: stki");
    }
    return res;
}
