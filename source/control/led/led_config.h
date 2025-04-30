
#ifndef LED_GENERAL_CONFIG_H
#define LED_GENERAL_CONFIG_H

#ifndef HAS_LED
#error "+HAS_LED"
#endif

#ifdef HAS_LED_MONO
#include "led_mono_config.h"
#endif

#ifdef HAS_LED_RGB
#include "led_rgb_config.h"
#endif

#endif /* LED_GENERAL_CONFIG_H  */
