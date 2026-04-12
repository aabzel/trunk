#include "systick_config.h"

#include "clock_utils.h"
#include "board_config.h"

const SysTickConfig_t SysTickConfig[] ={ {
    .SYSTICKx = SysTick_BASE,
    .bus_clock_hz = 84000000,
    .valid = true,
    .num = 1,
    .clk_source = SYSTICK_CLK_SRC_PROC,
    .interrupt_on = true,
    .period_ms = 1,
},
};

SysTickHandle_t SysTickInstance[] = { {
    .valid = true,
    .num = 1,
    .err_cnt = 0,
    .int_cnt = 0,
    .SYSTICKx = (SysTickMap_t*)SysTick_BASE,
},
};


uint32_t systick_get_cnt(void) { return 1; }
