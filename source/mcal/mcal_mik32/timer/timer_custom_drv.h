#ifndef TIM_DRV_CUSTOM_H
#define TIM_DRV_CUSTOM_H

#include <stdbool.h>
#include <stdint.h>

#include "mik32_hal.h"
#include "timer_custom_types.h"
#include "timer_mcal.h"

TIM_TypeDef* timer_get_ptr(uint8_t num);
//bool timer_get_auto_reload(uint8_t num);
bool timer_set_cc_val(uint8_t num, TimerCapComChannel_t chaneel, uint32_t cc_value, bool int_on);
int8_t TimInstance2Num(TIM_TypeDef* Instance);
//uint32_t timer_get_cc_val(uint8_t num, TimerCapComChannel_t chaneel);
uint32_t timer_get_counter(uint8_t num, TimerCapComChannel_t channel);

#endif /* TIM_DRV_H  */
