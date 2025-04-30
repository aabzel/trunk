#include "clock_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "clock.h"
#include "clock_custom.h"
#include "clock_custom_diag.h"
#include "clock_diag.h"
#include "common_diag.h"
#include "convert.h"
#include "ctype.h"
#include "data_utils.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "nrfx_clock.h"
#include "ostream.h"
#include "str_utils.h"
#include "timer_utils.h"

bool clock_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(CLK, "DiagLowLevel");
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = clock_diag_low_level();
    } else {
        LOG_ERROR(CLK, "Usage: clkd");
    }

    return res;
}

bool clock_diag_low_freq_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(CLK, "DiagLowFreq");
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = clock_diag_low_freq();
    } else {
        LOG_ERROR(CLK, "Usage: cldl");
    }
    return res;
}

bool clock_diag_high_frequency_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(CLK, "DiagHiFreq");
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = clock_diag_high_frequency();
    }
    return res;
}

// clct 2 0
bool clock_control_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    LOG_INFO(CLK, "Control");
    uint8_t domain = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &domain);
        res = try_str2bool(argv[1], &on_off);
    }

    if(res) {
        res = clock_control(domain, on_off);
        if(res) {
            LOG_INFO(CLK, "Ok");
        }
    } else {
        LOG_ERROR(CLK, "Usage: clct Domain OnOff");
    }

    return res;
}

/*
 * cldv 1 2
 * */
bool clock_nrfx_div_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t divider = 0;
    uint8_t domain = 0;
    LOG_INFO(CLK, "SetDivider...");

    if(2 == argc) {
        res = try_str2uint8(argv[0], &domain);
        res = try_str2uint8(argv[1], &divider);
    }

    if(res) {
        nrf_clock_hfclk_div_t nrf_divider = 0;
        nrf_clock_domain_t nrf_domain = ClockDomainToNrfxDomain(domain);
        nrf_divider = ClockDividerToNrfDivider(divider);

        nrfx_err_t ret = nrfx_clock_divider_set((nrf_clock_domain_t)nrf_domain, (nrf_clock_hfclk_div_t)nrf_divider);
        if(NRFX_SUCCESS == ret) {
            LOG_INFO(CLK, "Ok");
        } else {
            LOG_ERROR(CLK, "Err 0x%x=%s", ret, HalStatus2Str(ret));
        }

    } else {
        LOG_ERROR(CLK, "Usage: cldv domain div");
    }
    return res;
}

bool clock_nrfx_sleep_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(CLK, "Sleep");
    res = clock_nrfx_sleep();
    if(res) {
        LOG_INFO(CLK, "Ok");
    } else {
        LOG_ERROR(CLK, "Usage: cns");
    }
    return res;
}

bool clock_nrfx_audio_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t freq_value = 0;
    double freq_audio_hz = 0.0;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint16(argv[0], &freq_value);
    }

    if(res) {
        switch(argc) {
        case 0: {
            freq_value = nrfx_clock_hfclkaudio_config_get();
            freq_audio_hz = clock_audio_calc(freq_value);
            LOG_INFO(CLK, "FreqValueGet:%u,%f Hz", freq_value, freq_audio_hz);
            res = true;
        } break;
        case 1: {
            freq_audio_hz = clock_audio_calc(freq_value);
            LOG_INFO(CLK, "FreqValueSet:%u,%f Hz", freq_value, freq_audio_hz);
            nrfx_clock_hfclkaudio_config_set(freq_value);
            res = true;
        } break;
        }
    } else {
        LOG_ERROR(CLK, "Usage: cna FreqValue");
    }

    return res;
}
