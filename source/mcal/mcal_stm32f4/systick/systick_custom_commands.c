#include "systick_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "stm32f4xx_hal.h"
#include "systick_stm32.h"
#include "systick_general.h"
#include "timer_utils.h"

bool systick_stm32_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        LOG_INFO(SYS, "BaseAddr 0x%08X", SysTick_BASE);
        uint32_t sys_clk = HAL_RCC_GetSysClockFreq();
        LOG_INFO(SYS, "SysClk %u Hz", sys_clk);

        uint32_t load=systick_general_get_load();
        LOG_INFO(SYS, "load %u", load);

        uint32_t period_ms=systick_get_period_ms();
        LOG_INFO(SYS, "Period %u ms", period_ms);

    }else {
        LOG_ERROR(SYS, "Usage: stksd keyWord");
    }
    return res;
}

bool systick_set_period_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t period_ms=0;
    if(1 == argc){
        res = try_str2uint32(argv[0], &period_ms);
        if(false == res) {
            LOG_ERROR(LG_SYSTICK, "Unable to extract period %s", argv[0]);
        }
    }
    if(res){
        res = systick_set_period_ms( period_ms);
    }else {
        LOG_ERROR(LG_SYSTICK, "Usage: stksp PeriodMs");
    }
    return res;
}



