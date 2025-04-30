#ifndef PWM_ISR_H
#define PWM_ISR_H

#include "nrfx_pwm.h"

void pwm0_handler(nrfx_pwm_evt_type_t event_type, void* p_context) ;
void pwm1_handler(nrfx_pwm_evt_type_t event_type, void* p_context) ;
void pwm2_handler(nrfx_pwm_evt_type_t event_type, void* p_context) ;
void pwm3_handler(nrfx_pwm_evt_type_t event_type, void* p_context) ;

#endif /* PWM_ISR_H  */
