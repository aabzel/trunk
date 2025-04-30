#include "timer_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /*HAS_TIMER*/

#include "data_utils.h"

const TimerConfig_t TimerConfig[] = {
       {.num=TIMER_RTC_NUM , .valid=true,  /*.bitness=16,*/ .cnt_period_ns = 1000000, .dir=CNT_DIR_UP, .interrupt_on=true,   .on_off=true, .period_ms = 1000,                       .name="s"},
       {.num=TIMER_US_TICK_NUM , .valid=true, /*.bitness=32,*/ .cnt_period_ns = 1000, .dir=CNT_DIR_UP, .interrupt_on=true,   .on_off=true,  .period_ms = TIMER_US_PERIOD_MS,    .name="us"},
       {.num=TIMER_STACK_NUM , .valid=true,   /*.bitness=16,*/ .cnt_period_ns = 1000, .dir=CNT_DIR_UP, .interrupt_on=true,   .on_off=true,  .period_ms = 1, .name="stack"},
       {.num=TIMER_MS_TICK_NUM , .valid=true, /*.bitness=32,*/ .cnt_period_ns = 1000, .dir=CNT_DIR_UP, .interrupt_on=true,  .on_off=true,  .period_ms = 1, .name="ms"},
};

TimerHandle_t TimerInstance[]={
 {.num=TIMER_RTC_NUM, .valid=true, },
 {.num=TIMER_US_TICK_NUM, .valid=true, },
 {.num=TIMER_MS_TICK_NUM, .valid=true, },
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
