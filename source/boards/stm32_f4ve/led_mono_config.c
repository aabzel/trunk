#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif 

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
       { .num = 1,
         .period_ms = 1000,
         .phase_ms = 0,
         .duty = 50,
         .pad = {.port = PORT_A, .pin = 6,},
         .name = "D1/LED 1",
         .color = COLOR_RED,
         .group = 1,
         .mode = LED_MCAL_MODE_PWM,
         .led_phy = LED_PHY_GPIO,
         .ctrl_mode = CONTROL_MODE_GPIO,
         .active = GPIO_LVL_LOW, .valid = true,},

       { .num = 2,
         .period_ms = 1000,
         .phase_ms = 500,
         .group = 1,
         .duty = 50,
         .pad = { .port = PORT_A, .pin = 7,},
         .name = "D3/LED 2",
         .mode = LED_MCAL_MODE_PWM,
         .color = COLOR_RED,
         .ctrl_mode = CONTROL_MODE_GPIO,
         .led_phy = LED_PHY_GPIO,
         .active = GPIO_LVL_LOW,
         .valid = true,},
};




LedMonoHandle_t LedMonoInstance[] = {
     {.num = 1, .valid = true, .active = GPIO_LVL_LOW,},
     {.num = 2, .valid = true, .active = GPIO_LVL_LOW,},
};


COMPONENT_GET_CNT(LedMono, led_mono)



