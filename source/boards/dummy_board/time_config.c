#include "time_config.h"

#include "data_utils.h"



const TimeConfig_t TimeConfig[] = {
    {
        .num =TIME_SW_INC,
        .time_source = TIME_SRC_SW_INCR,
        .valid = true,
    },
    {
        .num = TIME_SW_SYSTICK,
        .time_source = TIME_SRC_SYSTICK,
        .valid = true,
    },
#ifdef HAS_TIMER
    {
        .num = TIME_SW_TIMER2,
        .time_source = TIME_SRC_TIMER2,
        .valid = true,
    },
#endif

};

TimeHandle_t TimeInstance[] = {
    {        .num = TIME_SW_INC,        .valid = true,    },
    {        .num = TIME_SW_SYSTICK,        .valid = true,    },
#ifdef HAS_TIMER
    {        .num = TIME_SW_TIMER2,        .valid = true,    },
#endif
};

uint32_t time_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(TimeInstance);
    cnt2 = ARRAY_SIZE(TimeConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
