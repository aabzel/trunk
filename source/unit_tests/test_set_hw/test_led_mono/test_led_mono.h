#ifndef TEST_LED_MONO_H
#define TEST_LED_MONO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "sys_config.h"

#include "test_hw_dep_check.h"

#ifndef HAS_LED_MONO
#error "It is needed HAS_LED_MONO option for that component"
#endif

bool test_led_mono_one(uint8_t pad_num);
bool test_led_mono_set(void);
bool test_led_mono_types(void);
bool test_led_mono_pwm(void);
bool test_led_mono_const(void);
bool test_led_mono_blink(void) ;

#define TEST_SUIT_LED_MONO                      \
    {"LedMonoConst", test_led_mono_const},      \
    {"LedMonoTypes", test_led_mono_types},      \
    {"LedMonoSet", test_led_mono_set},          \
    {"LedMonoPwm", test_led_mono_pwm},          \
    {"LedMonoBlink", test_led_mono_blink},

#ifdef __cplusplus
}
#endif

#endif /* TEST_LED_MONO_H */
