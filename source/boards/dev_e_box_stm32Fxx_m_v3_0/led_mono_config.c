#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
       {
        .num = 1,
        .period_ms = 5000,
        .phase_ms = 0,
        .duty = 10,
        .pad = {.port = PORT_A, .pin = 1},
        .name = "Green",
        .mode = LED_MODE_PWM,
        .active = GPIO_LVL_LOW,
        .valid = true,
       },
};

LedMonoHandle_t LedMonoInstance[] = {
     {.num = 1, .valid = true, .active = GPIO_LVL_LOW,},
};

COMPONENT_GET_CNT(LedMono, led_mono)
