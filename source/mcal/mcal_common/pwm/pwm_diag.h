#ifndef PWM_DIAG_H
#define PWM_DIAG_H

#include <stdbool.h>

#include "pwm_types.h"

const char* PwmConfig2Str(const PwmConfig_t* const Config);
bool PwmDiagConfig(const PwmConfig_t* const Config);

#endif /* PWM_DIAG_H */
