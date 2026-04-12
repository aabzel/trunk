#ifndef LED_MONO_TYPES_H
#define LED_MONO_TYPES_H

#include "std_includes.h"
#include "led_mono_const.h"
#include "led_general_const.h"
#include "led_general_types.h"
#include "gpio_types.h"

#ifdef HAS_PWM
/* Some boards produce very bright LEDs shine.
   Therefore, a PWM mode has been added to reduce brightness.
*/
#define LED_MONO_PWM_MODE_VARIABLES             \
    int16_t pwm_num;                            \
    float pwm_frequency_hz;                     \
    float pwm_duty_on;                          \
    float pwm_duty_off;

#else
#define LED_MONO_PWM_MODE_VARIABLES
#endif


#define LED_MONO_COMMON_VARIABLES     \
    LED_MONO_PWM_MODE_VARIABLES       \
    Pad_t pad;                        \
    LedPhy_t led_phy;                 \
    Color_t color;

typedef struct {
    LED_GENERAL_VARIABLES
    LED_MONO_COMMON_VARIABLES
} LedMonoConfig_t;

typedef struct {
    LED_GENERAL_VARIABLES
    LED_MONO_COMMON_VARIABLES
    GpioLogicLevel_t prev;
    bool init;
    LedMode_t prev_mode;
    uint32_t cur_time_ms;
    uint32_t spin;
} LedMonoHandle_t;

#endif /* LED_MONO_TYPES_H  */
