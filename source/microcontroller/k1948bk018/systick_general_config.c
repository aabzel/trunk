#include "systick_general_config.h"

#include "board_config.h"
#include "clock_utils.h"

#ifndef SCS_BASE
#define SCS_BASE (0xE000E000UL)
#endif

#ifndef SysTick_BASE
#define SysTick_BASE (SCS_BASE + 0x0010UL)
#endif

const SysTickConfig_t SysTickConfig = {
    .SYSTICKx = (SysTickMap_t*)SysTick_BASE, .interrupt_on = true, .period_ms = 1,
    //.bus_clock_hz = SYS_FREQ,
};

SysTickHandle_t SysTickItem = {
    .init_done = true,
    .err_cnt = 0,
    .SYSTICKx = (SysTickMap_t*)SysTick_BASE,
    .up_time_ms = 0,
    .int_cnt = 0,
};
