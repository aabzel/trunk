#include "systick_config.h"

#include "board_config.h"
#include "clock_utils.h"


//#ifndef SysTick_BASE
//#define SysTick_BASE (SEC_BASE + 0x0010UL)
//#endif

const SysTickConfig_t SysTickConfig = {
    .SYSTICKx = (SysTickMap_t*) SysTick_BASE,
    .interrupt_on = true,
    .period_ms = 1,
    .bus_clock_hz = 300000000,
};

SysTickHandle_t SysTickInstance = {
    .init_done = true,
    .err_cnt = 0,
    .SYSTICKx = (SysTickMap_t*) SysTick_BASE,
    .up_time_ms = 0,
    .int_cnt = 0,
};
