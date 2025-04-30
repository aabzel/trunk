#include "systick_general_config.h"

#include "clock_utils.h"
#include "board_config.h"

const SysTickConfig_t SysTickConfig = {
    .base_address = SysTick_BASE,
    .int_enable = true,
    .period_ms = 1,
    .bus_clock_hz = SYS_FREQ,
};

SysTick_t SysTickItem = {
    .init_done = true,
    .err_cnt = 0,
    .base_address = (SysTickMap_t*) SysTick_BASE,
    .systick_up_time_ms = 0,
    .systick_int_cnt= 0,
};
