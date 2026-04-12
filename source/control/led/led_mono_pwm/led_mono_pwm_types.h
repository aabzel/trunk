#ifndef LED_MONO_PWM_TYPES_H
#define LED_MONO_PWM_TYPES_H

#include "std_includes.h"
#include "led_mono_pwm_const.h"
#include "led_general_types.h"
#include "gpio_types.h"

#define LED_MONO_PWM_COMMON_VARIABLES                  \
    LED_GENERAL_VARIABLES                              \
    float duty_on;                                     \
    float duty_off;                                    \
    uint8_t pwm_num;                                   \
    char* name;                                        \
    Pad_t Pad;                                         \
    Color_t color;

typedef struct {
    LED_MONO_PWM_COMMON_VARIABLES
} LedMonoPwmConfig_t;

typedef struct {
    LED_MONO_PWM_COMMON_VARIABLES
    float prev_duty;
    bool init;
    LedMode_t prev_mode;
    uint32_t cur_time_ms;
    uint32_t spin;
} LedMonoPwmHandle_t;


#endif /* LED_MONO_PWM_TYPES_H */
