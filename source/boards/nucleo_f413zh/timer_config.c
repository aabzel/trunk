#include "timer_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /*HAS_TIMER*/

#include "data_utils.h"

const TimerConfig_t TimerConfig[] = {
    {.num=TIMER_MS_TICK_NUM , .valid=true, .cnt_period_ns = 1000000, .period_ms = TIMER_MS_PERIOD_MS, .name="ms"},
    {.num=TIMER_RTC_NUM , .valid=true,  .cnt_period_ns = 1000000, .period_ms = 1000,                       .name="s"},
    {.num=TIMER_US_TICK_NUM , .valid=true,   .cnt_period_ns = 1000,    .period_ms = TIMER_US_PERIOD_MS,    .name="us"},
    {.num=TIMER_RF_TUNER ,  .valid=true,    .cnt_period_ns = 1000,    .period_ms =0, .period_us = 0,  .period_ns = 30517,       .name="RfTuner"},
    {.num=TIMER_STACK_NUM ,  .valid=true,    .cnt_period_ns = 1000,    .period_ms = 1,          .name="stack"},
};

TimerHandle_t TimerInstance[]={
 {.num=TIMER_MS_TICK_NUM, .valid=true, },
 {.num=TIMER_RTC_NUM, .valid=true, },
 {.num=TIMER_US_TICK_NUM, .valid=true, },
 {.num=TIMER_RF_TUNER, .valid=true, },
 {.num=TIMER_STACK_NUM, .valid=true, },
};

uint32_t timer_get_cnt(void){
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
