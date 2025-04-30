#ifndef PWM_STM32_TYPES_H
#define PWM_STM32_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "pwm_stm32_const.h"

#ifdef USE_HAL_DRIVER
#include "at32f435_437.h"
#endif

typedef struct{
    TimChannel_t channel;
    uint32_t code;
}Channal2Code_t ;

#endif /* PWM_STM32_TYPES_H  */
