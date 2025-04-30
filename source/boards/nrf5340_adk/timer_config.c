#include "timer_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /*HAS_TIMER*/

#include "data_utils.h"

const TimerConfig_t TimerConfig[] = {
    {.num=0, .bitness=32, .cnt_period_us = 1,      .on_off=true,   .period_us = 1000000,  .valid=true, .name="s",    .compare[0]=0xFF,.compare[1]=0xFFF,.compare[2]=0xFFFF,.compare[3]=0xFFFFF,},
    {.num=1, .bitness=32, .cnt_period_us = 1,      .on_off=true,   .period_us = 1000,     .valid=true, .name="ms",   .compare[0]=0xFF,.compare[1]=0xFFF,.compare[2]=0xFFFF,.compare[3]=0xFFFFF,},
    {.num=2, .bitness=32, .cnt_period_us = 1,      .on_off=true,   .period_us = 10000000,   .valid=true, .name="us",   .compare[0]=0xFF,.compare[1]=0xFFF,.compare[2]=0xFFFF,.compare[3]=0xFFFFF,},
};

TimerHandle_t TimerInstance[]={
 {.num=0, .valid=true,},
 {.num=1, .valid=true,},
 {.num=2, .valid=true,},
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
