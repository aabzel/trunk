#include "pwm_config.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif /*HAS_PWM*/

#include "data_utils.h"

const PwmConfig_t PwmConfig[] = {
     {.channel_id=0, .timer_num=4 , .period_us = 31, .duty = 33, .phase_us = 0,  .Channel=TIM_CHANNEL1, .name="RfTuner", .valid=true, .on=false,},
     {.channel_id=1, .timer_num=4 , .period_us = 31, .duty = 50, .phase_us = 10, .Channel=TIM_CHANNEL2, .name="RfTuner", .valid=true, .on=false,},
     {.channel_id=2, .timer_num=4 , .period_us = 31, .duty = 51, .phase_us = 20, .Channel=TIM_CHANNEL3, .name="RfTuner", .valid=true, .on=true,},
     {.channel_id=3, .timer_num=4 , .period_us = 31, .duty = 25, .phase_us = 20, .Channel=TIM_CHANNEL4, .name="RfTuner", .valid=true, .on=false,},
};

PwmHandle_t PwmItem[]={
 {.channel_id=0, .valid=true,},
 {.channel_id=1, .valid=true,},
 {.channel_id=2, .valid=true,},
 {.channel_id=3, .valid=true,},
};

uint32_t pwm_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(PwmItem); 
    cnt2 = ARRAY_SIZE(PwmConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
