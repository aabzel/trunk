#ifndef TEST_LED_RGB_H
#define TEST_LED_RGB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "sys_config.h"

#include "test_hw_dep_check.h"

#ifndef HAS_LED_RGB
#error "It is needed HAS_LED_RGB option for that component"
#endif

#define TRANSITION_PROCESS_TIMEOUT_MS 400

bool test_led_rgb_one(uint8_t led_num);
bool test_led_rgb_color_set(void);
bool test_led_rgb_types(void);
bool test_led_rgb_const(void);

#define TEST_SUIT_LED_RGB                                                                                                 \
    {"led_rgb_const", test_led_rgb_const}, {"led_rgb_color_set", test_led_rgb_color_set}, {"led_rgb_types", test_led_rgb_types},

#ifdef __cplusplus
}
#endif

#endif /* TEST_LED_RGB_H */
