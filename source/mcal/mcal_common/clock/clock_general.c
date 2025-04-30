#include "clock.h"

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif
#include "compiler_const.h"
#include "sys_config.h"
#ifdef HAS_TIME
#include "time_mcal.h"
#endif

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
/*
W,[SYS] Set: Freq:100000000 Hz
I,[PLL] FreqXtal:8000000 Hz,FreqSys:100000000  Hz
{ [ (  {Xtal:8000000Hz} /M )*N ]/FR  }= Sys:100000000 Hz
1: MS: 1,NS:100,FR: 8
2: MS: 2,NS:200,FR: 8
3: MS: 3,NS:300,FR: 8
4: MS: 4,NS:400,FR: 8
I,[PLL] SpotPllVals! 4 Solutions
I,[SYS] Pll:M: 4,N:400,FR: 8
I,[SYS] SetOk,Freq:100000000 Hz
 */
_WEAK_FUN_ bool clock_init(void) {
    bool res = true;
#ifdef HAS_PARAM
#ifdef HAS_LOG
    LOG_WARNING(SYS, "ClockInit XTAL:%u Hz", XTALL_FREQ_HZ);
#endif
    uint32_t core_freq_hz = 100000000;
    bool out_res = true;
    (void)out_res;
    LOAD_PARAM(CLK, PAR_ID_SYS_CLOCK_HZ, core_freq_hz, 100000000)
    res = clock_core_freq_set(core_freq_hz);
#else
    clock_config_100mhz();
#endif

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

#ifdef HAS_CLOCK_EXT
uint64_t clock_sw_pause_ms(uint32_t delay_ms) {
    uint64_t cnt = 0;
    uint32_t t = 0;
    for(t = 0; t < delay_ms; t++) {
        cnt += pause_1ms();
    }
    return cnt;
}
#endif

#ifdef HAS_CLOCK_EXT
/* in order to that the power supply has time to
 * spread across the electronic board PCB*/
bool clock_start_pause_init(void) {
    bool res = true;
    clock_sw_pause_ms(200);
    return res;
}
#endif

#ifdef HAS_CLOCK_EXT
bool clock_calc_prescaler(uint32_t base_freq_hz, uint32_t max_val, uint32_t timeout_ms, ClockSetting_t* const Node) {

#ifdef HAS_LOG
    LOG_INFO(CLK, "Clock:%uHz,Max:%u,Period:%u s", base_freq_hz, max_val, timeout_ms);
#endif
    uint32_t cur_div = 0;
    bool res = false;
    double timeout_s = MSEC_2_SEC(timeout_ms);

    double bus_tick_s = 1.0 / ((double)base_freq_hz);
#ifdef HAS_LOG
    LOG_INFO(CLK, "bus_tick:%f s", bus_tick_s);
#endif
    double tick_s = bus_tick_s;
    for(cur_div = 1;; cur_div++) {
        tick_s = bus_tick_s * ((double)cur_div);
        double period_max_s = tick_s * ((double)max_val);
#ifdef HAS_LOG
        LOG_DEBUG(CLK, "Div:%u,Max:%f s", cur_div, period_max_s);
#endif
        if(timeout_s < period_max_s) {
            Node->divider = cur_div;
            Node->period = timeout_s / tick_s;
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
    double bus_tick_s = 1.0 / ((double)bus_freq);
    double bit_rate_tick_s = 1.0 / ((double)bit_rate);

    prescaler1 = (uint32_t)(bit_rate_tick_s / bus_tick_s);

    prescaler2 = (uint32_t)(bus_freq / bit_rate);
#ifdef HAS_LOG
    LOG_INFO(SYS, "prescaler:%u %u", prescaler1, prescaler2);
#endif

    return prescaler1;
}
#endif

#ifdef HAS_CLOCK_EXT
double clock_calc_period_s(uint32_t clock_hz, uint32_t prescaler, uint32_t reload) {
    double bus_tick_s = 1.0 / ((double)clock_hz);
    double tick_s = bus_tick_s * ((double)prescaler);
    double period_s = tick_s * ((double)reload);
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

#ifdef HAS_PARAM
    res = param_set(PAR_ID_SYS_CLOCK_HZ, &core_freq_hz);
    // res = clock_core_freq_set(core_freq_hz);
    if(res) {
#ifdef HAS_LOG
        LOG_INFO(SYS, "SetOk:%u Hz", core_freq_hz);
#endif
        res = core_reboot();
    } else {
        res = false;
#ifdef HAS_LOG
        LOG_ERROR(SYS, "SetErr");
#endif
    }
#endif
    return res;
}
#endif
