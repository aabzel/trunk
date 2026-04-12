#ifndef LED_GENERAL_TYPES_H
#define LED_GENERAL_TYPES_H

#include "std_includes.h"
#include "led_general_const.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

#define LED_SW_PWM_VARIABLES                  \
    float duty;  /*for SW PWM*/               \
    uint32_t period_ms;                       \
    uint32_t phase_ms;

#define LED_BLITZ_VARIABLES                   \
    uint32_t on_time_ms;                      \
    uint32_t duration_ms;

#define LED_GENERAL_VARIABLES                 \
    LED_SW_PWM_VARIABLES                      \
    LED_BLITZ_VARIABLES                       \
    char* name;                               \
    uint32_t off_time_stamp;                  \
    uint32_t group;                           \
    LedMode_t mode;                           \
    uint8_t num;                              \
    bool valid;                               \
    GpioLogicLevel_t active;

#endif /* LED_GENERAL_TYPES_H  */
