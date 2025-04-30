#include "tim_config.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /*HAS_TIMER*/

#include "data_utils.h"

const TimerConfig_t TimerConfig[] = {
                             {.num=2 , .bitness=32, .cnt_period_us = 1,    .period_ms = 4194965000, .name="us"},
                             {.num=5 , .bitness=32, .cnt_period_us = 1000, .period_ms = 4194965000, .name="ms"},
                             {.num=1 , .bitness=16, .cnt_period_us = 1000, .period_ms = 1000,       .name="s"},
};

TimerHandle_t TimerInstance[]={
 {.num=1, },
 {.num=2, },
 {.num=5, },
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
