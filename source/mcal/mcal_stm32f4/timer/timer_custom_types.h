#ifndef TIM_STM32_DRV_H
#define TIM_STM32_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "stm32f4xx_hal.h"
#include "timer_types.h"
#include "clock_custom_const.h"
#include "gpio_custom_types.h"


#define PRESCALER_MAX 0xFFFF

#define TIMER_CUSTOM_VARIABLES \
    TIM_HandleTypeDef timer_h;

typedef struct  {
    uint8_t num;
    TIM_TypeDef* TIMx;
    ClockBus_t clock_bus;
} TimerInfo_t;

typedef struct {
    uint8_t timer_num; /**/
    TimerCapComChannel_t out_channel;
    // uint8_t num; /*Timer*/
    bool valid;
    Pad_t Pad;
} TimerChannelInfo_t;


#endif /* TIM_STM32_DRV_H  */
