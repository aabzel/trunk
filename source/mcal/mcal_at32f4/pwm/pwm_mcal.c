#include "pwm_mcal.h"

#include <stdbool.h>
#include <stdint.h>

#include "common_diag.h"
#include "data_utils.h"
#include "log.h"
#include "microcontroller_const.h"
#include "pwm_config.h"
#include "pwm_custom_types.h"
#include "timer_mcal.h"

bool pwm_is_valid_channel(PwmChannel_t channel) {
    bool res = false;
    if(PWM_CHANNEL_0 <= channel) {
        if(channel <= PWM_CHANNEL_5) {
            res = true;
        }
    }
    return res;
}

static TimerCapComChannel_t PwmChannelToTimerChannel(PwmChannel_t pwm_channel) {
    TimerCapComChannel_t timer_channel = TIMER_CC_UNDEF;
    switch(pwm_channel) {
    case PWM_CHANNEL_0:
        timer_channel = TIMER_CC_CHAN_0;
        break;
    case PWM_CHANNEL_1:
        timer_channel = TIMER_CC_CHAN_1;
        break;
    case PWM_CHANNEL_2:
        timer_channel = TIMER_CC_CHAN_2;
        break;
    case PWM_CHANNEL_3:
        timer_channel = TIMER_CC_CHAN_3;
        break;
    case PWM_CHANNEL_4:
        timer_channel = TIMER_CC_CHAN_4;
        break;
    case PWM_CHANNEL_5:
        timer_channel = TIMER_CC_CHAN_5;
        break;
    default:
        timer_channel = TIMER_CC_UNDEF;
        break;
    }
    return timer_channel;
}

bool pwm_channel_ctrl_ll(PwmHandle_t* Node, bool on_off) {
    bool res = false;
    if(Node) {
        LOG_INFO(PWM, "PWM%u,CH%u,%s", Node->num, Node->channel, OnOffToStr(on_off));
        TimerCapComChannel_t timer_channel = PwmChannelToTimerChannel(Node->channel);
        res = timer_channel_ctrl(Node->timer_num, timer_channel, on_off);
    } else {
        LOG_ERROR(PWM, "PWM%u NodeErr", Node->num);
    }

    return res;
}

bool pwm_channel_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = pwm_channel_ctrl_ll(Node, on_off);
    }
    return res;
}

bool pwm_duty_get(uint8_t num, double* const out_duty_cycle) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = timer_duty_get(Node->timer_num, Node->channel, out_duty_cycle);
    }
    return res;
}

#if 0
bool pwm_set_phase(uint8_t num, uint32_t phase) {
    bool res = false;
    return res;
}
#endif

bool pwm_start(uint8_t num) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = timer_ctrl(Node->timer_num, true);
    }
    return res;
}

bool pwm_stop(uint8_t num) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = timer_ctrl(Node->timer_num, false);
        Node->mode = PWM_MODE_OFF;
    }
    return res;
}

bool pwm_init_custom(void) {
    bool res = true;
    return res;
}

/*called from ISR*/
bool pwm_pulse_diration_set_ll(PwmHandle_t* Node, PwmChannel_t channel, uint32_t pulse_diration) {
    bool res = false;
    if(Node) {
        res = timer_compare_set(Node->timer_num, (TimerCapComChannel_t)Node->channel, pulse_diration);
    }
    return res;
}
/*duty_cycle - %*/
static bool pwm_duty_set_ll(PwmHandle_t* Node, double duty_cycle) {
    bool res = false;
    if(Node) {
        LOG_INFO(PWM, "PWM%u,Set,Duty:%f %%", Node->num, duty_cycle);
        uint32_t period = timer_period_get(Node->timer_num);
        uint32_t compare_value = (((double)period) * duty_cycle) / 100.0;
        // compare_value = period - compare_value;

        LOG_WARNING(PWM, "TIMER%u,CH:%u,Comp:%u/%u", Node->timer_num, Node->channel, compare_value, period);
        res = timer_compare_set(Node->timer_num, (TimerCapComChannel_t)Node->channel, compare_value);
        if(res) {
            Node->duty = duty_cycle;
            LOG_INFO(PWM, "TIMER%u CompareSetOk", Node->timer_num);
        } else {
            LOG_ERROR(PWM, "TIMER%u CompareSetErr", Node->timer_num);
        }
    } else {
        LOG_ERROR(PWM, "PWM%u NodeErr", Node->num);
    }
    return res;
}

bool pwm_duty_set(uint8_t num, double duty_cycle) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        // LOG_WARNING(PWM, "PWM%u,Set,Duty:%f %%", num, duty_cycle);
        res = pwm_duty_set_ll(Node, duty_cycle);
        if(res) {
            Node->duty = duty_cycle;
        }
    } else {
        LOG_ERROR(PWM, "PWM%u,NodeErr", num);
    }
    return res;
}

/*called from ISR*/
bool pwm_period_set_ll(PwmHandle_t* Node, uint32_t period) {
    bool res = false;
    if(Node) {
        res = timer_period_set(Node->timer_num, period);
    }
    return res;
}

bool pwm_frequency_set(uint8_t num, double frequency_hz) {
    bool res = false;
    LOG_INFO(PWM, "PWM%u,Set,Freq:%7.3f Hz", num, frequency_hz);
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = timer_frequency_set(Node->timer_num, frequency_hz);
        if(res) {
            Node->frequency_hz = frequency_hz;
            LOG_INFO(PWM, "TIMER%u FreqSetOk", Node->timer_num);
            res = pwm_duty_set_ll(Node, Node->duty);
            if(res) {
                Node->mode = PWM_MODE_ON;
                LOG_INFO(PWM, "TIMER%u UpdateDutyOk", Node->timer_num);
            } else {
                LOG_ERROR(PWM, "TIMER%u UpdateDutyErr, Duty:%f %%", Node->timer_num, Node->duty);
            }
        } else {
            LOG_ERROR(PWM, "TIMER%u,FreqSetErr", Node->timer_num);
        }
    }
    return res;
}

bool pwm_init_one(uint8_t num) {
    bool res = false;
    const PwmConfig_t* Config = PwmGetConfig(num);
    if(Config) {
        LOG_WARNING(PWM, "Init:%s", PwmConfigToStr(Config));
        PwmHandle_t* Node = PwmGetNode(num);
        if(Node) {
            uint32_t ok = 0;
            res = pwm_init_cache(Config, Node);
            if(res) {
                ok++;
            }

            pwm_ctrl(num, false);

            res = pwm_frequency_set(num, Node->frequency_hz);
            if(res) {
                ok++;
                LOG_INFO(PWM, "PWM%u,FreqSetOk", num);
            } else {
                LOG_ERROR(PWM, "PWM%u,FreqSetErr", num);
            }

            res = pwm_duty_set(num, Node->duty);
            if(res) {
                ok++;
                LOG_INFO(PWM, "PWM%u DutySetOk", num);
            } else {
                LOG_ERROR(PWM, "PWM%u DutySetErr", num);
            }

            res = pwm_channel_ctrl(num, Node->channel_on);
            if(res) {
                ok++;
                LOG_INFO(PWM, "PWM%u,ChannelCtrlSetOk", num);
            } else {
                LOG_ERROR(PWM, "PWM%u,ChannelCtrlSetErr", num);
            }

            res = pwm_ctrl(num, Node->on);
            if(res) {
                ok++;
                LOG_INFO(PWM, "PWM%u,Ctrl,%u,SetOk", num, Node->on);
            } else {
                LOG_ERROR(PWM, "PWM%u,CtrlSetErr", num);
            }

            if(5 == ok) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}

static bool pwm_compose_signal(PwmHandle_t* Node, PwmSignal_t* Signal, double frequency_hz, double duty) {
    bool res = false;
    if(Signal) {
        double tick_s = timer_tick_get_s(Node->timer_num);
        LOG_WARNING(PWM, "Tick:%f s", tick_s);
        double period_s = 1.0 / frequency_hz;
        uint32_t value = (uint32_t)(period_s / tick_s);
        Signal->period = value;
        Signal->pulse_diration = (uint32_t)(duty * ((double)Signal->period) / 100.0);
        LOG_WARNING(PWM, "%s", SignalToStr(Signal));
        res = true;
    }
    return res;
}

bool pwm_frequency_mux_set(uint8_t num, double frequency1_hz, double frequency2_hz, uint32_t impulses) {
    bool res = false;
    LOG_WARNING(PWM, "PWM%u Set Freq1:%f Hz,Freq2:%f Hz,Pulses:%u", num, frequency1_hz, frequency2_hz, impulses);
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = pwm_compose_signal(Node, &Node->Modulation.Signal[0], frequency1_hz, 50.0);
        res = pwm_compose_signal(Node, &Node->Modulation.Signal[1], frequency2_hz, 50.0) && res;
        if(res) {
            Node->Modulation.period_cnt = impulses;
            Node->mode = PWM_MODE_FREQ_MUX;
            Node->Modulation.impulse_cnt = 0;
            Node->Modulation.cur_signal = 1;
            res = pwm_ctrl_ll(Node, true);
            res = timer_ctrl(Node->timer_num, true);
        }
    }
    return res;
}

bool pwm_frequency_get(uint8_t num, double* const frequency_hz) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = timer_frequency_get(Node->timer_num, frequency_hz);
    }
    return res;
}

bool pwm_freq_duty_set(uint8_t num, double frequency_hz, double duty_cycle) {
    bool res = false;
    LOG_INFO(BOARD, "PWM%u,Set,Freq:%f Hz,Duty:%f %%", num, frequency_hz, duty_cycle);
    // res = pwm_stop(num);
    res = pwm_duty_set(num, duty_cycle);
    if(res) {
        res = pwm_frequency_set(num, frequency_hz);
        if(res) {
            res = pwm_start(num);
        } else {
            LOG_ERROR(PWM, "PWM%u,FreqSetErr", num);
        }
    } else {
        LOG_ERROR(PWM, "PWM%u,DutuSetErr", num);
    }

    return res;
}

bool pwm_pad_get(uint8_t num, Pad_t* const pad) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        pad->port = PORT_UNDEF;
        pad->pin = 0;
        res = timer_out_channel_pad_get(Node->timer_num, Node->channel, pad);
    }
    return res;
}
