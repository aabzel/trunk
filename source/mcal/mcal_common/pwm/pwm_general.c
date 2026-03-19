#include "pwm_mcal.h"

#include <string.h>

#include "code_generator.h"
#include "common_diag.h"
#include "compiler_const.h"
#include "log.h"
#include "pwm_config.h"
#include "timer_mcal.h"

COMPONENT_IS_VALID(Pwm, pwm)

COMPONENT_GET_NODE(Pwm, pwm)

COMPONENT_GET_CONFIG(Pwm, pwm)

PwmHandle_t* PwmTimerNumToNode(uint8_t timer_num) {
    PwmHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = pwm_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(timer_num == PwmInstance[i].timer_num) {
            if(PwmInstance[i].valid) {
                Node = &PwmInstance[i];
                break;
            }
        }
    }
    return Node;
}

bool pwm_is_valid_duty_cycle(float duty_cycle) {
    bool res = false;
    if(0.0f <= duty_cycle) {
        if(duty_cycle <= 100.0f) {
            res = true;
        }
    }
    return res;
}

bool PwmIsValidConfig(const PwmConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        res = pwm_is_valid_duty_cycle(Config->duty);
        if(!res) {
            LOG_ERROR(PWM, "PWM%u,Duty,Err", Config->num);
            res = false;
        }

        ifn(0.0 < Config->frequency_hz) {
            LOG_ERROR(PWM, "PWM%u,frequency,Err", Config->num);
            res = false;
        }

        ifn(Config->ComparatorHandler) { LOG_WARNING(PWM, "PWM%u,ComparatorHandler,Err", Config->num); }

        ifn(Config->PulseDoneHandler) { LOG_WARNING(PWM, "PWM%u,PulseDoneHandler,Err", Config->num); }

        ifn(Config->name) {
            LOG_ERROR(PWM, "PWM%u,name,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool pwm_init_common(const PwmConfig_t* const Config, PwmHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->phase_us = Config->phase_us;
            Node->name = Config->name;
            Node->channel = Config->channel;
            Node->duty = Config->duty;
            Node->on = Config->on;
            Node->Pad = Config->Pad;
            Node->channel_cnt = Config->channel_cnt;
            Node->frequency_hz = Config->frequency_hz;
            Node->PulseDoneHandler = Config->PulseDoneHandler;
            Node->ComparatorHandler = Config->ComparatorHandler;
            Node->timer_num = Config->timer_num;
            Node->init_phase = Config->init_phase;
            res = true;
        }
    }
    return res;
}

PwmMode_t PwmOnOffToMode(bool on_off) {
    PwmMode_t mode = PWM_MODE_OFF;
    switch((uint8_t)on_off) {
    case true:
        mode = PWM_MODE_ON;
        break;
    case false:
        mode = PWM_MODE_OFF;
        break;
    default:
        mode = PWM_MODE_OFF;
        break;
    }
    return mode;
}

bool pwm_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = pwm_ctrl_ll(Node, on_off);
    }

    return res;
}

_WEAK_FUN_
bool pwm_frequency_set(uint8_t num, float frequency_hz) {
    bool res = false;
    LOG_DEBUG(PWM, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool pwm_duty_set(uint8_t num, float duty) {
    bool res = false;
    LOG_ERROR(PWM, "[%s]NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool pwm_pad_get(uint8_t num, Pad_t* const pad) {
    bool res = false;
    LOG_ERROR(PWM, "[%s]NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool pwm_ctrl_ll(PwmHandle_t* Node, bool on_off) {
    bool res = false;
    LOG_DEBUG(PWM, "PWM%u,%s", Node->num, OnOffToStr(on_off));
    if(Node) {
        res = timer_channel_ctrl(Node->timer_num, (TimerCapComChannel_t)Node->channel, on_off);
        if(res) {
            Node->mode = PwmOnOffToMode(on_off);
            LOG_PARN(PWM, "TIMER%u,%s,CtrlOk", Node->timer_num, OnOffToStr(on_off));
        } else {
            LOG_DEBUG(PWM, "TIMER%u CtrlErr", Node->timer_num);
            res = false;
        }
    }

    return res;
}

_WEAK_FUN_ bool pwm_phase_set(uint8_t num, uint32_t phase_us) {
    bool res = false;
    LOG_ERROR(PWM, "[%s]NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool pwm_frequency_get(uint8_t num, float* const frequency_hz) {
    bool res = false;
    LOG_ERROR(PWM, "[%s]NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool pwm_duty_get(uint8_t num, float* const duty) {
    bool res = false;
    LOG_ERROR(PWM, "[%s]NotImplemented", __FUNCTION__);
    return res;
}

COMPONENT_INIT_PATTERT_CNT(PWM, PWM, pwm, 10)
