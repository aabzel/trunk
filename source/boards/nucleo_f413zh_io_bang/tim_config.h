#ifndef TIM_CONFIG_GENERAL_H
#define TIM_CONFIG_GENERAL_H

#include <stdbool.h>
#include <stdint.h>

#include "tim_types.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /*HAS_TIMER*/

extern const TimerConfig_t TimerConfig[];
extern TimerHandle_t TimerInstance[];

uint32_t timer_get_cnt(void);

#endif /* TIM_CONFIG_GENERAL_H  */
