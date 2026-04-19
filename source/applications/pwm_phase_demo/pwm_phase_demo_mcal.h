#ifndef PWM_PHASE_DEMO_MCAL_H
#define PWM_PHASE_DEMO_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "pwm_phase_demo_config.h"
#include "pwm_phase_demo_types.h"
#ifdef HAS_PWM_PHASE_DEMO_DIAG
#include "pwm_phase_demo_diag.h"
#endif

/* API */
const PwmPhaseDemoConfig_t* PwmPhaseDemoGetConfig(uint8_t num);
PwmPhaseDemoHandle_t* PwmPhaseDemoGetNode(uint8_t num);
bool PwmPhaseDemoIsValidConfig(const PwmPhaseDemoConfig_t* const Config);

#ifdef HAS_PWM_PHASE_DEMO_CUSTOM
const PwmPhaseDemoInfo_t* PwmPhaseDemoGetInfo(uint8_t num);
#endif

bool pwm_phase_demo_mcal_init(void);
bool pwm_phase_demo_init_custom(void);
bool pwm_phase_demo_init_one(uint8_t num);

bool pwm_phase_demo_proc_one(uint8_t num);
bool pwm_phase_demo_proc(void);

/*setters*/

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* PWM_PHASE_DEMO_MCAL_H */
