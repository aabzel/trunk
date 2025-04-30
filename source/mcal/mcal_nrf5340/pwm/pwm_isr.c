#include "pwm_isr.h"


#include "pwm_drv.h"

void pwm0_handler(nrfx_pwm_evt_type_t event_type, void* p_context) {
    PwmHandle_t* Node = PwmGetNode(0);
    if(Node) {
        if(NRFX_PWM_EVT_FINISHED == event_type) {
            Node->int_cnt++;
        }
    }
}

void pwm1_handler(nrfx_pwm_evt_type_t event_type, void* p_context) {
    PwmHandle_t* Node = PwmGetNode(1);
    if(Node) {
        if(NRFX_PWM_EVT_FINISHED == event_type) {
            Node->int_cnt++;
        }
    }
}

void pwm2_handler(nrfx_pwm_evt_type_t event_type, void* p_context) {
    PwmHandle_t* Node = PwmGetNode(2);
    if(Node) {
        if(NRFX_PWM_EVT_FINISHED == event_type) {
            Node->int_cnt++;
        }
    }
}

void pwm3_handler(nrfx_pwm_evt_type_t event_type, void* p_context) {
    PwmHandle_t* Node = PwmGetNode(3);
    if(Node) {
        if(NRFX_PWM_EVT_FINISHED == event_type) {
            Node->int_cnt++;
        }
    }
}
