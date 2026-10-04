#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#include "data_utils.h"
#include "gpio_custom_const.h"
#include "led_general_const.h"

#ifdef HAS_PWM
#include "pwm_config.h"
#endif

#define LED_PWM_DUTY 7.0

const LedMonoConfig_t SECTION_CFG_DATA LedMonoConfig[] = {
       { .num = LED_STATUS_LED,
         .group = 1,
         .led_phy = LED_PHY_GPIO,
#ifdef HAS_PWM
         .pwm_num = 5, .pwm_frequency_hz = 200, .pwm_duty_off = 0.0, .pwm_duty_on = 6.0,
#endif
         .on_time_ms = 10,
         .pad = {.port = PORT_I, .pin = 1,},
         .active = GPIO_LVL_HI,
         .color = COLOR_GREEN,
         .mode = LED_MCAL_MODE_PWM,
         .duty = 10.0f,
         .period_ms = 1000,
         .phase_ms = 0,
         .valid = true,
#ifdef HAS_LOG
         .name = "ARD_D13",
#endif
       },

       { .num = LED_ERROR_LED,
         .group = 1,
         .led_phy = LED_PHY_GPIO,
         .on_time_ms = 10,
         .phase_ms = 500,
         .pad = {.port = PORT_J, .pin = 12,},
         .active = GPIO_LVL_HI,
         .color = COLOR_GREEN,
         .mode = LED_MCAL_MODE_PWM,
         .duty = 10.0f,
         .period_ms = 1000,
         .valid = true,
#ifdef HAS_PWM
         .pwm_num = 5,
         .pwm_frequency_hz = 200,
         .pwm_duty_off = 0.0,
         .pwm_duty_on = 6.0,
#endif
#ifdef HAS_LOG
         .name = "OTG_FS_VBUS",
#endif
       },

};

LedMonoHandle_t LedMonoInstance[] = {
     {.num = LED_STATUS_LED, .valid = true, .active = GPIO_LVL_HI,},
     {.num = LED_ERROR_LED, .valid = true, .active = GPIO_LVL_HI,},
};


COMPONENT_GET_CNT(LedMono, led_mono)



