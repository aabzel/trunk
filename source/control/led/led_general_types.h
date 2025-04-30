#ifndef LED_GENERAL_TYPES_H
#define LED_GENERAL_TYPES_H

#include "std_includes.h"
#include "led_general_const.h"

#ifdef HAS_GPIO
#include "gpio_types.h"
#endif

#define LED_GENERAL_VARIABLES   \
    uint32_t phase_ms;          \
    uint32_t on_time_ms;        \
    uint32_t period_ms;         \
    uint32_t duration_ms;       \
    uint8_t num;                \
    bool valid;                 \
    LedMode_t mode;             \
    float duty;                 \
    GpioLogicLevel_t active;

#endif /* LED_GENERAL_TYPES_H  */
