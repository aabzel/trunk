#include "systick_config.h"

#include "board_config.h"
#include "clock_utils.h"

const SysTickConfig_t SysTickConfig[] = {
    {
        .SYSTICKx = SysTick_BASE,
        .period_ms = 1,
        .clk_source = SYSTICK_CLK_SRC_PROC, //
        .num = 1,
        .interrupt_on = true,
        .valid = true,
        .bus_clock_hz = 48000000,
    },
};

SysTickHandle_t SysTickInstance[] = {
    {
            .num = 1,
            .valid = true,
            .err_cnt = 0,
            .int_cnt = 0,
#ifdef HAS_VENDOR_SDK
            .SYSTICKx = (SysTickMap_t*) SysTick_BASE,
#endif
    },
};

uint32_t systick_get_cnt(void) { return 1; }
