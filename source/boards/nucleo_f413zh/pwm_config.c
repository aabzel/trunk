#include "pwm_config.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif /*HAS_PWM*/

#include "data_utils.h"


static  bool PwmIsrHandler(void){
    bool res = false ;
    return res;
}


const PwmConfig_t PwmConfig[] = {
     {.channel=1, .num=4 , .period_us = 31, .duty = 33, .phase_us = 0,    .ComparatorHandler=PwmIsrHandler,  .PulseDoneHandler=PwmIsrHandler, .name="RfTuner", .valid=true, .on=false,},
     {.channel=2, .num=4 , .period_us = 31, .duty = 50, .phase_us = 10,   .ComparatorHandler=PwmIsrHandler,  .PulseDoneHandler=PwmIsrHandler, .name="RfTuner", .valid=true, .on=false,},
     {.channel=3, .num=4 , .period_us = 31, .duty = 51, .phase_us = 20,   .ComparatorHandler=PwmIsrHandler,  .PulseDoneHandler=PwmIsrHandler, .name="RfTuner", .valid=true, .on=true,},
     {.channel=4, .num=4 , .period_us = 31, .duty = 25, .phase_us = 20,   .ComparatorHandler=PwmIsrHandler,  .PulseDoneHandler=PwmIsrHandler, .name="RfTuner", .valid=true, .on=false,},
};

PwmHandle_t PwmInstance[]={
 {.channel=0, .valid=true,},
 {.channel=1, .valid=true,},
 {.channel=2, .valid=true,},
 {.channel=3, .valid=true,},
};

uint32_t pwm_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(PwmInstance);
    cnt2 = ARRAY_SIZE(PwmConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
