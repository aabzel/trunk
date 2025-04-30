#ifndef PWM_TYPES_H
#define PWM_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "pwm_const.h"
#include "gpio_types.h"

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif

#include "pwm_custom_types.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif

#define PWM_COMMON_VARIABLES \
    uint32_t phase_us;       \
    double duty;             \
    double frequency_hz;     \
    Pad_t pad[4];            \
    uint8_t num;             \
    uint8_t channel_cnt;     \
    bool valid;              \
    PwmChannel_t Channel;    \
    bool on;

typedef struct {
    PWM_COMMON_VARIABLES
    //uint32_t period_us;
    //uint32_t phase_us;
    //uint8_t timer_num;
    char name[10];
} PwmConfig_t;

typedef struct {
	PWM_COMMON_VARIABLES

#ifdef USE_HAL_DRIVER
    TIM_HandleTypeDef h_tim;
    TIM_OC_InitTypeDef ConfigOC;
#endif /*USE_HAL_DRIVER*/

    PWM_CUSTON_VARIABLES

    uint32_t error_cnt;
    volatile uint32_t int_cnt;
    bool init_done;
} PwmHandle_t;

#endif /* PWM_TYPES_H */
