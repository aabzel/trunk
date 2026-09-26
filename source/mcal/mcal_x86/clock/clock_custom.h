#ifndef CLOCK_CUSTOM_H
#define CLOCK_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "clock_config.h"
#include "microcontroller_types.h" // not const

bool clock_x86_init(void);

/*getters*/
uint64_t getRunTimeCounterValue64(void);
uint64_t get_time_tick64(void);
uint64_t get_runtime_counter(void);
uint64_t pc_clock_get_us(void);
uint32_t pc_clock_get_ms(void);
uint32_t getRunTimeCounterValue32(void);
uint32_t HAL_GetTick(void);

/*setters*/
//bool clock_init(void);
//uint64_t pause_1ms(void);
//uint64_t pause_1us(void);
bool delay_ms(uint32_t delay_in_ms);
void delay_us(uint32_t delay_in_us);


const ClockInfo_t* ClockGetInfo(uint8_t num) ;
uint64_t tick2us(uint64_t tick);
uint64_t us2tick(uint64_t ms64);
uint64_t runtime_2_us(uint64_t rtc);

uint64_t sw_pause_ms(uint32_t delay_in_ms);
uint32_t clock_get_tick_ms(void);


#ifdef __cplusplus
}
#endif

#endif // CLOCK_CUSTOM_H
