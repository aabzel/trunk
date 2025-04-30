#ifndef PWM_DRV_H
#define PWM_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "pwm_types.h"

bool pwm_init(void);
bool pwm_ctrl(uint8_t num, PwmChannel_t channel, bool on);
bool oe_ctrl(uint8_t num, PwmChannel_t channel, bool on);
bool pwm_start(uint8_t num, PwmChannel_t channel);
bool pwm_stop(uint8_t timer_num, PwmChannel_t channel);
bool pwm_phase_set(uint8_t num, uint32_t phase);
bool pwm_phase_get(uint8_t num, uint32_t* phase);
bool pwm_duty_get(uint8_t num, PwmChannel_t channel, double* duty);
bool pwm_duty_set(uint8_t num, PwmChannel_t channel, double duty);

#endif /* PWM_DRV_H  */
