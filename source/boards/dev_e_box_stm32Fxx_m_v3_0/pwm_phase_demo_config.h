#ifndef PWM_PHASE_DEMO_CONFIG_H
#define PWM_PHASE_DEMO_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "pwm_phase_demo_types.h"
#include "pwm_phase_demo_dep.h"

extern const PwmPhaseDemoConfig_t PwmPhaseDemoConfig[];
extern PwmPhaseDemoHandle_t PwmPhaseDemoInstance[];

uint32_t pwm_phase_demo_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* PWM_PHASE_DEMO_CONFIG_H */
