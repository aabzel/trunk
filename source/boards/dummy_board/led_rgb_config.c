#include "led_rgb_config.h"

#ifndef HAS_LED_RGB
#error "Add HAS_LED_RGB"
#endif /*HAS_LED_RGB*/

#include "data_utils.h"
#include "gpio_custom_const.h"

const LedRgbConfig_t LedRgbConfig[] = {
    {
        .num = 1,
        .active = GPIO_LVL_HI,
        .duty = 10.0,
        .mode = LED_MODE_PWM,
        .name = "Status",
        .period_ms = 3000,
        .phase_ms = 0,
        .valid = true,
        .set_color = COLOR_YELLOW,
        .Pads = {
                .red = {
                         .port = PORT_B,
                         .pin = 8,
                       },
                .green = {
                           .port = PORT_B,
                           .pin = 9,
                         },
                .blue = {
                          .port = PORT_B,
                          .pin = 10,
                        },
        },
    },
};

LedRgbHandle_t LedRgbInstance[] = {
        { .num = 1,
          .valid = true, },
};

uint32_t led_rgb_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(LedRgbInstance);
    cnt2 = ARRAY_SIZE(LedRgbConfig);
    if (cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
