#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#ifndef HAS_LED_MONO
#error "Add +HAS_LED_MONO"
#endif /* HAS_LED_MONO*/

#include "data_utils.h"
#include "gpio_stm_const.h"

const LedMonoConfig_t LedMonoConfig[LED_CNT] = {
       {.num=LED_YELLOW_ID, .period_ms=1000, .phase_ms=0, .duty=60, .pad.port=PORT_C, .pad.pin=13,  .name="Yellow",  .mode=LED_MODE_OFF, .active=GPIO_LVL_HI, .valid=true,},
       {.num=LED_RED_ID,    .period_ms=1000, .phase_ms=0, .duty=60, .pad.port=PORT_C, .pad.pin=12,  .name="Red",     .mode=LED_MODE_PWM, .active=GPIO_LVL_HI, .valid=true,},
};

LedHandle_t LedMonoInstance[LED_CNT]={
     {.num=LED_RED_ID,    .valid=true,},
     {.num=LED_YELLOW_ID, .valid=true,},
};

uint32_t led_mono_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LedMonoInstance); 
    cnt2 = ARRAY_SIZE(LedMonoConfig); 
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
