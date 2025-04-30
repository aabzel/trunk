#include "led_rgb_config.h"

#ifndef HAS_LED_RGB
#error "Add HAS_LED_RGB"
#endif /*HAS_LED_RGB*/

#include "data_utils.h"

const LedRgbConfig_t LedRgbConfig[] = {
       {.num=1,  .set_color=COLOR_GREEN, .Pads={.red={.port=0 , .pin=7 ,},  .green={.port=0, .pin=25,}, .blue={.port=0, .pin=26,},}, .period_ms=1000, .phase_ms=0, .duty=10, .name="RGB1",    .mode=LED_MODE_PWM, .active=GPIO_LVL_HI, .valid=true,},
       {.num=2,  .set_color=COLOR_GREEN, .Pads={.red={.port=0 , .pin=26,},  .green={.port=0, .pin=29,}, .blue={.port=0, .pin=30,},}, .period_ms=2000, .phase_ms=0, .duty=10, .name="RGB2",    .mode=LED_MODE_PWM, .active=GPIO_LVL_HI, .valid=true,},
};

LedRgbHandle_t LedRgbItem[]={
     {.num=1,   .valid=true,},
     {.num=2,   .valid=true,},
};

uint32_t led_rgb_get_cnt(void){
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LedRgbItem);
    cnt2 = ARRAY_SIZE(LedRgbConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
} 
