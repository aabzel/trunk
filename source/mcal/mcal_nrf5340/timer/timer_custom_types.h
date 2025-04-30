#ifndef TIMER_CUSTOM_TYPES_H
#define TIMER_CUSTOM_TYPES_H

#include <stdint.h>

#include "timer_custom_const.h"
#include "nrfx_timer.h"

#define TIMER_CUSTOM_VARIABLES           \
    volatile uint32_t int_compare_cnt;   \
    volatile uint32_t int_com_cnt[10];   \
    nrfx_timer_config_t config;          \
    nrfx_timer_t timer_h;

typedef struct {
    uint8_t num;
    uint32_t clock_hz;
} TimerIntance_t;

typedef struct {
    uint32_t freq_hz;
    nrf_timer_frequency_t freq_code;
} TimerFreqInfo_t;

typedef struct  {
    bool valid;
    uint8_t num;
    nrfx_timer_event_handler_t  event_handler;
} TimerEventHandler_t;

typedef struct  {
    uint8_t num;
    bool valid;
    uint8_t instance_id;
    uint8_t cc_channel_count;
    nrfx_timer_event_handler_t  event_handler;
    NRF_TIMER_Type* p_reg;
} NrfTimerInfo_t;

#endif /* TIMER_CUSTOM_TYPES_H  */
