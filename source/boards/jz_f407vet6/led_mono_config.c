#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif 

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
#if 0
   {
     .num = 1, .group = 1,
     .period_ms = 1000, .led_phy=LED_PHY_GPIO,
     .phase_ms = 0, .duty = 10,
     .duration_ms = 10, .on_time_ms = 0,
     .pad = {.port = PORT_E, .pin = 13},
     .name = "BPSKdata,LED1",
     .mode = LED_MCAL_MODE_PWM,
     .color = COLOR_RED,
     .active = GPIO_LVL_LOW,
     .valid = true,
    },
#endif
    {
     .num = LED_ID_HEARTBEAT, .group = 1,
     .period_ms = 1000, .led_phy=LED_PHY_GPIO,
     .phase_ms = 500, .duty = 50,
     .duration_ms = 10, .on_time_ms = 0,
     .pad = {.port = PORT_E, .pin = 15},
     .name = "HartBeat_LED3",
     .mode = LED_MCAL_MODE_PWM,
     .color = COLOR_RED,
     .active = GPIO_LVL_LOW,
     .valid = true,
    },
    {
     .num = LED_ID_ERROR, .group = 1,
     .period_ms = 1000, .led_phy=LED_PHY_GPIO,
     .phase_ms = 0, .duty = 20,
     .duration_ms = 10, .on_time_ms = 0,
     .pad = {.port = PORT_E, .pin = 14},
     .name = "Error_LED2",
     .mode = LED_MCAL_MODE_OFF,
     .color = COLOR_RED,
     .active = GPIO_LVL_LOW,
     .valid = true,
     },
};

LedMonoHandle_t LedMonoInstance[] = {
  //   { .num = 1, .valid = true, .active = GPIO_LVL_LOW,},
     { .num = LED_ID_HEARTBEAT, .valid = true, .active = GPIO_LVL_LOW,},
     { .num = LED_ID_ERROR, .valid = true, .active = GPIO_LVL_LOW,},
};


COMPONENT_GET_CNT(LedMono, led_mono)



