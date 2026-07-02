#include "systick_config.h"

#include "board_config.h"
#include "clock_utils.h"


const SysTickConfig_t SECTION_CFG_DATA SysTickConfig[] = {
    {
            .num = 1,
#ifdef HAS_VENDOR_SDK
            .SYSTICKx = (SysTickMap_t*) SysTick_BASE,
#endif
            .interrupt_on = true,
            .clk_source = SYSTICK_CLK_SRC_PROC,
            .valid = true,
            .period_ms = 1,
            .bus_clock_hz = 96000000,
    },
};

SysTickHandle_t SysTickInstance[] = {
    {
            .num = 1,
            .init_done = true,
            .err_cnt = 0,
#ifdef HAS_VENDOR_SDK
            .SYSTICKx = (SysTickMap_t*) SysTick_BASE,
#endif
            .int_cnt = 0,
            .valid = true,
    } ,
};

uint32_t systick_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt_node = 0;
    uint32_t cnt_cfg = 0;
    cnt_node = ARRAY_SIZE( SysTickInstance);
    cnt_cfg = ARRAY_SIZE( SysTickConfig);
    if(cnt_cfg <= cnt_node) {
        cnt = cnt_cfg;
    }
    return cnt;
}
