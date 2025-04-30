#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#include "data_utils.h"

const LedMonoConfig_t LedMonoConfig[ ] = {
   {.num=1, .period_ms=1000, .phase_ms=0,   .duty=50, .pad={.port=0, .pin=31,}, .name="Blue",  .mode=LED_MODE_PWM, .active=GPIO_LVL_HI, .valid=true,},
   //{.num=2, .period_ms=1000, .phase_ms=0,   .duty=50, .pad={.port=1, .pin=0,},  .name="Green", .mode=LED_MODE_PWM, .active=GPIO_LVL_HI, .valid=true,},
  // {.num=3, .period_ms=1000, .phase_ms=500, .duty=50, .pad={.port=1, .pin=1,},  .name="Green", .mode=LED_MODE_PWM, .active=GPIO_LVL_HI, .valid=true,},
#ifndef HAS_LED_RGB
   {.num=4, .period_ms=1000, .phase_ms=500, .duty=50, .pad={.port=0, .pin=7,},  .name="Red",   .mode=LED_MODE_OFF, .active=GPIO_LVL_HI, .valid=true,},
   {.num=5, .period_ms=1000, .phase_ms=500, .duty=50, .pad={.port=0, .pin=25,}, .name="Green", .mode=LED_MODE_OFF, .active=GPIO_LVL_HI, .valid=true,},
   {.num=6, .period_ms=1000, .phase_ms=500, .duty=50, .pad={.port=0, .pin=26,}, .name="Blue",  .mode=LED_MODE_OFF, .active=GPIO_LVL_HI, .valid=true,},

   {.num=7, .period_ms=1000, .phase_ms=500, .duty=50, .pad={.port=0, .pin=28,}, .name="Red",   .mode=LED_MODE_OFF, .active=GPIO_LVL_HI, .valid=true,},
   {.num=8, .period_ms=1000, .phase_ms=500, .duty=50, .pad={.port=0, .pin=29,}, .name="Green", .mode=LED_MODE_OFF, .active=GPIO_LVL_HI, .valid=true,},
   {.num=9, .period_ms=1000, .phase_ms=500, .duty=50, .pad={.port=0, .pin=30,}, .name="Blue",  .mode=LED_MODE_OFF, .active=GPIO_LVL_HI, .valid=true,},
#endif /*HAS_LED_RGB*/
};

LedHandle_t LedMonoInstance[ ]={
 {.num=1, .valid=true,},
// {.num=2, .valid=true,},
 //{.num=3, .valid=true,},
#ifndef HAS_LED_RGB
 {.num=4, .valid=true,},
 {.num=5, .valid=true,},
 {.num=6, .valid=true,},
 {.num=7, .valid=true,},
 {.num=8, .valid=true,},
 {.num=9, .valid=true,},
#endif /*HAS_LED_RGB*/
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
