#ifndef PWM_PHASE_DEMO_DIAG_H
#define PWM_PHASE_DEMO_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "pwm_phase_demo_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_PWM_PHASE_DEMO
#error "+HAS_PWM_PHASE_DEMO"
#endif

#ifndef HAS_PWM_PHASE_DEMO_DIAG
#error "+HAS_PWM_PHASE_DEMO_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool pwm_phase_demo_diag(void);
bool pwm_phase_demo_diag_one(uint8_t num);
const char* PwmPhaseDemoConfigToStr(const PwmPhaseDemoConfig_t* const Config);
const char* PwmPhaseDemoNodeToStr(const PwmPhaseDemoHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* PWM_PHASE_DEMO_DIAG_H  */
