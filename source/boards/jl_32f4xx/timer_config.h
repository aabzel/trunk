#ifndef TIM_CONFIG_GENERAL_H
#define TIM_CONFIG_GENERAL_H

#include "std_includes.h"
#include "timer_types.h"

typedef enum {
    TIMER_NUM_T2_x = 1,
    TIMER_NUM_ADC1 = 2,
    TIMER_NUM_T2_4 = 3,
    TIMER_NUM_T3_x = 4,
    TIMER_NUM_MASTER5 = 5,
    TIMER_NUM_RTC = 6,
    TIMER_NUM_T3_1 = 8,
    //TIMER_NUM_OUT4_3 = 12,
} TimerLegalNums_t;

extern const TimerConfig_t TimerConfig[];
extern TimerHandle_t TimerInstance[];

uint32_t timer_get_cnt(void);

#endif /* TIM_CONFIG_GENERAL_H  */
