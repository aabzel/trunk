#ifndef TIMER_UTILS_H
#define TIMER_UTILS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t get_runtime_counter(void);
uint64_t get_time_tick64(void);

double timer_2_seconds(uint64_t timer_cnt, uint64_t base_clock_hz);
uint64_t runtime_2_us(uint64_t rtc);
uint64_t tick2us(uint64_t tick);
uint64_t us2tick(uint64_t ms64);
bool time_delay_us(uint32_t delay_us);
void delay_us_wd(uint32_t delay_in_us);
void delay_wd(uint32_t delay_in_ms);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_UTILS_H */
