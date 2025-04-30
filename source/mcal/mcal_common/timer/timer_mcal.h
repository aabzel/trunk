#ifndef TIMER_GENERAL_MCAL_API_H
#define TIMER_GENERAL_MCAL_API_H

#include <stdbool.h>

#include "timer_config.h"
#include "timer_types.h"
#include "timer_isr.h"
#ifdef HAS_TIMER_DIAG
#include "timer_diag.h"
#endif

/*API*/
uint32_t timer_get_cc_val(uint8_t num, TimerCapComChannel_t chaneel);
double  TimerConfigToPeriodSec(const TimerConfig_t* const Config);
const TimerConfig_t* TimerGetConfig(uint8_t num);
TimerHandle_t* TimerGetNode(uint8_t num);
TimerInfo_t* TimerGetInfo(uint8_t num);
bool timer_init_common(const TimerConfig_t * const Config, TimerHandle_t*const Node);
bool timer_mcal_init(void);
bool timer_init_one(uint8_t num);
bool timer_wait_us(uint32_t pause_us);


/*Setters------------------------*/
bool timer_channel_ctrl(uint8_t num, TimerCapComChannel_t channel, bool on_off);
bool timer_compare_set(uint8_t num, TimerCapComChannel_t channel, uint32_t compare_value);
bool timer_counter_set( uint8_t num, uint32_t value);
bool timer_counter_set_percent_u(uint8_t num, uint8_t counter_percent);
bool timer_overflow_set( uint8_t num, uint32_t overflow);
bool timer_overflow_get( uint8_t num, uint32_t* const overflow);
bool timer_period_set( uint8_t num, uint32_t value);
bool timer_period_set_s( uint8_t num, double period_s);
bool timer_ctrl(uint8_t num, bool on_off);
bool timer_frequency_set(uint8_t num, double frequency_hz);

/*Getters-------------------------------------*/
TimerDir_t timer_dir_get(uint8_t num);
uint8_t timer_bitness_get(uint8_t num);
const TimerChannelInfo_t* TimerChannelGetInfo(uint8_t num, TimerCapComChannel_t channel);
bool timer_out_channel_pad_get(uint8_t num, TimerCapComChannel_t channel, Pad_t* const Pad) ;
bool timer_get_status(uint8_t num);
bool timer_is_valid(uint8_t num);
bool timer_init_custom(void);
uint64_t timer_get_period_us(uint8_t num);
/*freq period*/
bool timer_frequency_get(uint8_t num, double * const frequency);
uint32_t TimerGetCntFreq(uint32_t cnt_period_us);

double timer_get_period_s(uint8_t num) ;
double timer_tick_get_s(uint8_t num);
int32_t timer_bus_clock_get(uint8_t num);
uint32_t timer_get_tick_us(uint8_t num);
uint32_t timer_prescaler_get(uint8_t num);
uint32_t timer_get_int_period_ms(uint8_t num);
uint32_t timer_get_tick_period_us(uint8_t num);
/*period*/
double timer_period_get_s(uint8_t num);
uint32_t timer_get_auto_reload(uint8_t num);
uint32_t timer_period_get(uint8_t num);
uint64_t timer_period_get_us(uint8_t num);
uint32_t timer_period_get_ms(uint8_t num);

/*counter*/
double timer_counter_get_s(uint8_t num) ;
uint32_t timer_counter_get(uint8_t num);

/*output comparator*/
bool timer_duty_get(uint8_t num,TimerCapComChannel_t channel, double* const duty);
uint32_t timer_ccc_val_get(uint8_t num, TimerCapComChannel_t chaneel);
uint32_t timer_cc_val_get(uint8_t num, TimerCapComChannel_t channel);
/*up time*/
double timer_get_s(uint8_t num);
uint32_t timer_get_ms(uint8_t num);
uint32_t timer_get_uptime_ms(uint8_t num);
uint32_t timer_get_uptime_us(uint8_t num);
uint64_t timer_get_us(uint8_t num);
uint32_t timer_get_us32(uint8_t num);
uint8_t timer_get_bitness(uint8_t num);
//uint8_t timer_get_bitness(uint8_t num);
uint8_t timer_get_width(uint32_t timer_base);
TimerDir_t timer_get_dir(uint8_t num);

/*computing*/
double timer_calc_real_period_s(uint32_t cpu_clock, uint32_t prescaler, uint32_t laod);
bool timer_calc_registers(uint32_t period_ms, uint32_t period_us, uint32_t period_ns, uint32_t bus_clock,
                          uint32_t prescaler, uint32_t* out_load, uint32_t max_val);
uint32_t timer_calc_prescaler(uint32_t bus_clock_hz, uint32_t des_tick_per_ns, uint32_t max_prescaler);


#endif /* TIMER_GENERAL_MCAL_API_H  */
