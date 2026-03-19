#ifndef CLOCK_MCAL_H
#define CLOCK_MCAL_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "clock_config.h"
#include "clock_types.h"
#include "clock_utils.h"

#ifdef HAS_CLOCK_DIAG
#include "clock_diag.h"
#endif

#ifdef HAS_CLOCK_CUSTOM
#include "clock_custom.h"
#endif

#define CLOCK_FOR_US (SYS_FREQ / 1000000U)

#define CLOCK_KHZ_TO_HZ(KHZ) ((MHZ)*1000)
#define CLOCK_MHZ_TO_HZ(MHZ) ((MHZ)*1000000)

/*API*/
bool clock_mcal_init(void);
bool clock_is_valid_config(const ClockConfig_t* const Config);

/*setters*/
bool clock_core_freq_set(const uint32_t core_freq_hz);
bool clock_core_mux_set(const ClockMux_t clock_mux);
bool clock_core_set_reboot(uint32_t core_freq_hz);
bool clock_config_default(void) ;
#ifdef HAS_AUDIO
bool clock_audio_freq_set(uint32_t audio_freq_hz);
#endif
uint64_t pause_1us(void);
uint64_t pause_1ms(void);
uint64_t clock_sw_pause_ms(uint32_t delay_in_ms);

/*getters*/
bool clock_core_mux_get(ClockMux_t* const clock_mux);
bool clock_frequency_get(const ClockBus_t clock_name, uint32_t* const frequency_hz);
uint32_t clock_freq_get(const ClockBus_t bus);
uint32_t clock_freq_to_flash_latency_2_7v_3_6v(const int32_t core_freq_hz );
uint32_t clock_audio_freq_get(void);
uint32_t clock_core_freq_get(void);

bool clock_calc_prescaler( uint32_t base_freq_hz,
                           uint32_t max_val,
                           uint32_t timeout_ms, ClockSetting_t* const Node);

uint32_t ClockSourcToHz(const ClockSource_t clock_source) ;

bool clock_control(ClockDomain_t domain, bool on_off);
bool clock_start_pause_init(void);
float clock_audio_calc( uint16_t freq_value);
float clock_calc_period_s(uint32_t clock_hz, uint32_t prescaler, uint32_t reload);
bool clock_config_100mhz(void) ;

#ifdef HAS_FC7300X
bool ScgRetToRes(const SCG_StatusType ret) ;
#endif
//uint32_t clock_freq_get(nrf_clock_domain_t domain_nrf);
uint32_t calc_prescaler(int32_t bus_freq, int32_t bit_rate);
uint32_t clock_int_per_us(uint64_t delay_in_us);
uint32_t clock_int_per_ms(uint32_t delay_ms);


#ifdef HAS_FC7300X
bool clock_init_peripheral2(const PCC_ClkSrcType e_clock_name,
                            const PCC_ClkGateSrcType eClkSrc,
                            const PCC_ClkDivType eDivider) ;
#endif

#ifdef __cplusplus
}
#endif

#endif // CLOCK_MCAL_H
