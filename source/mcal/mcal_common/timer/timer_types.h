#ifndef TIMER_MCAL_TYPES_H
#define TIMER_MCAL_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "timer_const.h"
#include "timer_custom_types.h"

#define TIMER_COMMON_VARIABLES     \
    uint8_t num;                   \
    bool interrupt_on;             \
    TimerDir_t dir;                \
    bool valid;

typedef struct  {
    TIMER_COMMON_VARIABLES
    uint32_t period_ms;
    uint32_t period_us;
    uint32_t period_ns;
    uint32_t cnt_period_ns;
    uint32_t compare[4];
    bool on_off;
    char name[20];
} TimerConfig_t;


#define TIMER_ISR_VARIABLES       \
    volatile uint32_t comparator; \
    volatile uint32_t int_cnt;    \
    volatile uint32_t overflow;

typedef struct {
    TIMER_COMMON_VARIABLES
    TIMER_ISR_VARIABLES
    bool init_done;
    uint32_t error_cnt;
    uint32_t ic_cap_cnt;
    uint32_t pulse_fin_cnt;
    uint32_t pulse_fin_half_cnt;
    uint32_t delay_elapse_cnt;
    uint32_t period_val;
    uint32_t poll_cnt; /*For illusion that TIM works*/

    TIMER_CUSTOM_VARIABLES
} TimerHandle_t;

#endif /* TIMER_MCAL_TYPES_H */
