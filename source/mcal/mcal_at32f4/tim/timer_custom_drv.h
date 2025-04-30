#ifndef TIM_DRV_CUSTOM_H
#define TIM_DRV_CUSTOM_H

#include <stdbool.h>
#include <stdint.h>

#include "at32f435_437.h"
#include "timer_stm32_types.h"
#include "timer_drv.h"
#include "timer_bsp.h"

TIM_TypeDef* timer_get_ptr(uint8_t num);
bool timer_get_auto_reload(uint8_t timer_num);
bool timer_set_cc_val(uint8_t timer_num, CapComChannel_t chaneel, uint32_t cc_value, bool int_on);
int8_t TimInstance2Num(TIM_TypeDef* Instance);
uint32_t timer_get_cc_val(uint8_t timer_num, CapComChannel_t chaneel);
uint32_t timer_get_counter(uint8_t timer_num, CapComChannel_t channel);

#endif /* TIM_DRV_H  */
