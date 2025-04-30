#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedMonoConfig_t LedMonoConfig[] = {
    {
        .num = LED_BLUE_ID,
        .active = GPIO_LVL_HI,
        .period_ms = 1000,
        .phase_ms = 0,
        .duty = 50,
        .pad = {.port = PORT_B, .pin = 7},
        .name = "Blue",
        .mode = LED_MODE_PWM,
        .valid = true,
    },
    {
        .num = LED_RED_ID,
        .active = GPIO_LVL_HI,
        .period_ms = 300,
        .phase_ms = 0,
        .duty = 40,
        .pad = {.port = PORT_B, .pin = 14},
        .name = "Red",
        .mode = LED_MODE_OFF,
        .valid = true,
    },

};

LedHandle_t LedMonoInstance[] = {
    {
        .num = LED_BLUE_ID,
        .valid = true,
    },
    {
        .num = LED_RED_ID,
        .valid = true,
    },
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
