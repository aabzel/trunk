#ifndef LED_TASKS_H
#define LED_TASKS_H

#ifdef HAS_LED_RGB_PROC
#include "led_rgb_drv.h"
#define	LED_RGB_TASK {.name="LED_RGB", .period_us=LED_RGB_POLL_PERIOD_US, .limiter.function=proc_led_rgbs,},
#else
#define	LED_RGB_TASK
#endif /**/

#ifdef HAS_LED_MONO_PROC
#include "led_mono_drv.h"

#ifdef HAS_LOG
#define LED_MONO_TASK_NAME .name = "LedMono",
#else
#define LED_MONO_TASK_NAME
#endif

#define	LED_MONO_TASK { .period_us = LED_MONO_POLL_PERIOD_US, .limiter.function = led_mono_proc, LED_MONO_TASK_NAME},
#else
#define	LED_MONO_TASK
#endif /*HAS_LED_MONO_PROC*/


#define LEDS_TASKS          \
    LED_MONO_TASK           \
    LED_RGB_TASK


#endif /* LED_TASKS_H */
