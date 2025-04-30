#include "systick_config.h"


SysTickConfig_t SysTickConfig={
                             .base_addr=SysTick_BASE,
                             .period_ms=1,
                             .valid = true,
                             .clksourse = CLK_SRC_PROC,
};

SysTick_t SysTickItem={
                             .err_cnt=0,
                             .SysTickMapPtr=SysTick_BASE,
                             .systick_up_time_ms=0,
};

