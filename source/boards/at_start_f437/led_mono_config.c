#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
    {
        .num = 1,
        .period_ms = 500,
        .phase_ms = 500,
        .duty = 10,
        .pad = {.port = PORT_D, .pin = 15},
        .name = "Green",
        .mode = LED_MODE_PWM,
        .active = GPIO_LVL_LOW,
        .valid = true,
    },
    {
        .num = 2,
        .period_ms = 1000,
        .phase_ms = 0,
        .duty = 10,
        .pad = {.port = PORT_D, .pin = 13},
        .name = "Red",
        .mode = LED_MODE_OFF,
        .active = GPIO_LVL_LOW,
        .valid = true,
    },
#if 0
    {
        .num = 3,
        .period_ms = 1000,
        .phase_ms = 0,
        .duty = 10,
        .pad = {.port = PORT_D, .pin = 14},
        .name = "Yellow",
        .mode = LED_MODE_PWM,
        .active = GPIO_LVL_LOW,
        .valid = true,
    },
#endif
};

LedMonoHandle_t LedMonoInstance[] = {
    {
        .num = 1,
        .valid = true,
        .active = GPIO_LVL_LOW,
    },
    {
        .num = 2,
        .valid = true,
        .active = GPIO_LVL_LOW,
    },
#if 0
    {
        .num = 3,
        .valid = true,
        .active = GPIO_LVL_LOW,
    },
#endif
};

uint32_t led_mono_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LedMonoInstance);
    cnt2 = ARRAY_SIZE(LedMonoConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
