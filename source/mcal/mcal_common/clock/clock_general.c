#include "clock_mcal.h"

#include "compiler_const.h"
#include "sys_config.h"
#include "data_utils.h"

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_STORE_FS
#include "store_fs.h"
#endif

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

bool clock_is_valid_config(const ClockConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
#ifdef HAS_DATA_MISC
        res = is_range_uint32(Config->core_clock_hz, 10000, 310000000);
        if(!res) {
#ifdef HAS_LOG
            LOG_ERROR(CLK, "CoreClk,Err,%u Hz", Config->core_clock_hz);
#endif
        }
#endif
    }
    return res;
}

_WEAK_FUN_
bool clock_core_mux_get(ClockMux_t* const clock_mux) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool clock_core_mux_set(const ClockMux_t clock_mux) {
    uint32_t core_freq_hz = 0;
    /*TODO*/
    return core_freq_hz;
}

_WEAK_FUN_ uint32_t clock_core_freq_get(void) {
    uint32_t core_freq_hz = 0;
    /*TODO*/
    return core_freq_hz;
}

_WEAK_FUN_ bool clock_config_100mhz(void) {
    bool res = false;
    return res;
}

uint32_t ClockSourcToHz(const ClockSource_t clock_source) {
    uint32_t frequency_hz = 0;
    switch(clock_source) {
    case CLOCK_SRC_INTERNAL:
        frequency_hz = 0;
        break;
    case CLOCK_SRC_EXTERNAL:
        frequency_hz = 0;
        break;
    case CLOCK_SRC_RTC:
        frequency_hz = 32768;
        break;
    case CLOCK_SRC_EXTERNAL_32MHZ:
        frequency_hz = 32000000;
        break;
    default:
        frequency_hz = 0;
        break;
    }
    return frequency_hz;
}

_WEAK_FUN_ bool clock_config_default(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_ bool clock_mcal_init(void) {
    bool res = true;
#ifdef HAS_LOG
#ifdef XTALL_FREQ_HZ
    LOG_WARNING(SYS, "ClockInit,XTAL:%u Hz", XTALL_FREQ_HZ);
#endif
#endif

    res = clock_is_valid_config(&ClockConfig);
    if(res) {
#ifdef HAS_CLOCK_DIAG
        LOG_WARNING(SYS, "%s", ClockConfigToStr(&ClockConfig));
#endif
        uint32_t core_freq_hz = ClockConfig.core_clock_hz;
#ifdef HAS_STORE_FS
        res = store_fs_get(1, PAR_ID_SYS_CLOCK_HZ, &core_freq_hz);
        if(!res) {
            core_freq_hz = ClockConfig.core_clock_hz;
        }
#endif
        res = clock_core_freq_set(core_freq_hz);
    }

    if(!res) {
        res = clock_config_default();
    }

    return res;
}

//_WEAK_FUN_ uint64_t pause_1ms(void) { return 0; }

#ifdef HAS_CLOCK_EXT
uint32_t clock_int_per_us(uint64_t duration_us) {
    uint32_t cnt = 0;
    if(duration_us) {
        uint64_t start_us = 0;
        start_us = time_get_us();

        uint64_t cur_us = 0;
        uint64_t diff_us = 0;
        while(diff_us < duration_us) {
            cur_us = time_get_us();
            diff_us = cur_us - start_us;
            cnt++;
        }
    }
    return cnt;
}
#endif

#ifdef HAS_CLOCK_EXT
uint32_t clock_int_per_ms(uint32_t delay_ms) {
    uint32_t cnt = 0;
    if(delay_ms) {
        uint32_t start_ms = 0;
        start_ms = time_get_ms32();

        uint32_t cur_ms = 0;
        uint32_t diff_ms = 0;
        while(diff_ms < delay_ms) {
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            cnt++;
        }
    }
    return cnt;
}
#endif

_WEAK_FUN_ uint64_t pause_1ms(void) {
    uint64_t in = 0, cnt = 0;
    for(in = 0; in < 1397; in++) {
        cnt++;
    }
    return cnt;
}

uint64_t clock_sw_pause_ms(uint32_t delay_ms) {
    uint64_t cnt = 0;
    uint32_t t = 0;
    for(t = 0; t < delay_ms; t++) {
        cnt += pause_1ms();
    }
    return cnt;
}
#ifdef HAS_CLOCK_EXT
#endif

/* in order to that the power supply has time to
 * spread across the electronic board PCB*/
bool clock_start_pause_init(void) {
    bool res = true;
    clock_sw_pause_ms(1000);
    return res;
}
#ifdef HAS_CLOCK_EXT
#endif

#ifdef HAS_CLOCK_EXT
/*
  timeout_ms - desired timer overflow duration
  TODO test it
 */
bool clock_calc_prescaler(uint32_t base_freq_hz, uint32_t max_val, uint32_t timeout_ms, ClockSetting_t* const Node) {

#ifdef HAS_LOG
    LOG_INFO(CLK, "Clock:%uHz,Max:%u,Period:%u s", base_freq_hz, max_val, timeout_ms);
#endif
    bool res = false;
    float timeout_s = MSEC_2_SEC(timeout_ms);
    float bus_tick_s = 1.0f / ((float)base_freq_hz);
#ifdef HAS_LOG
    LOG_INFO(CLK, "bus_tick:%f s", bus_tick_s);
#endif
    float tick_s = bus_tick_s;
    uint32_t cur_div = 0;
    for(cur_div = 1;; cur_div++) {
        tick_s = bus_tick_s * ((float)cur_div);
        float period_max_s = tick_s * ((float)max_val);
#ifdef HAS_LOG
        LOG_DEBUG(CLK, "Div:%u,Max:%f s", cur_div, period_max_s);
#endif
        if(timeout_s < period_max_s) {
            Node->divider = cur_div;
            Node->period = (uint32_t)(timeout_s / tick_s);
            res = true;
            break;
        }
    }
#ifdef HAS_CLOCK_DIAG
    LOG_INFO(SYS, "%s", ClockSettingToStr(Node));
#endif
    return res;
}
#endif

#ifdef HAS_CLOCK_EXT
uint32_t calc_prescaler(int32_t bus_freq, int32_t bit_rate) {
    uint32_t prescaler1 = 0;
    uint32_t prescaler2 = 0;
    (void)prescaler1;
    (void)prescaler2;
#ifdef HAS_LOG
    LOG_INFO(SYS, "BitRate:%u bit/s,Bus:%u Hz", bit_rate, bus_freq);
#endif
    float bus_tick_s = 1.0f / ((float)bus_freq);
    float bit_rate_tick_s = 1.0f / ((float)bit_rate);

    prescaler1 = (uint32_t)rintf(bit_rate_tick_s / bus_tick_s);

    prescaler2 = (uint32_t)(bus_freq / bit_rate);
#ifdef HAS_LOG
    LOG_INFO(SYS, "prescaler:%u %u", prescaler1, prescaler2);
#endif

    return prescaler1;
}
#endif

#ifdef HAS_CLOCK_EXT
float clock_calc_period_s(uint32_t clock_hz, uint32_t prescaler, uint32_t reload) {
    float bus_tick_s = 1.0f / ((float)clock_hz);
    float tick_s = bus_tick_s * ((float)prescaler);
    float period_s = tick_s * ((float)reload);
#ifdef HAS_LOG
    LOG_INFO(CLK, "Clock:%u Hz,Div:%u,Period:%u,Period:%f s", clock_hz, prescaler, reload, period_s);
#endif
    return period_s;
}
#endif

#ifdef HAS_CLOCK_EXT

bool clock_core_set_reboot(uint32_t core_freq_hz) {
    bool res = false;
#ifdef HAS_NUM_DIAG
    uint32_t prev_core_freq_hz = clock_core_freq_get();
#ifdef HAS_LOG
    LOG_INFO(CLK, "GetCoreFreq:%s Hz", uint32ToStr(prev_core_freq_hz));
    LOG_INFO(CLK, "SetCoreFreq:%s Hz", uint32ToStr(core_freq_hz));
#endif
#endif

#ifdef HAS_STORE_FS
    res = store_fs_set(1, PAR_ID_SYS_CLOCK_HZ, &core_freq_hz);
    // res = clock_core_freq_set(core_freq_hz);
    if(res) {
#ifdef HAS_LOG
        LOG_INFO(SYS, "SetOk:%u Hz", core_freq_hz);
#endif
#ifdef HAS_CORE
        res = core_reboot();
#endif
    } else {
        res = false;
#ifdef HAS_LOG
        LOG_ERROR(SYS, "SetErr");
#endif
    }
#endif
    return res;
}

_WEAK_FUN_ bool clock_core_freq_set(const uint32_t core_freq_hz) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(CLK, "Set,Clock:%u Hz", core_freq_hz);
#endif
    if(core_freq_hz) {
#ifdef HAS_STORE_FS
        res = store_fs_set(1, PAR_ID_SYS_CLOCK_HZ, &core_freq_hz);
#endif
    }
    return res;
}

#endif /*HAS_CLOCK_EXT*/
