#include "time_config.h"


#include "data_utils.h"

const TimeConfig_t TimeConfig[] = {
    {.num=1,  .time_source = TIME_SRC_SYSTICK,  .valid=true,},
#ifdef HAS_TIMER5
    {.num=2 , .time_source = TIME_SRC_TIMER5,   .valid=true,},
#endif
};

TimeHandle_t TimeInstance[]={
    {.num=1, .valid=true,},
#ifdef HAS_TIMER5
    {.num=2, .valid=true,},
#endif
};

uint32_t time_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(TimeInstance);
    cnt2 = ARRAY_SIZE(TimeConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
