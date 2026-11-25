#include "systick_mcal.h"

#include "physics_utils.h"
#include "clock_mcal.h"
#include "microcontroller_types.h"
#include "module_driver_scg.h"
#include "std_includes.h"
#include "systick_custom.h"
#include "systick_custom_const.h"

#ifdef HAS_LOG
#include "log.h"
#endif

volatile uint32_t systic_up_time_ms = 0;

bool systick_set_period_ms(uint32_t period_ms) {
    bool res = false;
    uint32_t sys_clock_freq = 0;
    sys_clock_freq = clock_core_freq_get();
    uint32_t load = (period_ms * sys_clock_freq) / 1000;
    res = systick_set_load(load);
    return res;
}

static bool systick_init_low_level(const SysTickConfig_t* const Config) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(LG_SYSTICK, "SysTickInit");
#endif
    if(Config) {
        /*  TODO SCG_GetScgClockFreq shows wrong value on core1         */
        uint32_t freq_hz = 300000000;
        // freq_hz = Config->bus_clock_hz;
        freq_hz = SCG_GetScgClockFreq(SCG_CORE_CLK);
#ifdef HAS_LOG
        LOG_INFO(LG_SYSTICK, "Freq:%u Hz",freq_hz);
#endif

        ClockSetting_t Setting = {0};
        Setting.divider = 1;
        Setting.period = 1;
        res = clock_calc_prescaler(freq_hz, SYSTICK_MAX_VALUE, Config->period_ms, &Setting);

        SysTick_Config( Setting.period);

        if(Config->interrupt_on) {
#ifdef HAS_SYSTICK_INT
            NVIC_SetPriority(SysTick_IRQn, 0);
            NVIC_EnableIRQ(SysTick_IRQn);
#endif
        }

    }

    return res;
}

/*
output the frequency at which the system timer is clocked
 */
uint32_t systick_get_base_freq(void) {
    bool res = false;
    uint32_t frequency_hz = 0;
    res = clock_frequency_get(CLOCK_BUS_PLL0, &frequency_hz);
    if(!res) {
        frequency_hz = 0;
    }
    return frequency_hz;
}

uint32_t systick_cnt_get(void) {
    uint32_t cnt_value = 0;
    return cnt_value;
}

bool systick_custom_start(void) {

    return false;
}

bool systick_stop(void) {
    return false;
}

bool systick_custom_init(void) {
    bool res = false;
    const SysTickConfig_t* Config = SysTickGetConfig(1);
    if(Config) {
        res = systick_init_low_level(Config);
    }
    return res;
}
