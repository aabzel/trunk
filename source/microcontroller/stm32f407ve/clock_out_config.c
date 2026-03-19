#include "clock_out_config.h"

//#include "sys_config.h"
#include "data_utils.h"

const ClockOutConfig_t SECTION_CFG_DATA ClockOutConfig[] ={
    { .num = 1, .clock_bus = CLOCK_OUT_FOSC, .divider = 8, .valid = true, .name ="FOSC", },
    { .num = 2, .clock_bus = CLOCK_OUT_CORE, .divider = 8, .valid = true, .name ="Core", },
};

ClockOutHandle_t ClockOutInstance[] ={
    { .num = 1, .valid = true,   },
    { .num = 2, .valid = true,   },
};

uint32_t clock_out_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(ClockOutConfig);
    return cnt;

}
