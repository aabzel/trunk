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


typedef bool (*TimerCallBack_t)(void);

typedef union {
    uint8_t byte;
    struct {
        uint8_t timer  : 5; /*0 1 2 ...31*/
        uint8_t channel : 3; /*0 1 2 3 4 .. 7 */
    };
}TimerChannel_t;


#define TIMER_SLAVE_VARIABLES \
    TimerSlaveMode_t slave_mode;   \
    uint32_t slave_trigger_prescaler;    \
    uint32_t slave_trigger_filter;       \
    TimerSlaveInTrigger_t slave_input_trigger;   \
    TimerSlaveTriggerPolarity_t slave_trigger_polarity;


#define TIMER_COMMON_CALLBACK_VARIABLES                        \
    TimerCallBack_t ComparatorHandler;                         \
    TimerCallBack_t PeriodDoneHandler;

#define TIMER_COMMON_VARIABLES              \
    TIMER_COMMON_CALLBACK_VARIABLES         \
    TIMER_SLAVE_VARIABLES                   \
    uint8_t num;                            \
    float period_s;                \
    char* name;                    \
    TimerDir_t dir;                \
    TimerRole_t role;              \
    TimerMasterOutTrigger_t master_out_trigger;              \
    uint32_t cnt_period_ns;              \
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
