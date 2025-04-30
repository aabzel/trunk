#include "pwm_config.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif /*HAS_PWM*/

#include "data_utils.h"

const PwmConfig_t PwmConfig[] = {
     {.num=0,  .frequency_hz = 13000000.0, .duty = 50, .phase_us = 0,  .name="PWM0", .valid=true, .on=true,  .pad1={.port=1, .pin=6,}, .pad2.byte=0xff, .pad3.byte=0xff, .pad4.byte=0xff,},
     {.num=1,  .frequency_hz = 10000000.0, .duty = 50, .phase_us = 10, .name="PWM1", .valid=true, .on=false, .pad1.byte=0xff, .pad2.byte=0xff, .pad3.byte=0xff, .pad4.byte=0xff,},
     {.num=2,  .frequency_hz = 20000000.0, .duty = 75, .phase_us = 20, .name="PWM2", .valid=true, .on=false, .pad1.byte=0xff, .pad2.byte=0xff, .pad3.byte=0xff, .pad4.byte=0xff,},
     {.num=3,  .frequency_hz = 13000000.0, .duty = 10, .phase_us = 20, .name="PWM3", .valid=true, .on=false, .pad1.byte=0xff, .pad2.byte=0xff, .pad3.byte=0xff, .pad4.byte=0xff,},
};


PwmHandle_t PwmItem[]={
 {.num=0, .valid=true,},
 {.num=1, .valid=true,},
 {.num=2, .valid=true,},
 {.num=3, .valid=true,},
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
