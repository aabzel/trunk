#ifndef CLOCK_CUSTOM_H
#define CLOCK_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <std_includes.h>

#include "clock_config.h"
#include "microcontroller_types.h" // not const

#define CLOCK_FOR_US (SYS_FREQ / 1000000U)
#define COUNTER_FREQ (SYS_FREQ / 1000000U)

//#define HZ_2_KHZ(HZ) ((double)(HZ)/1000.0)
//#define HZ_2_MHZ(HZ) ((double)(HZ)/1000000.0)

#define US_TO_COUNTER(us) ((uint64_t)((uint64_t)(us) * (COUNTER_FREQ)))
#define MS_TO_COUNTER(ms) ((uint64_t)(((ms)*1000UL) * (COUNTER_FREQ)))
#define COUNTER_TO_US(counter) ((counter) / (COUNTER_FREQ))
#define COUNTER_TO_MS(counter) ((counter) / ((COUNTER_FREQ)*1000))

/*getters*/
uint64_t getRunTimeCounterValue64(void);
uint64_t get_time_tick64(void);
uint32_t getRunTimeCounterValue32(void);
uint64_t get_runtime_counter(void);

/*setters*/
//bool clock_init(void);
//uint64_t pause_1ms(void);
//uint64_t pause_1us(void);
bool delay_ms(uint32_t delay_in_ms);
void delay_us(uint32_t delay_in_us);

#ifdef HAS_AT32F43X
crm_pll_fr_type ClockFrToArtery(uint32_t fr);
#endif
uint64_t tick2us(uint64_t tick);
uint64_t us2tick(uint64_t ms64);
uint64_t runtime_2_us(uint64_t rtc);

uint64_t sw_pause_ms(uint32_t delay_in_ms);
uint32_t clock_get_tick_ms(void);


#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_H
