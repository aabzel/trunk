#ifndef TIMER_CUSTOM_TYPES_H
#define TIMER_CUSTOM_TYPES_H

#include "std_includes.h"
#include "artery_at32f4xx.h"
#include "timer_const.h"
#include "clock_const.h"
#include "gpio_types.h"
#include "clock_custom_const.h"

#define PRESCALER_MAX 0xFFFF

#define TIMER_CUSTOM_VARIABLES                    \
    tmr_type *TMRx;                               \
    tmr_output_config_type tmr_oc_init_structure;

typedef struct {
    uint8_t num;
    bool valid ;
    tmr_type* TMRx;
    ClockBus_t clock_bus;
    uint8_t resolution_bit;
    IRQn_Type irq_n;
    crm_periph_clock_type clock_type;
} TimerInfo_t;

typedef struct {
    uint8_t timer_num; /**/
    TimerCapComChannel_t out_channel;
    // uint8_t num; /*Timer*/
    bool valid;
    Pad_t Pad;
} TimerChannelInfo_t;

#endif /* TIMER_CUSTOM_TYPES_H  */
