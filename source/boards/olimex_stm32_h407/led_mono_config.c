#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#include "data_utils.h"
#include "gpio_custom_const.h"
#include "control_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
   {
        .active = GPIO_LVL_LOW,
        .num = 1, .group = 1,
        .period_ms = 5000,
        .phase_ms = 0, .duty = 10,
        .duration_ms = 10, .on_time_ms = 0,
        .pad = {.port = PORT_C, .pin = 13},
        .name = "Green",
        .mode = LED_MCAL_MODE_PWM,
        .valid = true,
    },
};

LedMonoHandle_t LedMonoInstance[] = {
     { 
         .active = GPIO_LVL_LOW,
         .num = 1,
         .valid = true,
     },
};

COMPONENT_GET_CNT(LedMono, led_mono)
