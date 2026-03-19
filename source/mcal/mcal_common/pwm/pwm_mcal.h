#ifndef PWM_MCAL_API_H
#define PWM_MCAL_API_H


#include "std_includes.h"
#include "pwm_types.h"
#include "pwm_config.h"
#include "pwm_custom.h"
#include "pwm_isr.h"
#ifdef HAS_PWM_DIAG
#include "pwm_diag.h"
#endif

/*API*/
const PwmConfig_t* PwmGetConfig(uint8_t num);
PwmHandle_t* PwmGetNode(uint8_t num);
PwmHandle_t* PwmTimerNumToNode(uint8_t timer_num) ;

bool PwmIsValidConfig(const PwmConfig_t * const Config);
bool pwm_mcal_init(void);
bool pwm_init_custom(void);
bool pwm_init_common(const PwmConfig_t* const Config, PwmHandle_t* const Node);
bool pwm_init_one(uint8_t num);
bool pwm_is_valid_duty_cycle(float duty_cycle);
bool pwm_is_valid(uint8_t num);
bool pwm_is_valid_channel(PwmChannel_t channel);
PwmMode_t PwmOnOffToMode(bool on_off) ;

/*setters*/
bool pwm_channel_ctrl_ll(  PwmHandle_t* Node , bool on_off);
bool pwm_channel_ctrl(uint8_t num, TimChannel_t channel, bool on);
bool pwm_channel_start(uint8_t timer_num, uint8_t channel) ;
bool pwm_ctrl_ll(PwmHandle_t* Node, bool on_off);
bool pwm_ctrl(uint8_t num, bool on_off);
bool pwm_start(uint8_t num);
bool pwm_stop(uint8_t num);
bool pwm_phase_set(uint8_t num, uint32_t phase_us);
bool pwm_period_set_ll(PwmHandle_t* Node, uint32_t period);
bool pwm_pulse_diration_set_ll(PwmHandle_t* Node, PwmChannel_t channel, uint32_t pulse_diration);
bool pwm_freq_duty_set(uint8_t pwm_num, float frequency_hz, float duty_cycle);
bool pwm_frequency_set(uint8_t num, float frequency_hz);
bool pwm_frequency_mux_set(uint8_t num, float frequency1_hz, float frequency2_hz, uint32_t impulses);
bool pwm_duty_set(uint8_t num, float duty);

/*getters*/
bool pwm_is_valid(uint8_t num);
bool pwm_phase_get(uint8_t num, uint32_t* const phase_us);
bool pwm_pad_get(uint8_t num, Pad_t* const pad);
bool pwm_duty_get(uint8_t num, float* const duty);
bool pwm_channel_get(uint8_t num, PwmChannel_t* const channel);
bool pwm_channel_duty_get(uint8_t num, PwmChannel_t channel, float* const duty);
bool pwm_channel_frequency_get(uint8_t num, PwmChannel_t channel, float* const frequency_hz);
bool pwm_frequency_get(uint8_t num, float* const frequency_hz);

#endif /* PWM_MCAL_API_H */
