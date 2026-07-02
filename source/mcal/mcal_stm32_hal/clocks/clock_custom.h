#ifndef CLOCKS_CUSTOM_H
#define CLOCKS_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "clock_config.h"
#include "sys_config.h"

#define CLOCK_FOR_US (SYS_FREQ / 1000000U)

#define COUNTER_FREQ (SYS_FREQ / 1000000U)

//#define HZ_2_KHZ(HZ) ((double)(HZ)/1000.0)
//#define HZ_2_MHZ(HZ) ((double)(HZ)/1000000.0)

#define US_TO_COUNTER(us) ((uint64_t)((uint64_t)(us) * (COUNTER_FREQ)))
#define MS_TO_COUNTER(ms) ((uint64_t)(((ms)*1000UL) * (COUNTER_FREQ)))
#define COUNTER_TO_US(counter) ((counter) / (COUNTER_FREQ))
#define COUNTER_TO_MS(counter) ((counter) / ((COUNTER_FREQ)*1000))

uint64_t getRunTimeCounterValue64(void);
uint32_t getRunTimeCounterValue32(void);
uint64_t pause_1ms(void);
uint64_t pause_1us(void);
bool delay_ms(uint32_t delay_in_ms);
void delay_us(uint32_t delay_in_us);

uint64_t sw_pause_ms(uint32_t delay_in_ms);
uint32_t clock_get_tick_ms(void);


#ifdef __cplusplus
}
#endif

#endif // CLOCKS_CUSTOM_H
