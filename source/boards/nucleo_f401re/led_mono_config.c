#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
       {.num=LED_GREEN_ID,   
       .period_ms=1000,
       .phase_ms=0,
       .duty=50,
       .pad={.port=PORT_A, .pin=5},
       .name="Green",
       .mode=LED_MODE_PWM,
       .active=GPIO_LVL_LOW,
       .valid=true,},
};

LedHandle_t LedMonoInstance[]={
     {.num=LED_GREEN_ID, .valid=true, .active=GPIO_LVL_LOW,},
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
