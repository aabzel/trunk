#ifndef PWM_VENDOR_CUSTOM_TYPES_H
#define PWM_VENDOR_CUSTOM_TYPES_H

#include "pwm_custom_const.h"
#include "std_includes.h"
#include "stm32f4xx_hal.h"
#include "timer_const.h"

#define PWM_CUSTON_VARIABLES             \
    TIM_HandleTypeDef h_tim;             \
    TIM_OC_InitTypeDef ConfigOC;

typedef struct {
    TimerOutChannel_t channel;
    uint32_t stm32_ch_code;
} Channal2Code_t;

#endif /* PWM_VENDOR_CUSTOM_TYPES_H  */
