#ifndef SCR1_TIMER_CORE_H
#define SCR1_TIMER_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "scr1_timer_types.h"
#include "scr1_timer_diag.h"
#include "scr1_timer_config.h"

void Scr1TimerIntHandler(void);
bool scr1_timer_init(void);

/*setter*/
bool scr1_timer_clock_source_set(Scr1Timer_t* const Node,
                                 ClockSource_t clock_source);
bool scr1_timer_divider_set(Scr1Timer_t* const  Node, uint32_t divider);
bool scr1_timer_stop(void);
bool scr1_timer_tick_time_set(uint32_t scr1_timer_clock_hz, float period_s);
bool scr1_timer_counter_set(Scr1Timer_t* const  Node, const uint64_t value);
bool scr1_timer_start(void);
bool scr1_timer_disable(void);
bool scr1_timer_set_period_s(uint32_t scr1_timer_clock_hz, float period_s);
bool scr1_timer_set_load(uint32_t load);
bool scr1_timer_reset(void);

/*getter*/
bool scr1_timer_is_run(void);
float scr1_timer_tick_time_get(Scr1Timer_t* const  Node);
uint64_t scr1_timer_counter_get(const Scr1Timer_t* const  Node);
float scr1_timer_get_period(uint32_t scr1_timer_clock_hz);
uint32_t scr1_timer_get_ms(void);
float scr1_timer_get_s(void);
uint64_t scr1_timer_get_us(void);

#ifdef __cplusplus
}
#endif

#endif // SCR1_TIMER_CORE_H
