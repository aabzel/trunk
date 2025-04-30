#include "clock_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

//#include "clock_diag.h"
#include "clock.h"
#include "clock_custom_diag.h"
#include "convert.h"
#include "ctype.h"
#include "data_utils.h"
#include "log.h"
#include "str_utils.h"
#include "timer_utils.h"

bool clock_stm_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(res) {
        res = true;
        uint32_t sys_clk = HAL_RCC_GetSysClockFreq();
        uint32_t phclk = HAL_RCC_GetHCLKFreq();
        uint32_t pclk1 = HAL_RCC_GetPCLK1Freq();
        uint32_t pclk2 = HAL_RCC_GetPCLK2Freq();
        LOG_INFO(SYS, "SysClk %u Hz", sys_clk);
        LOG_INFO(SYS, "HClock %u Hz", phclk);
        LOG_INFO(SYS, "P1Clock %u Hz", pclk1);
        LOG_INFO(SYS, "P2Clock %u Hz", pclk2);
        uint32_t instrictions = clock_int_per_us(100);
        LOG_INFO(SYS, "InstrPerUs 100Us %u 1Us-%u", instrictions, instrictions / 100);
        instrictions = clock_int_per_ms(100);
        LOG_INFO(SYS, "InstrPerMs %u", instrictions / 100);
#ifdef HAS_CLOCK_DIAG
        res = periph_clock_diag(keyWord1, keyWord2);
#endif
    } else {
        LOG_ERROR(SYS, "Usage: clsd keyWord");
    }
    return res;
}
