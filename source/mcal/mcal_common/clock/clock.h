#ifndef CLOCK_MCAL_H
#define CLOCK_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "clock_config.h"
#include "clock_types.h"
#include "clock_utils.h"
#include "sys_config.h"
#ifdef HAS_CLOCK_DIAG
#include "clock_diag.h"
#endif
#ifdef HAS_CLOCK_CUSTOM
#include "clock_custom.h"
#endif

#define CLOCK_FOR_US (SYS_FREQ / 1000000U)

/*setters*/
bool clock_core_set_reboot(uint32_t core_freq_hz);
bool clock_audio_freq_set(uint32_t audio_freq_hz);
bool clock_core_freq_set(uint32_t core_freq_hz);
//bool clock_config_100mhz(void);
//uint64_t pause_1us(void);
//uint64_t pause_1ms(void);
uint64_t clock_sw_pause_ms(uint32_t delay_in_ms);

//uint64_t pause_1ms(void) ;
/*getters*/
uint32_t clock_freq_get(ClockBus_t bus);
uint32_t clock_audio_freq_get(void);
uint32_t clock_core_freq_get(void);

bool clock_calc_prescaler( uint32_t base_freq_hz,
                           uint32_t max_val,
                           uint32_t timeout_ms, ClockSetting_t* const Node);

uint32_t ClockSourcToHz(const ClockSource_t clock_source) ;

bool clock_init(void);
bool clock_control(ClockDomain_t domain, bool on_off);
bool clock_start_pause_init(void);
double clock_audio_calc( uint16_t freq_value);
double clock_calc_period_s(uint32_t clock_hz, uint32_t prescaler, uint32_t reload);
bool clock_config_100mhz(void) ;
//uint32_t clock_freq_get(nrf_clock_domain_t domain_nrf);
uint32_t calc_prescaler(int32_t bus_freq, int32_t bit_rate);
uint32_t clock_int_per_us(uint64_t delay_in_us);
uint32_t clock_int_per_ms(uint32_t delay_ms);
#ifdef __cplusplus
}
#endif

#endif // CLOCK_MCAL_H
