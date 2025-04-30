#ifndef PWM_DRV_H
#define PWM_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "pwm_types.h"

bool pwm_init_cache(const PwmConfig_t* const Config, PwmHandle_t* const Node);
bool pwm_init(void);
bool pwm_init_one(uint8_t num);
bool pwm_start(uint8_t num);
bool pwm_stop(uint8_t num);
bool pwm_phase_set(uint8_t num, uint32_t phase_us);
bool pwm_is_valid(uint8_t num);
bool pwm_phase_get(uint8_t num, uint32_t* const phase_us);
bool pwm_duty_get(uint8_t num, PwmChannel_t channel, double* const duty);
bool pwm_duty_set(uint8_t num, PwmChannel_t channel, double duty);
bool pwm_frequency_get(uint8_t num, PwmChannel_t channel, double* const frequency_hz);
bool pwm_frequency_set(uint8_t num, PwmChannel_t channel, double frequency_hz);
const PwmConfig_t* PwmGetConfig(uint8_t num);
PwmHandle_t* PwmGetNode(uint8_t channel_id);

#endif /* PWM_DRV_H */
