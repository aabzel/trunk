#include "led_drv.h"

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_LED
#error "Add HAS_LED"
#endif /*HAS_LED*/

bool led_pwm(uint8_t led_num, double freq_hz, uint8_t duty) {
    bool res = true;
#ifdef HAS_LED_MONO
    res = led_mono_pwm(led_num, freq_hz, duty);
#endif

#ifdef HAS_LED_RGB
    res = led_rgb_pwm(led_num, freq_hz, duty);
#endif
    return res;
}

#ifdef HAS_RTOS
void led_thread(void* arg1, void* arg2, void* arg3) {
    for(;;) {
#ifdef HAS_LED_MONO
        led_mono_proc();
#endif

#ifdef HAS_ZEPHYR_RTOS
        k_msleep(10);
#endif
    }
}
#endif
