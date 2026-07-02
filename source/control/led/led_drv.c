#include "led_drv.h"

#include "std_includes.h"

#ifndef HAS_LED
#error "Add HAS_LED"
#endif

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

bool led_pwm(uint8_t led_num, float freq_hz, uint8_t duty) {
    bool res = true;
#ifdef HAS_LED_MONO
    res = led_mono_sw_pwm(led_num, freq_hz, duty);
#endif

#ifdef HAS_LED_RGB
    res = led_rgb_pwm(led_num, freq_hz, duty);
#endif
    return res;
}

bool led_blink(const uint8_t num, const uint32_t duration_ms) {
    bool res = true;

#ifdef HAS_LED_RGB
    res = led_rgb_blink(num, duration_ms, COLOR_BLUE);
#endif

#ifdef HAS_LED_MONO
    res = led_mono_blink(num, duration_ms);
#endif
    return res;
}
