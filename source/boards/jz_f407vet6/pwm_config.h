#ifndef PWM_CONFIG_GENERAL_H
#define PWM_CONFIG_GENERAL_H

#include "std_includes.h"
#include "pwm_types.h"

#ifndef HAS_PWM
#error "Add HAS_PWM"
#endif /*HAS_PWM*/

extern const PwmConfig_t PwmConfig[];
extern PwmHandle_t PwmInstance[];

uint32_t pwm_get_cnt(void);

#endif /* PWM_CONFIG_GENERAL_H  */
