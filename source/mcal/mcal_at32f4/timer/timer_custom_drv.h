#ifndef TIMER_CUSTOM_DRIVER_H
#define TIMER_CUSTOM_DRIVER_H

#include <stdbool.h>
#include <stdint.h>

#include "artery_at32f4xx.h"
#include "timer_custom_types.h"
#include "timer_mcal.h"
#include "mcal_types.h"

extern const Reg32_t TimerReg[];

tmr_type* timer_get_ptr(uint8_t num);
int8_t TimerInstance2Num(tmr_type* Instance);
uint32_t timer_reg_cnt(void);

#endif /* TIM_DRV_H  */
