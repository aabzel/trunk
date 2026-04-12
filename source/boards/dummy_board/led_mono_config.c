#include "led_mono_config.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

#include "data_utils.h"
#ifdef HAS_GPIO_CUSTOM
#include "gpio_custom_const.h"
#endif

const LedMonoConfig_t LedMonoConfig[] = {
    {
        .num = LED_ID_GREEN_1,
        .period_ms = 1000,
        .group = 1,
        .phase_ms = 0,
        .duty = 50,

#ifdef HAS_GPIO_CUSTOM
        .pad = {.port = PORT_A, .pin = 0},
#endif
#ifdef HAS_LOG
        .name = "Green",
#endif

        .mode = LED_MODE_PWM,
        .active = GPIO_LVL_HI,
        .valid = true,
    },

    {
        .num = LED_ID_GREEN_2,
#ifdef HAS_LOG
        .name = "Green",
#endif
        .period_ms = 1000,
		.group = 2,
        .phase_ms = 0,
        .duty = 50,

#ifdef HAS_GPIO_CUSTOM
        .pad = {.port = PORT_A, .pin = 1},
#endif
        .mode = LED_MODE_PWM,
        .active = GPIO_LVL_HI,
        .valid = true,
    },

    {
        .num = LED_ID_GREEN_3,
#ifdef HAS_LOG
        .name = "Green",
#endif
        .period_ms = 1000,
		.group = 3,
        .phase_ms = 10,
        .duty = 50,

#ifdef HAS_GPIO_CUSTOM
        .pad = {.port = PORT_A, .pin = 2},
#endif
        .mode = LED_MODE_PWM,
        .active = GPIO_LVL_HI,
        .valid = true,
    },
    {
        .num = LED_ID_GREEN_4,
#ifdef HAS_LOG
        .name = "Green",
#endif
        .period_ms = 3000,
		.group = 1,
        .phase_ms = 10,
        .duty = 50,

#ifdef HAS_GPIO_CUSTOM
        .pad = {.port = PORT_A, .pin = 3},
#endif
        .mode = LED_MODE_OFF,
        .active = GPIO_LVL_HI,
        .valid = true,
    },
};

LedMonoHandle_t LedMonoInstance[] = {
    {
        .num = LED_ID_GREEN_1,
        .valid = true,
        .active = GPIO_LVL_HI,
    },
    {
        .num = LED_ID_GREEN_2,
        .valid = true,
        .active = GPIO_LVL_HI,
    },
    {
        .num = LED_ID_GREEN_3,
        .valid = true,
        .active = GPIO_LVL_HI,
    },
    {
        .num = LED_ID_GREEN_4,
        .valid = true,
        .active = GPIO_LVL_HI,
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
