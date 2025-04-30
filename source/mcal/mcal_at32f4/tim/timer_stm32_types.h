#ifndef TIM_STM32_DRV_H
#define TIM_STM32_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "at32f435_437.h"
#include "timer_types.h"
#include "clock_custom_const.h"

#define PRESCALER_MAX 0xFFFF

typedef struct  {
    uint8_t num;
    TIM_TypeDef* instance;
    //uint32_t clock_hz;
    ClockBus_t clock_bus;
} TimIntance_t;

#endif /* TIM_STM32_DRV_H  */
