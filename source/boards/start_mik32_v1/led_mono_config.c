#include "led_mono_config.h"

#include "data_utils.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_const.h"
#endif

const LedMonoConfig_t LedMonoConfig[2] = {
   {
        .num = LED_ID_HEARTBEAT,
#ifdef HAS_TIME
        .period_ms = 1000,
#else
        .period_ms = 4000,
#endif
        .phase_ms = 0,
        .duty = 50,
        .pad = {.port = 0, .pin = 3},
#ifdef HAS_LOG
        .name = "Green",
#endif
        .mode = LED_MODE_PWM,
        .active = GPIO_LVL_HI,
        .valid = true,
    },
    {
        .num = LED_ID_ERROR,
        .valid = true,
#ifdef HAS_TIME
        .period_ms = 500,
#else
        .period_ms = 40000,
#endif
        .phase_ms = 1,
        .duty = 50,
        .pad = {.port = 1, .pin = 3},
#ifdef HAS_LOG
        .name = "Green",
#endif
        .mode = LED_MODE_OFF,
        .active = GPIO_LVL_HI,
    },
};

LedMonoHandle_t LedMonoInstance[2] = {
     {.num = LED_ID_HEARTBEAT, .valid = true, .active = GPIO_LVL_LOW,},
     {.num = LED_ID_ERROR, .valid = true, .active = GPIO_LVL_LOW,},
};



bool led_mono_fix(void) {
    bool res = true;
    LedMonoInstance[0].num = LED_ID_HEARTBEAT;
    LedMonoInstance[0].valid = true;

    LedMonoInstance[1].num = LED_ID_ERROR;
    LedMonoInstance[1].valid = true;
    return res;
}

uint32_t led_mono_get_cnt(void){
    //led_mono_fix() ; // cause hang-up in optimization Os
    return 2;
}
