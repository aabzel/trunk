#include "systick_mcal.h"

#include "clock/clock.h"
#include "microcontroller_types.h"
#include "module_driver_scg.h"
#include "module_driver_systick.h"
#include "std_includes.h"
#include "systick_custom.h"
#include "systick_custom_const.h"

#ifdef HAS_LOG
#include "log.h"
#endif
//#include "x86x_x86x_cortex.h"

// extern SysTick_t SysTickItem;
volatile uint32_t systic_up_time_ms = 0;

bool systick_set_period_ms(uint32_t period_ms) {
    bool res = false;
    uint32_t sys_clock_freq = 0;
    sys_clock_freq = clock_core_freq_get();
    uint32_t load = (period_ms * sys_clock_freq) / 1000;
    res = systick_general_set_load(load);
    return res;
}

static bool systick_init_low_level(const SysTickConfig_t* const Config) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(SYS, "SysTickInit");
#endif
    if(Config) {
        /*
         TODO SCG_GetScgClockFreq shows wrong value on core1
         */
        uint32_t freq_hz = 300000000;
        // freq_hz = Config->bus_clock_hz;
        freq_hz = SCG_GetScgClockFreq(SCG_CORE_CLK);
        systickType TickCfg = {0};
        /* Use processor clock flag. */
        TickCfg.bUseProcessorclock = true;
        /* SysTick interrupt enable flag. */
        TickCfg.bTickInt = Config->interrupt_on;

        ClockSetting_t Setting = {0};
        Setting.divider = 1;
        Setting.period = 1;
        res = clock_calc_prescaler(freq_hz, SYSTICK_MAX_VALUE, Config->period_ms, &Setting);

        /* Counter reload value. */
        TickCfg.u32LoadValue = Setting.period;

        SYSTICK_Init(&TickCfg);

        if(Config->interrupt_on) {
#ifdef HAS_SYSTICK_INT
            NVIC_SetPriority(SysTick_IRQn, 0);
            NVIC_EnableIRQ(SysTick_IRQn);
#endif /*HAS_SYSTICK_INT*/
        }

        SysTick_Enable();
    }

    return res;
}

uint32_t systick_cnt_get(void) {
    uint32_t cnt_value = 0;
    cnt_value = SysTick_GetCntValue();
    return cnt_value;
}

bool systick_start(void) {
    SysTick_Enable();
    return true;
}

bool systick_stop(void) {
    SysTick_Disable();
    return true;
}

bool systick_custom_init(void) {
    bool res = false;
    res = systick_init_low_level(&SysTickConfig);
    return res;
}

#if 0
bool systick_disable(void) {
    bool res = true;
    LOG_WARNING(SYS, "SysTickStop");
    // res = systick_general_init();

    SysTickCntl_t SysTickCntl;
    SysTickCntl.reg_val = 0xFF;
    SysTickCntl.enable = 0;
    SysTickCntl.tickint = 0;
    SysTickCntl.clksourse = STK_CLK_SRC_AHB;
    SysTick->CTRL = SysTickCntl.reg_val;
    return res;
}
#endif

uint32_t systick_get_period_ms(void) {
    uint32_t period_ms = 0;
    double period = 0.0;
    double tick = 0.0;
    uint32_t load = systick_general_get_load();
    uint32_t sys_clock_freq = 0;
    // sys_clock_freq = HAL_RCC_GetSysClockFreq( );
    tick = 1.0 / sys_clock_freq;
    period = tick * ((double)load);
    period_ms = (uint32_t)(period * 1000.0);
    return period_ms;
}
