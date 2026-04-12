#ifndef TIMER_MCAL_TYPES_H
#define TIMER_MCAL_TYPES_H


#include "std_includes.h"
#include "timer_const.h"
#include "gpio_types.h"

#ifdef HAS_TIMER_CUSTOM
#include "timer_custom_types.h"
#else
#define TIMER_CUSTOM_VARIABLES
#endif



#define TIMER_COMMON_VARIABLES     \
    uint8_t num;                   \
    float period_s;                \
    uint32_t cnt_period_ns;        \
    char* name;                    \
    TimerDir_t dir;                \
    bool interrupt_on;             \
    bool on_off;                   \
    bool valid;

typedef struct  {
    TIMER_COMMON_VARIABLES
    uint32_t compare[4];
} TimerConfig_t;

typedef struct {
    uint8_t timer_num;
    uint8_t out_channel;
    bool valid;
    Pad_t Pad;
} TimerChannelInfo_t;

#define TIMER_ISR_VARIABLES            \
    volatile bool isr_busy;            \
    volatile uint32_t comparator_cnt;  \
    volatile bool comparator_done;     \
    volatile uint32_t int_cnt;         \
    volatile bool int_done;            \

typedef struct {
    TIMER_COMMON_VARIABLES
    TIMER_CUSTOM_VARIABLES
    TIMER_ISR_VARIABLES
    uint32_t error_cnt;
    uint32_t ic_cap_cnt;
    uint32_t pulse_fin_cnt;
    uint32_t pulse_fin_half_cnt;
    uint32_t delay_elapse_cnt;
    uint32_t period_val;
    uint32_t poll_cnt; /*For illusion that TIM works*/
    bool init_done;
} TimerHandle_t;

#endif /* TIMER_MCAL_TYPES_H */
