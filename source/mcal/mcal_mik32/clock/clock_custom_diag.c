#include "clock_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "clock_types.h"
#include "common_diag.h"
#include "mcal_types.h"
#include "array.h"
#include "log.h"
#include "log_utils.h"
#include "mik32_hal.h"
#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_STRING
#include "str_utils.h"
#endif


/* see Table 125 – CLOCK Controller Registers*/
static const Reg32_t ClockRegs[] = {
    {.num=1, .access = ACCESS_READ_WRITE, .name = "DIV_AHB", .offset=0x0, .valid=true, },
    {.num=2, .access = ACCESS_READ_WRITE, .name = "DIV_APB_M", .offset=0x4, .valid=true, },
    {.num=3, .access = ACCESS_READ_WRITE, .name = "DIV_APB_P", .offset=0x8, .valid=true, },
    {.num=4, .access = ACCESS_READ_WRITE, .name = "CLK_AHB_SET", .offset=0xC, .valid=true, },
    {.num=5, .access = ACCESS_READ_ONLY,  .name = "CLK_AHB_CLEAR", .offset=0x10, .valid=true, },
    {.num=7, .access = ACCESS_READ_WRITE, .name = "CLK_APB_M_SET", .offset=0x14, .valid=true, },
    {.num=6, .access = ACCESS_READ_WRITE, .name = "CLK_APB_M_CLEAR", .offset=0x18, .valid=true, },
    {.num=8, .access = ACCESS_READ_WRITE, .name = "CLK_APB_P_SET", .offset=0x1C, .valid=true, },
    {.num=8, .access = ACCESS_READ_WRITE, .name = "CLK_APB_P_CLEAR", .offset=0x20, .valid=true, },
    {.num=8, .access = ACCESS_READ_WRITE, .name = "AHB_MUX", .offset=0x24, .valid=true, },
    {.num=8, .access = ACCESS_READ_WRITE, .name = "WDT_CLK_MUX", .offset=0x28, .valid=true, },
    {.num=8, .access = ACCESS_READ_WRITE, .name = "CPU_RTC_CLK_MUX", .offset=0x2C, .valid=true, },
    {.num=8, .access = ACCESS_READ_WRITE, .name = "TIMER_CFG", .offset=0x30, .valid=true, },
    {.num=8, .access = ACCESS_READ_WRITE, .name = "FREQ_MASK", .offset=0x34, .valid=true, },
    {.num=8, .access = ACCESS_READ_WRITE, .name = "FREQ_STATUS", .offset=0x38, .valid=true, },
    {.num=8, .access = ACCESS_READ_WRITE, .name = "SLEEP_MODE", .offset=0x3C, .valid=true, },

};

bool clock_raw_reg(void) {
    bool res = false;
    uint32_t cnt  = ARRAY_SIZE(ClockRegs);
    res = debug_raw_reg_diag(CLOCK, PM_BASE_ADDRESS, ClockRegs, cnt);
    return res;
}

const char* Bus2Str(ClockBus_t bus_code) {
    char* name = "?";
    switch((uint8_t)bus_code) {
    case CLOCK_BUS_AHB1:
        name = "AHB1";
        break;
    case CLOCK_BUS_AHB2:
        name = "AHB2";
        break;
    case CLOCK_BUS_AHB3:
        name = "AHB3";
        break;
    case CLOCK_BUS_APB1:
        name = "APB1";
        break;
    case CLOCK_BUS_APB2:
        name = "APB2";
        break;
    }
    return name;
}
