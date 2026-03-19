#ifndef PWM_ISR_H
#define PWM_ISR_H

#include "std_includes.h"
#include "pwm_types.h"

bool PwmPulseFinishedCallback_ll(PwmHandle_t *Node, PwmChannel_t channel);
void PwmPulseFinishedHalfCpltCallback(PwmHandle_t* Node ) ;
bool PwmPulseFinishedCallback(uint8_t timer_num, PwmChannel_t channel) ;
void PwmDelayElapsedCallback(PwmHandle_t* Node ) ;

bool PwmPeriodElapsedCallback(uint8_t timer_num);

#endif /* PWM_ISR_H */
