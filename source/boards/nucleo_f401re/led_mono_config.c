#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#include "back_count_config.h"
#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
    {
       .back_count_num = BACK_COUNT_WIFI_AP,
       .num = LED_GREEN_ID,
       .duty = 1,
       .group = 1,
       .led_phy = LED_PHY_GPIO,
       .period_ms = 5000,
       .phase_ms = 0,
       .pad = {.port = PORT_A, .pin = 5,}, /* TIM2_CH1 */
       .name = "Green",
       .mode = LED_MCAL_MODE_PWM,
       .active = GPIO_LVL_HI,
       .valid = true,
    },
};

LedMonoHandle_t LedMonoInstance[] = {
     {
         .num = LED_GREEN_ID, 
         .valid = true, 
         .active = GPIO_LVL_HI,
     },
};

COMPONENT_GET_CNT(LedMono, led_mono)
