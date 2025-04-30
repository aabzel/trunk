#include "systick_custom.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_LOG
#include "log.h"
#endif
#ifdef HAS_CLOCK
#include "clock.h"
#endif
#include "systick_general.h"
#include "systick_custom_const.h"
#include "nrf_systick.h"


volatile uint32_t systic_up_time_ms = 0;

bool systick_set_period_ms(uint32_t period_ms){
    bool res = false;
    uint32_t sys_clock_freq = 0;
    uint32_t load=(period_ms*sys_clock_freq)/1000;
    res=systick_set_load(load);
    return res;
}

bool systick_init(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(SYS, "SysTickInit");
#endif
    res = systick_general_init(SysTick_BASE, SYS_FREQ);

#if 0
    nrf_systick_load_set(SystemCoreClock / (1000UL / (uint32_t)1)); // 1Khz
    nrf_systick_csr_set(
        NRF_SYSTICK_CSR_CLKSOURCE_CPU |
        NRF_SYSTICK_CSR_TICKINT_ENABLE |
        NRF_SYSTICK_CSR_ENABLE);
#endif
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 7, 0));
    return res;
}

uint32_t systick_get_period_ms(void){
    uint32_t period_ms=0;
    double period=0.0;
    double tick=0.0;
    uint32_t load = systick_general_get_load();
    uint32_t sys_clock_freq = 0;
    sys_clock_freq = 50000000;
    tick = 1.0/sys_clock_freq;
    period=tick*((double)load);
    period_ms=(uint32_t) (period*1000.0);
    return period_ms;
}


