#include "pwm_isr.h"

#include "pwm_mcal.h"

static uint8_t toggle_u8(uint8_t in_val) {
    uint8_t val_out = 0;
    switch(in_val) {
    case 1:
        val_out = 0;
        break;
    case 0:
        val_out = 1;
        break;
    default:
        val_out = 0;
        break;
    }
    return val_out;
}

static bool PwmPeriodFinishedCallback(PwmHandle_t* Node) {
    bool res = false;
    if(Node) {
        if(Node->PeriodDoneHandler) {
            res = Node->PeriodDoneHandler();
        }
        Node->period_elapse_cnt++;
        Node->Modulation.impulse_cnt++;
        switch(Node->mode) {
        case PWM_MODE_FREQ_MUX: {
            if(Node->Modulation.period_cnt <= Node->Modulation.impulse_cnt) {
                Node->Modulation.impulse_cnt = 0;
                Node->Modulation.cur_signal = toggle_u8(Node->Modulation.cur_signal);
                res = pwm_period_set_ll(Node, Node->Modulation.Signal[Node->Modulation.cur_signal].period);
                res = pwm_pulse_diration_set_ll(Node, Node->timer_channel,
                                                Node->Modulation.Signal[Node->Modulation.cur_signal].pulse_diration);
            }
        } break;
        case PWM_MODE_ON: {
            res = true;
        } break;
        case PWM_MODE_OFF: {
            res = true;
        } break;
        default:
            break;
        } // switch
    }
    return res;
}

void PwmPulseFinishedHalfCpltCallback(PwmHandle_t* Node) {
    if(Node) {
        Node->pulse_fin_half_cnt++;
    }
}

bool PwmPulseFinishedCallback_ll(PwmHandle_t* Node, TimerOutChannel_t channel) {
    bool res = false;
    if(Node) {
        res = true;
        if(Node->ComparatorHandler) {
            res = Node->ComparatorHandler();
        }
        Node->pulse_fin_cnt++;
    }
    return res;
}

bool PwmPulseFinishedCallback(uint8_t timer_num, TimerOutChannel_t channel) {
    bool res = false;
    uint8_t pwm_cnt = 0;
    pwm_cnt = pwm_get_cnt();
    uint8_t p = 0;
    for(p = 0; p < pwm_cnt; p++) {
        if(timer_num == PwmInstance[p].timer_num) {
            if(channel == PwmInstance[p].timer_channel) {
                res = PwmPulseFinishedCallback_ll(&PwmInstance[p], channel);
            }
        }
    }
    return res;
}

bool PwmPeriodElapsedCallback(uint8_t timer_num) {
    bool res = false;
    uint8_t pwm_cnt = 0;
    uint8_t p = 0;
    pwm_cnt = pwm_get_cnt();
    for(p = 0; p < pwm_cnt; p++) {
        if(timer_num == PwmInstance[p].timer_num) {
            res = PwmPeriodFinishedCallback(&PwmInstance[p]);
        }
    }
    return res;
}
