#ifndef LED_INIT_H
#define LED_INIT_H

#include "std_includes.h"

#ifndef HAS_CONTROL
#error "+HAS_CONTROL"
#endif

#ifndef HAS_LED
#error "+HAS_LED"
#endif



#ifdef HAS_LED_RGB_TEST
#include "led_rgb_drv.h"
#define  LED_RGB_TEST_INIT {.init_function=led_rgb_test, "LedRgbTest",},
#else
#define  LED_RGB_TEST_INIT
#endif

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"

#ifdef HAS_LOG
#define LED_MONO_INIT_NAME .name = "LedMono",
#else
#define LED_MONO_INIT_NAME
#endif

#define LED_MONO_INIT  {.init_function = led_mono_mcal_init, LED_MONO_INIT_NAME},
#else
#define LED_MONO_INIT
#endif /*HAS_LED_MONO*/

#ifdef HAS_LED_RGB
#include "led_rgb_drv.h"
#define LED_RGB_INIT  {.init_function=led_rgb_mcal_init,  .name= "LedRgb",},
#else
#define LED_RGB_INIT
#endif /*HAS_LED_RGB*/

// order matter
#define LED_INIT            \
    LED_MONO_INIT           \
    LED_RGB_INIT


#endif /* LED_INIT_H */
