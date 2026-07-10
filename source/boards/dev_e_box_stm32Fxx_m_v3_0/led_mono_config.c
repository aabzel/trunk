#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
    {
       .active = GPIO_LVL_LOW,
       .num = 1,
       .group = 1,
       .led_phy = LED_PHY_GPIO,
       .phase_ms = 0,
       .duty = 50,
       .pad = {.port = PORT_A, .pin = 1. },
       .period_ms = 1000,
       .name = "Green/D2",
       .mode = LED_MCAL_MODE_PWM,
       .valid = true,
    },

};

LedMonoHandle_t LedMonoInstance[] = {
     {
         .num = 1, 
         .valid = true,
         .active = GPIO_LVL_LOW,
      },
};

COMPONENT_GET_CNT(LedMono, led_mono)
