#ifndef TIM_CONFIG_GENERAL_H
#define TIM_CONFIG_GENERAL_H

#include "std_includes.h"
#include "timer_types.h"

typedef enum {
    TIMER_NUM_RTC = 1,
    TIMER_NUM_US = 2,
    TIMER_NUM_STACK = 3,
    TIMER_NUM_MS = 5,
} TimerLegalNums_t;

extern const TimerConfig_t TimerConfig[];
extern TimerHandle_t TimerInstance[];

uint32_t timer_get_cnt(void);

#endif /* TIM_CONFIG_GENERAL_H  */
