#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif 

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[5] = {
   {
     .num = LED_ID_GPS, .group = 1,
     .pad = {.port = PORT_D, .pin = 14},
     .color = COLOR_BLUE,
     .name = "GPS",
     .phase_ms = 0, .duty = 33,
     .period_ms = 1000, .led_phy=LED_PHY_GPIO,
     .duration_ms = 10, .on_time_ms = 0,
     .mode = LED_MCAL_MODE_PWM,
     .active = GPIO_LVL_HI,
     .valid = true,
    },
    {
     .num = LED_ID_ERROR, .group = 1,
     .period_ms = 1000, .led_phy = LED_PHY_GPIO,
     .phase_ms = 0, .duty = 11,
     .duration_ms = 10, .on_time_ms = 0,
     .pad = {.port = PORT_D, .pin = 15},
     .name = "PWR",
     .mode = LED_MCAL_MODE_OFF,
     .color = COLOR_RED,
     .active = GPIO_LVL_HI,
     .valid = true,
     },
      {
       .num = LED_ID_CAN, .group = 1,
       .pad = {.port = PORT_G, .pin = 6},
       .period_ms = 1000, .led_phy=LED_PHY_GPIO,
       .phase_ms = 0, .duty = 11,
       .duration_ms = 10, .on_time_ms = 0,
       .name = "CAN",
       .mode = LED_MCAL_MODE_OFF,
       .color = COLOR_UNDEF,
       .active = GPIO_LVL_HI,
       .valid = true,
       },
     {
      .num = LED_ID_SIM, .group = 1,
      .period_ms = 1000, .led_phy = LED_PHY_GPIO,
      .phase_ms = 0, .duty = 50,
      .duration_ms = 10, .on_time_ms = 0,
      .pad = {.port = PORT_G, .pin = 10},
      .name = "SIMSwitch",
      .mode = LED_MCAL_MODE_PWM,
      .color = COLOR_UNDEF,
      .active = GPIO_LVL_HI,
      .valid = true,
      },

      {
       .num = LED_ID_GSM, .group = 1,
       .pad = {.port = PORT_D, .pin = 13,},
       .period_ms = 1000, .led_phy = LED_PHY_GPIO,
       .phase_ms = 0, .duty = 50,
       .duration_ms = 10, .on_time_ms = 0,
       .name = "GSM",
       .mode = LED_MCAL_MODE_PWM,
       .color = COLOR_GREEN,
       .active = GPIO_LVL_HI,
       .valid = true,
       },
};

LedMonoHandle_t LedMonoInstance[5] = {
     { .num = LED_ID_CAN, .valid = true, .active = GPIO_LVL_HI,},
     { .num = LED_ID_ERROR, .valid = true, .active = GPIO_LVL_HI,},
     { .num = LED_ID_GPS, .valid = true, .active = GPIO_LVL_HI,},
     { .num = LED_ID_SIM, .valid = true, .active = GPIO_LVL_HI,},
     { .num = LED_ID_GSM, .valid = true, .active = GPIO_LVL_HI,},
};

COMPONENT_GET_CNT(LedMono, led_mono)
