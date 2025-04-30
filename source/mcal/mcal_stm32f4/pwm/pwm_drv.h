#ifndef PWM_DRV_H
#define PWM_DRV_H

#include <stdbool.h>
#include <stdint.h>

#include "pwm_stm32_types.h"

#ifndef HAS_TIMER
#error "+HAS_TIMER"
#endif

#ifndef HAS_PWM
#error "+HAS_PWM"
#endif

bool pwm_init(void);
bool pwm_ctrl(uint8_t tim_num, TimChannel_t channel, bool on);
bool oe_ctrl(uint8_t tim_num, TimChannel_t channel, bool on);
bool pwm_start(uint8_t tim_num, TimChannel_t channel);
bool pwm_stop(uint8_t timer_num, TimChannel_t channel);
bool pwm_set_phase(uint8_t tim_num, uint32_t phase);
bool pwm_get_phase(uint8_t tim_num, uint32_t* phase);
bool pwm_get_duty(uint8_t tim_num, TimChannel_t channel, double* duty);
bool pwm_set_duty(uint8_t tim_num, TimChannel_t channel, double duty);

#endif /* PWM_DRV_H  */
