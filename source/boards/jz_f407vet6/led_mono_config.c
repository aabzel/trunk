#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif 

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
   {
    .num = 1, .group = 1,
    .period_ms = 1000, .led_phy=LED_PHY_GPIO,
    .phase_ms = 0, .duty = 10,
    .duration_ms = 10, .on_time_ms = 0,
    .pad = {.port = PORT_E, .pin = 13},
    .name = "Green",
    .mode = LED_MCAL_MODE_PWM,
    .active = GPIO_LVL_LOW,
    .valid = true,
    },
    {
     .num = 2, .group = 1,
     .period_ms = 1000, .led_phy=LED_PHY_GPIO,
     .phase_ms = 0, .duty = 10,
     .duration_ms = 10, .on_time_ms = 0,
     .pad = {.port = PORT_E, .pin = 14},
     .name = "Green",
     .mode = LED_MCAL_MODE_PWM,
     .active = GPIO_LVL_LOW,
     .valid = true,
     },
     {
      .num = 3, .group = 1,
      .period_ms = 1000, .led_phy=LED_PHY_GPIO,
      .phase_ms = 0, .duty = 10,
      .duration_ms = 10, .on_time_ms = 0,
      .pad = {.port = PORT_E, .pin = 15},
      .name = "Green",
      .mode = LED_MCAL_MODE_PWM,
      .active = GPIO_LVL_LOW,
      .valid = true,
      },
};

LedMonoHandle_t LedMonoInstance[] = {
     { .num = 1, .valid = true, .active = GPIO_LVL_LOW,},
     { .num = 2, .valid = true, .active = GPIO_LVL_LOW,},
     { .num = 3, .valid = true, .active = GPIO_LVL_LOW,},
};


COMPONENT_GET_CNT(LedMono, led_mono)



