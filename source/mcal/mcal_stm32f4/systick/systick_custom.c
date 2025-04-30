#include "systick_custom.h"

#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#include "clock.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "systick_custom_const.h"
#include "systick_mcal.h"

// extern SysTick_t SysTickItem;
volatile uint32_t systic_up_time_ms = 0;

bool systick_set_period_ms(uint32_t period_ms) {
    bool res = false;
    uint32_t sys_clock_freq = 0;
    sys_clock_freq = HAL_RCC_GetSysClockFreq();
    uint32_t load = (period_ms * sys_clock_freq) / 1000;
    res = systick_general_set_load(load);
    return res;
}

bool systick_custom_init(void) {
    bool res = true;
    LOG_INFO(SYS, "SysTickInit");
    res = systick_general_init();
    systick_set_period_ms(1);

    SysTickCntl_t SysTickCntl;
    SysTickCntl.reg_val = 0;
    SysTickCntl.enable = 1;
    SysTickCntl.tickint = 0;
#ifdef HAS_SYSTICK_INT
    SysTickCntl.tickint = 1;
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
    NVIC_EnableIRQ(SysTick_IRQn);
#endif /*HAS_SYSTICK_INT*/
    SysTickCntl.clksourse = STK_CLK_SRC_AHB;
    SysTick->CTRL = SysTickCntl.reg_val;
    return res;
}

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

uint32_t systick_get_period_ms(void) {
    uint32_t period_ms = 0;
    double period = 0.0;
    double tick = 0.0;
    uint32_t load = systick_general_get_load();
    uint32_t sys_clock_freq = 0;
    sys_clock_freq = HAL_RCC_GetSysClockFreq();
    tick = 1.0 / sys_clock_freq;
    period = tick * ((double)load);
    period_ms = (uint32_t)(period * 1000.0);
    return period_ms;
}

bool systick_hal_suspend(void) {
    bool res = true;
    HAL_SuspendTick();
    return res;
}
