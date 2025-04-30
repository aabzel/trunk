#include <boards/olimex_stm32_h407/timer_config.h>

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /*HAS_TIMER*/

#include "data_utils.h"

const TimerConfig_t TimerConfig[] = {
                             {.num=1,   .cnt_period_ns = 250000, .period_ms = 1000,    .name="s",  .valid=true,},
                             {.num=2 ,  .cnt_period_ns = 1000,   .period_ms = TIMER_US_PERIOD_MS,    .name="us", .valid=true,},
                             {.num=3 ,  .cnt_period_ns = 1000,   .period_ms = 1,    .name="1ms", .valid=true,},
                             {.num=4 ,  .cnt_period_ns = 500000, .period_ms = 1000, .name="c0.5msO1s", .valid=true,},
                             {.num=5 ,  .cnt_period_ns = 1000,   .period_ms = 1,    .name="1ms", .valid=true,},
};

TimerHandle_t TimerInstance[]={
    {.num=1, .valid=true,},
    {.num=2, .valid=true,},
    {.num=3, .valid=true,},
    {.num=4, .valid=true,},
    {.num=5, .valid=true,},
};

uint32_t timer_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(TimerInstance); 
    cnt2 = ARRAY_SIZE(TimerConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
