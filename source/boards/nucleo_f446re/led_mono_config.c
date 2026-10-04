#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
       {
       .num = LED_GREEN_ID,
       .period_ms = 1000,
       .phase_ms = 0,
       .duty = 50,
       .pad = {.port=PORT_A, .pin=5},
       .name = "Green",
       .mode = LED_MCAL_MODE_PWM,
       .active = GPIO_LVL_LOW,
       .valid = true,},
};

LedMonoHandle_t LedMonoInstance[]={
     {.num=LED_GREEN_ID, .valid=true, .active=GPIO_LVL_LOW,},
};


COMPONENT_GET_CNT(LedMono, led_mono)



