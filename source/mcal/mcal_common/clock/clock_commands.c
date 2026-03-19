#include "clock_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "clock_mcal.h"
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

bool clock_mux_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t code = CLOCK_MUX_UNDEF;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &code);
        log_info_res(CLK, res, "ReadMux");
    }

    if(res) {
        if(1 == argc) {
            res = clock_core_mux_set((ClockMux_t)code);
            log_info_res(CLK, res, "MuxSet");
        } else {
            ClockMux_t clock_mux = CLOCK_MUX_UNDEF;
            res = clock_core_mux_get(&clock_mux);
            log_info_res(CLK, res, "MuxGet");
            if(res) {
#ifdef HAS_CLOCK_DIAG
                LOG_INFO(CLK, "Mux:%s", ClockMuxToStr(clock_mux));
#endif
            }
        }
    }

    return res;
}

bool clock_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = clock_diag();
    return res;
}

bool clock_sw_pause_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t time_ms = 0;
    if(1 == argc) {
        res = try_str2uint32(argv[0], &time_ms);
        log_info_res(CLK, res, "ReadTimeMs");
    }

    if(res) {
        res = false;
        uint64_t cnt = 0;
        LOG_INFO(CLOCK, "Start");
        cnt = clock_sw_pause_ms(time_ms);
        LOG_INFO(CLOCK, "End %llu", cnt);
        res = true;
    } else {
        LOG_ERROR(CLOCK, "Usage: swp TimeMs");
    }
    return res;
}

bool clock_hw_pause_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        uint32_t time_ms = 0;
        res = try_str2uint32(argv[0], &time_ms);
        if(false == res) {
            LOG_ERROR(CLOCK, "ParseErr TimeMs %s", argv[0]);
        }

        if(res) {
            LOG_INFO(CLOCK, "Start");
            res = wait_in_loop_ms(time_ms);
            LOG_INFO(CLOCK, "End");
        }
    } else {
        LOG_ERROR(CLOCK, "Usage: swp time_ms");
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
        LOG_ERROR(CLOCK, "Usage: ut");
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
        log_info_res(CLK, res, "ReadFreq");
    }

    if(res) {
        switch(argc) {
        case 0: {
            core_freq_hz = clock_core_freq_get();
            LOG_INFO(CLK, "GetCoreFreq:%s Hz", uint32ToStr(core_freq_hz));
        } break;
        case 1: {
            LOG_INFO(CLK, "SetCoreFreq:%s Hz", uint32ToStr(core_freq_hz));
            res = clock_core_freq_set(core_freq_hz);
            log_info_res(CLK, res, "Set");
        } break;
        default:
            res = false;
            break;
        }

    } else {
        LOG_ERROR(CLOCK, "Usage: ccs CoreFreqHz");
    }
    return res;
}

bool clock_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = clock_mcal_init();
    return res;
}
