#ifndef LED_GENERAL_DRIVER_H
#define LED_GENERAL_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_LED
#error "+HAS_LED"
#endif

#ifndef HAS_PINS
#warning "+HAS_PINS"
#endif

#include "std_includes.h"
#include "gpio_const.h"
#include "led_config.h"
#include "led_dep.h"

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

#ifdef HAS_LED_RGB
#include "led_rgb_drv.h"
#endif

bool led_pwm(uint8_t led_num, float freq_hz, uint8_t duty);
bool led_blink(const uint8_t num, const uint32_t duration_ms);



#ifdef __cplusplus
}
#endif



#endif /* LED_GENERAL_DRIVER_H  */
