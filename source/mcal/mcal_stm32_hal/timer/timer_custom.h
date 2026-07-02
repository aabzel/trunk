#ifndef TIM_DRV_CUSTOM_H
#define TIM_DRV_CUSTOM_H

#include "std_includes.h"
#include "stm32fx_hal.h"
#include "timer_custom_types.h"
#include "timer_mcal.h"

//uint8_t IS_TIM_CCX_INSTANCE(TIM_TypeDef* TIMx, uint8_t channel);
int8_t TimInstance2Num(const TIM_TypeDef* const TIMERx);
bool timer_set_cc_val(uint8_t num, TimerOutChannel_t chaneel, uint32_t cc_value, bool int_on);
TIM_TypeDef* timer_get_ptr(uint8_t num);
uint32_t TimerChannelToHalChannel(uint8_t channel) ;
uint32_t timer_get_counter(uint8_t num, TimerOutChannel_t channel);
uint32_t timer_mcu_cnt_get(void);

#endif /* TIM_DRV_H  */
