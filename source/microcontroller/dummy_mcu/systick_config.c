#include "systick_config.h"

#include "board_config.h"
#include "clock_utils.h"

const SysTickConfig_t SysTickConfig[] = {
    {
            .num = 1,
#ifdef HAS_VENDOR_SDK
            .SYSTICKx = (SysTickMap_t*) SysTick_BASE,
#endif
            .interrupt_on = true,
            .valid = true,
            .period_ms = 1,
            .bus_clock_hz = 300000000,
    },
};

SysTickHandle_t SysTickInstance[] = {
    {
            .num = 1,
            .init_done = true,
            .err_cnt = 0,
            .int_cnt = 0,
            .valid = true,
    } ,
};

uint32_t systick_get_cnt(void) {
    return 1;
}
