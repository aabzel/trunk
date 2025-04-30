#include "systick_general_config.h"

#include "board_config.h"
#include "clock_utils.h"
//#include "core_cm4.h"

#ifndef SCS_BASE
#define SCS_BASE (0xE000E000UL)
#endif

#ifndef SysTick_BASE
#define SysTick_BASE (SCS_BASE + 0x0010UL)
#endif

const SysTickConfig_t SysTickConfig = {
    .base_address = SysTick_BASE, .int_enable = true, .period_ms = 1,
    //.bus_clock_hz = SYS_FREQ,
};

SysTick_t SysTickItem = {
    .init_done = true,
    .err_cnt = 0,
    .base_address = (SysTickMap_t*)SysTick_BASE,
    .up_time_ms = 0,
    .int_cnt = 0,
};
