#ifndef LED_GENERAL_DRIVER_H
#define LED_GENERAL_DRIVER_H

#include "std_includes.h"

#ifndef HAS_LED
#error "+HAS_LED"
#endif

#ifndef HAS_PINS
#warning "+HAS_PINS"
#endif

#include "gpio_const.h"
#include "led_config.h"
#include "led_dep.h"

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

#ifdef HAS_LED_RGB
#include "led_rgb_drv.h"
#endif

#ifdef HAS_RTOS
void led_thread(void *arg1, void *arg2, void *arg3);
#endif

bool led_pwm(uint8_t led_num, float freq_hz, uint8_t duty);
GpioLogicLevel_t LedLogicLevel2Voltage(uint8_t val, GpioLogicLevel_t active);

#endif /* LED_GENERAL_DRIVER_H  */
