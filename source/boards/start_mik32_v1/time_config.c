#include "time_config.h"

#include "data_utils.h"

const TimeConfig_t TimeConfig[] = {
    {.num = TIME_NUM_RISC_V_TIMER, .time_source = TIME_SRC_RISC_V, .valid = true,},
    {.num = TIME_NUM_SCR1_TIMER, .time_source = TIME_SCR1_TIMER, .valid = true,},
    {.num = TIME_NUM_SW_INCR, .time_source = TIME_SRC_SW_INCR, .valid = true,},
};

TimeHandle_t TimeInstance[] = {
    {.num = TIME_NUM_RISC_V_TIMER, .valid = true,},
    {.num = TIME_NUM_SCR1_TIMER, .valid = true,},
    {.num = TIME_NUM_SW_INCR, .valid = true,},
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

bool time_fix(void) {
    bool res = true;
    uint32_t i = 0 ;
    for(i=0;i<3;i++) {
        TimeInstance[i].num = TimeConfig[i].num;
        TimeInstance[i].time_source = TimeConfig[i].time_source;
        TimeInstance[i].valid = true;
    }
    return res;
}


