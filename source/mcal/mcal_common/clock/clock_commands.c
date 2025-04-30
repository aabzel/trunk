#include "clock_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "clock.h"
#include "clock_config.h"
#include "convert.h"
#include "ctype.h"
#include "data_utils.h"
#include "log.h"
#include "log_utils.h"
#include "none_blocking_pause.h"
#include "num_to_str.h"
#include "str_utils.h"
#include "time_mcal.h"
#include "timer_utils.h"

#define TIME_OUT_US 800.0
#define TIME_OUT_MS 300.0
bool clock_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t instrictions = 0;

    uint32_t core_freq_hz = clock_core_freq_get();

    LOG_INFO(CLK, "CoreFreq:%s Hz", uint32ToStr(core_freq_hz));
    LOG_INFO(CLK, "ISRcnt: %u", ClockInstance.isr_cnt);

    instrictions = clock_int_per_us(TIME_OUT_US);
    double iterations_per_us = ((double)instrictions) / TIME_OUT_US;
    LOG_INFO(CLK, "Period %f us, Iteration %u, 1Us=%f Iteration", TIME_OUT_US, instrictions,
             ((double)instrictions) / TIME_OUT_US);
    LOG_INFO(CLK, "Iterations/S: %f", iterations_per_us * 1000000.0);

    instrictions = clock_int_per_ms(TIME_OUT_MS);
    double iterations_per_ms = ((double)instrictions) / TIME_OUT_MS;
    LOG_INFO(CLK, "Period %f ms, %u iterations, InstrPerMs: %f", TIME_OUT_MS, instrictions, iterations_per_ms);
    LOG_INFO(CLK, "Iterations/S: %f", iterations_per_ms * 1000.0);
    res = true;

    return res;
}

bool clock_sw_pause_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t time_ms = 0;
    if(1 == argc) {
        res = try_str2uint32(argv[0], &time_ms);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr TimeMs %s", argv[0]);
        }
    }

    if(res) {
        res = false;
        uint64_t cnt = 0;
        LOG_INFO(SYS, "Start");
        cnt = clock_sw_pause_ms(time_ms);
        LOG_INFO(SYS, "End %llu", cnt);
        res = true;
    } else {
        LOG_ERROR(SYS, "Usage: swp TimeMs");
    }
    return res;
}

bool clock_hw_pause_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        uint32_t time_ms = 0;
        res = try_str2uint32(argv[0], &time_ms);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr TimeMs %s", argv[0]);
        }

        if(res) {
            LOG_INFO(SYS, "Start");
            res = wait_in_loop_ms(time_ms);
            LOG_INFO(SYS, "End");
        }
    } else {
        LOG_ERROR(SYS, "Usage: swp time_ms");
    }
    return res;
}

/*TODO mode to time commands*/
bool clock_up_time_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        uint32_t time_ms = 0;
        time_ms = time_get_ms32();
        cli_printf("UpTime: %u ms" CRLF, time_ms);
    } else {
        LOG_ERROR(SYS, "Usage: ut");
    }
    return res;
}

// ccs 101000000
// ccs 200000000
bool clock_core_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t core_freq_hz = 100000000;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &core_freq_hz);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr CoreCockHz %s", argv[0]);
        }
    }

    if(res) {
        switch(argc) {
        case 0: {
            core_freq_hz = clock_core_freq_get();
            LOG_INFO(CLK, "GetCoreFreq:%s Hz", uint32ToStr(core_freq_hz));
        } break;
        case 1: {
            LOG_INFO(CLK, "SetCoreFreq:%s Hz", uint32ToStr(core_freq_hz));
            res = clock_core_set_reboot(core_freq_hz);
            if(res) {
                LOG_INFO(SYS, "SetOk");
            } else {
                LOG_ERROR(SYS, "SetErr");
            }
        } break;
        }

    } else {
        LOG_ERROR(SYS, "Usage: ccs CoreFreqHz");
    }
    return res;
}
