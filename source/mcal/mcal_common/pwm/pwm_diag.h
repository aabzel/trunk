#ifndef PWM_MCAL_DIAG_H
#define PWM_MCAL_DIAG_H

#include <stdbool.h>

#include "pwm_types.h"

const char* PwmSignalToStr(const PwmSignalBinary_t * const PwmSignal) ;
const char* SignalToStr(const PwmSignal_t* const Signal);
const char* PwmConfigToStr(const PwmConfig_t* const Config);
bool PwmDiagConfig(const PwmConfig_t* const  Config);
bool pwm_diag(char* key_word1, char* key_word2);

#endif /* PWM_MCAL_DIAG_H */
