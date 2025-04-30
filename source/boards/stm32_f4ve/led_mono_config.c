#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
       { .num=1, .period_ms=5000, .phase_ms = 0, .duty = 10, .pad = {.port=PORT_A, .pin=6}, .name = "D2/RED", .mode = LED_MODE_PWM, .active = GPIO_LVL_LOW, .valid=true,},
       { .num=2, .period_ms=5000, .phase_ms = 0, .duty = 10, .pad = {.port=PORT_A, .pin=7}, .name = "D3/Green", .mode = LED_MODE_PWM, .active = GPIO_LVL_LOW, .valid=true,},
};

LedMonoHandle_t LedMonoInstance[]={
     {.num=1, .valid=true, .active=GPIO_LVL_LOW,},
     {.num=2, .valid=true, .active=GPIO_LVL_LOW,},
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
