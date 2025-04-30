#ifndef TIM_CONFIG_GENERAL_H
#define TIM_CONFIG_GENERAL_H


#include "std_includes.h"
#include "timer_types.h"

#ifndef HAS_TIMER
#error "Add HAS_TIMER"
#endif /*HAS_TIMER*/

#define TIME_TIMER_NUM 2

#define TIMER_RTC_NUM 1
#define TIMER_US_TICK_NUM 2
#define TIMER_STACK_NUM 3
#define TIMER_MS_TICK_NUM 5
#define TIMER_US_PERIOD_MS 4000U
//#define TIMER_MS_PERIOD_MS 4000000U

extern const TimerConfig_t TimerConfig[];
extern TimerHandle_t TimerInstance[];

uint32_t timer_get_cnt(void);

#endif /* TIM_CONFIG_GENERAL_H  */
