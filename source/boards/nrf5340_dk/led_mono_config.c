#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#include "data_utils.h"

const LedMonoConfig_t LedMonoConfig[ ] = {
#ifdef	HAS_CORE_APP
   {.num=1, .period_ms=1000, .phase_ms=0, .duty=50, .pad={.port=0, .pin=28}, .name="Green", .active=GPIO_LVL_LOW, .mode=LED_MODE_PWM, .valid=true,},
   {.num=2, .period_ms=1000, .phase_ms=500, .duty=50, .pad={.port=0, .pin=29}, .name="Green", .active=GPIO_LVL_LOW, .mode=LED_MODE_OFF, .valid=true,},
   {.num=3, .period_ms=10000, .phase_ms=0, .duty=50, .pad={.port=0, .pin=30}, .name="Green", .active=GPIO_LVL_LOW, .mode=LED_MODE_OFF, .valid=true,},
   {.num=4, .period_ms=10000, .phase_ms=0, .duty=50, .pad={.port=0, .pin=31}, .name="Green", .active=GPIO_LVL_LOW, .mode=LED_MODE_OFF, .valid=true,},
   {.num=5, .period_ms=1000, .phase_ms=0, .duty=50, .pad={.port=0, .pin=2}, .name="Virt", .active=GPIO_LVL_LOW, .mode=LED_MODE_PWM, .valid=true,},
   {.num=6, .period_ms=1000, .phase_ms=0, .duty=50, .pad={.port=0, .pin=3}, .name="Virt", .active=GPIO_LVL_LOW, .mode=LED_MODE_PWM, .valid=true,},
#endif/*HAS_CORE_APP*/

#ifdef	HAS_CORE_NET
   {.num=3, .period_ms=1000, .phase_ms=0, .duty=50, .pad={.port=0, .pin=30}, .name="Green", .active=GPIO_LVL_LOW, .mode=LED_MODE_PWM, .valid=true,},
   {.num=4, .period_ms=10000, .phase_ms=0, .duty=40, .pad={.port=0, .pin=31}, .name="Green", .active=GPIO_LVL_LOW, .mode=LED_MODE_PWM, .valid=true,},
#endif /*HAS_CORE_NET*/
};

LedHandle_t LedMonoInstance[ ]={
#ifdef	HAS_CORE_APP
 {.num=1, .valid=true,},
 {.num=2, .valid=true,},
 {.num=3, .valid=true,},
 {.num=4, .valid=true,},
 {.num=5, .valid=true,},
 {.num=6, .valid=true,},
#endif/*HAS_CORE_APP*/

#ifdef	HAS_CORE_NET
 {.num=3, .valid=true,},
 {.num=4, .valid=true,},
#endif/*HAS_CORE_NET*/
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
