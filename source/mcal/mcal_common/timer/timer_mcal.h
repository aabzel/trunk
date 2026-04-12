#ifndef TIMER_GENERAL_MCAL_API_H
#define TIMER_GENERAL_MCAL_API_H

#include "std_includes.h"
#include "timer_config.h"
#include "timer_types.h"
#include "timer_isr.h"
#include "clock_const.h"
#ifdef HAS_TIMER_CUSTOM
#include "timer_custom.h"
#endif

#ifdef HAS_TIMER_DIAG
#include "timer_diag.h"
#endif

/*API*/
TimerHandle_t* TimerGetNode(uint8_t num);
float  TimerConfigToPeriodSec(const TimerConfig_t* const Config);
const TimerConfig_t* TimerGetConfig(uint8_t num);
TimerChannelInfo_t* TimerChannelGetNode(const uint8_t timer_num, const uint8_t channel);
#ifdef HAS_TIMER_CUSTOM
TimerInfo_t* TimerGetInfo(const uint8_t num) ;
#endif
bool timer_init_common(const TimerConfig_t * const Config, TimerHandle_t*const Node);
bool timer_mcal_init(void);
bool timer_init_one(uint8_t num);
bool timer_init_custom(void);
bool timer_wait_us(uint32_t pause_us);
bool TimerIsValidConfig(const TimerConfig_t* const Config);


/*Setters------------------------*/
bool timer_base_clock_ctrl(const uint8_t num,const  bool on_off);
bool timer_channel_ctrl(uint8_t num, TimerCapComChannel_t channel, bool on_off);
bool timer_compare_set(uint8_t num, TimerCapComChannel_t channel, uint32_t compare_value);
bool timer_counter_set(uint8_t num, uint32_t value);
bool timer_counter_set_percent_u(uint8_t num, uint8_t counter_percent);
bool timer_overflow_set(uint8_t num, uint32_t overflow);
bool timer_overflow_get(uint8_t num, uint32_t* const overflow);
bool timer_period_set_ll(TimerHandle_t* const Node, const uint32_t period);
bool timer_period_set(uint8_t num, uint32_t value);
bool timer_period_set_s(uint8_t num, float period_s);
bool timer_ctrl(uint8_t num, bool on_off);
bool timer_frequency_set(uint8_t num, float frequency_hz);

/*Getters-------------------------------------*/

ClockBus_t timer_clock_bus_name_get(const uint8_t num);
TimerDir_t timer_dir_get(uint8_t num);
uint32_t timer_counter_get_us(const uint8_t num);
uint8_t timer_bitness_get(uint8_t num);
uint32_t TimerGetCntFreq(uint32_t cnt_period_us);
const TimerChannelInfo_t* TimerChannelGetInfo(uint8_t num, TimerCapComChannel_t channel);
bool timer_out_channel_pad_get(uint8_t num, TimerCapComChannel_t channel, Pad_t* const Pad) ;
bool timer_channel_is_work(const uint8_t num, const TimerCapComChannel_t channel);
bool timer_get_status(uint8_t num);
bool timer_is_valid(uint8_t num);
bool timer_is_valid_channel( const uint8_t num, const uint8_t channel);
/*freq period*/
bool timer_frequency_get(uint8_t num, float * const frequency);

uint32_t timer_counter_to_us(uint8_t num, uint32_t  counter);
uint32_t timer_cc_val_get(const uint8_t num, TimerCapComChannel_t chaneel) ;
uint64_t timer_get_period_us(uint8_t num) ;
float timer_get_period_s(uint8_t num) ;
float timer_tick_get_s(uint8_t num);
int32_t timer_bus_clock_get(uint8_t num);
uint32_t timer_get_tick_us(uint8_t num);
uint32_t timer_prescaler_get(uint8_t num);
uint32_t timer_get_period(uint8_t num);
uint32_t timer_get_int_period_ms(uint8_t num);
uint32_t timer_get_tick_period_us(uint8_t num);
/*period*/
float timer_period_get_s(uint8_t num);
uint32_t timer_get_auto_reload(uint8_t num);
uint32_t timer_period_get(uint8_t num);
uint64_t timer_period_get_us(uint8_t num);
uint32_t timer_period_get_ms(uint8_t num);

/*counter*/
float timer_counter_get_s(uint8_t num) ;
uint32_t timer_counter_get(uint8_t num);

/*output comparator*/
float timer_get_s(uint8_t num);
bool timer_duty_get(uint8_t num,TimerCapComChannel_t channel, float* const duty);
uint32_t timer_ccc_val_get(uint8_t num, TimerCapComChannel_t channel);
uint32_t timer_cc_val_get(uint8_t num,const TimerCapComChannel_t channel);
/*up time*/
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
float timer_calc_real_period_s(uint32_t cpu_clock, uint32_t prescaler, uint32_t laod);
bool timer_calc_registers(float period_s,  uint32_t bus_clock,
                          uint32_t prescaler, uint32_t* out_load, uint32_t max_val);
uint32_t timer_calc_prescaler(uint32_t bus_clock_hz, uint32_t des_tick_per_ns, uint32_t max_prescaler);


#endif /* TIMER_GENERAL_MCAL_API_H  */
