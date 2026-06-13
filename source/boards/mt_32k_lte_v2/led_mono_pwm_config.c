#include "led_mono_pwm_config.h"
#ifndef HAS_LED
#error "Add HAS_LED"
#endif 

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoPwmConfig_t LedMonoPwmConfig[] = {
    {
        .pwm_num = 6,
        .num = 1,
        .color = COLOR_GREEN,
        .valid = true,
        .group = 1,
        .period_ms = 10000,
        .phase_ms = 0,
        .duty_on = 90.0,
        .duty_off = 10.0,
        .duty = 50.0,
        .duration_ms = 10,
        .name = "LED",
        .mode = LED_MODE_PWM,
        .active = GPIO_LVL_LOW,
        .Pad = {.port = PORT_C, .pin = 13},
    },
};

LedMonoPwmHandle_t LedMonoPwmInstance[] = {
    {
        .num = 1,
        .valid = true,
        .active = GPIO_LVL_LOW,
    },
};

uint32_t led_mono_pwm_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LedMonoPwmConfig);
    cnt2 = ARRAY_SIZE(LedMonoPwmInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
