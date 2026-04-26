#include "pwm_mcal.h"

#include <stddef.h>
#include <string.h>

#include "bit_utils.h"
#include "common_diag.h"
#include "data_utils.h"
#include "float_utils.h"
#include "gpio_mcal.h"
#include "hal_diag.h"
#include "hal_mcal.h"
#include "pwm_diag.h"
#include "std_includes.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"
#include "sys_config.h"
#include "timer_mcal.h"
#include "time_mcal.h"

#ifdef HAS_CLOCK
#include "clock_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

static uint32_t PwmPolarityToStm32OCPolarity(const PwmPolarity_t pwm_polarity) {
    uint32_t oc_polarity = TIM_OCPOLARITY_HIGH;
    switch(pwm_polarity) {
    case PWM_POLARITY_LOW:
        oc_polarity = TIM_OCPOLARITY_LOW;
        break;
    case PWM_POLARITY_HIGH:
        oc_polarity = TIM_OCPOLARITY_HIGH;
        break;
    default:
        break;
    }
    return oc_polarity;
}

static int32_t TimerPhaseUsToCompareValue(uint8_t num,
                                          int32_t phase_us) {
    int32_t phase_value = 0;
    float tick_s = timer_tick_get_s(num);
    float phase_s = USEC_2_SEC(phase_us);
    float phase_value_f =  (phase_s / tick_s);
    phase_value = (int32_t) phase_value_f;
    return phase_value;
}

static PwmPolarity_t  PwmPolarityToggle(const PwmPolarity_t prev_polarity){
    PwmPolarity_t out_polarity=PWM_POLARITY_LOW;
    switch(prev_polarity){
        case PWM_POLARITY_LOW: out_polarity=PWM_POLARITY_HIGH;break;
        case PWM_POLARITY_HIGH: out_polarity=PWM_POLARITY_LOW;break;
        default: out_polarity=PWM_POLARITY_LOW;break;
    }
    return out_polarity;
}

static const Channal2Code_t ChannalToCodeLUT[] = {
    {
        .channel = TIMER_OUT_CHANNEL_1,
        .stm32_ch_code = TIM_CHANNEL_1,
    },
    {
        .channel = TIMER_OUT_CHANNEL_2,
        .stm32_ch_code = TIM_CHANNEL_2,
    },
    {
        .channel = TIMER_OUT_CHANNEL_3,
        .stm32_ch_code = TIM_CHANNEL_3,
    },
    {
        .channel = TIMER_OUT_CHANNEL_4,
        .stm32_ch_code = TIM_CHANNEL_4,
    },
    {
        .channel = TIMER_OUT_CHANNEL_ALL,
        .stm32_ch_code = TIM_CHANNEL_ALL,
    },
};

static bool is_valid_channel(const TimerOutChannel_t channel) {
    bool res = false;
    if(TIMER_OUT_CHANNEL_1 <= channel) {
        if(channel <= TIMER_OUT_CHANNEL_4) {
            res = true;
        }
    }
    return res;
}

/* Return  Channel TIM Channels to be enabled
          This parameter can be one of the following values:
             TIM_CHANNEL_1: TIM Channel 1 selected
             TIM_CHANNEL_2: TIM Channel 2 selected
             TIM_CHANNEL_3: TIM Channel 3 selected
             TIM_CHANNEL_4: TIM Channel 4 selected
*/
static uint32_t Channel2Code(const TimerOutChannel_t channel) {
    uint32_t stm32_ch_val = 0;
    bool res = is_valid_channel(channel);
    if(res) {
        uint8_t i = 0;
        for(i = 0; i < ARRAY_SIZE(ChannalToCodeLUT); i++) {
            if(channel == ChannalToCodeLUT[i].channel) {
                stm32_ch_val = ChannalToCodeLUT[i].stm32_ch_code;
                break;
            }
        }
    }
    return stm32_ch_val;
}

bool tim_get_compare(uint8_t timer_num, TimerOutChannel_t channel, uint32_t* const out_compare) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(timer_num);
    if(Info) {
        res = is_valid_channel(channel);
        if(res) {
            uint32_t ccrx = 0;
            switch(channel) {
            case TIMER_OUT_CHANNEL_1:
                ccrx = Info->TIMx->CCR1;
                break;
            case TIMER_OUT_CHANNEL_2:
                ccrx = Info->TIMx->CCR2;
                break;
            case TIMER_OUT_CHANNEL_3:
                ccrx = Info->TIMx->CCR3;
                break;
            case TIMER_OUT_CHANNEL_4:
                ccrx = Info->TIMx->CCR4;
                break;
            default:
                res = false;
                break;
            }
            if(out_compare) {
                res = true;
                (*out_compare) = ccrx;
            }
        }
    }
    return res;
}

bool pwm_channel_start(uint8_t timer_num, uint8_t channel) {
    bool res = false;
    TimerHandle_t* Timer = TimerGetNode(timer_num);
    if(Timer) {
        HAL_StatusTypeDef ret;
        uint32_t hal_channel = Channel2Code((TimerOutChannel_t)channel);
        ret = HAL_TIM_PWM_Start(&Timer->Handle, hal_channel);
        if(HAL_OK == ret) {
            LOG_INFO(PWM, "StartOk");
            res = true;
        } else {
#ifdef HAS_DIAG
            LOG_ERROR(PWM, "StartErr:%s", HalStatusToStr(ret));
#endif
            res = false;
        }
    }
    return res;
}

bool tim_set_compare(uint8_t timer_num, TimerOutChannel_t channel, uint32_t compare) {
    bool res = false;
#ifdef HAS_DIAG
    LOG_DEBUG(PWM, "SetCompare T:%u C:%u Compare:%u", timer_num, channel, compare);
#endif
    TimerInfo_t* Info = TimerGetInfo(timer_num);

    if(Info) {
        res = is_valid_channel(channel);
        if(res) {
            switch(channel) {
            case TIMER_OUT_CHANNEL_1:
                Info->TIMx->CCR1 = compare;
                break;
            case TIMER_OUT_CHANNEL_2:
                Info->TIMx->CCR2 = compare;
                break;
            case TIMER_OUT_CHANNEL_3:
                Info->TIMx->CCR3 = compare;
                break;
            case TIMER_OUT_CHANNEL_4:
                Info->TIMx->CCR4 = compare;
                break;
            default:
                res = false;
                break;
            }
            res = true;
        }
    }
    return res;
}

bool pwm_get_duty(uint8_t timer_num, TimerOutChannel_t channel, float* out_duty_cycle) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(timer_num);
    if(Info) {
        uint32_t ccrx = 0;
        res = tim_get_compare(timer_num, channel, &ccrx);
        if(res) {
            res = false;
            float duty_cycle = 0.0;
            duty_cycle = 100.0 * ((float)(ccrx) / ((float)Info->TIMx->ARR));
            if(out_duty_cycle) {
                (*out_duty_cycle) = duty_cycle;
                res = true;
            }
        }
    }
    return res;
}

static bool is_valid_duty_cycle(float duty_cycle) {
    bool res = false;
    if(0.0 <= duty_cycle && (duty_cycle <= 100.0)) {
        res = true;
    }
    return res;
}

bool timer_duty_set(uint8_t timer_num, TimerOutChannel_t channel, float duty_cycle) {
    bool res = false;
    TimerInfo_t* Info = TimerGetInfo(timer_num);
    if(Info) {
        res = is_valid_duty_cycle(duty_cycle);
        if(res) {
            uint32_t compare = 0;
            compare = (uint32_t)(   (        (  (float)  Info->TIMx->ARR ) * duty_cycle )/ 100.0f          );
#ifdef HAS_DIAG
            LOG_DEBUG(PWM, "TIM%u_CH%u,Compare:%u,ARR:%u", timer_num, channel, compare, Info->TIMx->ARR);
#endif
            res = is_valid_channel(channel);
            if(res) {
                res = tim_set_compare(timer_num, channel, compare);
            }
        }
    }
    return res;
}

bool pwm_duty_set(uint8_t num, float duty) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = timer_duty_set(Node->TimChan.timer, (TimerOutChannel_t)Node->TimChan.channel, duty);
    }
    // res = pwm_ctrl(num, true);
    return res;
}

bool pwm_freq_duty_set(uint8_t pwm_num, float frequency_hz, float duty_cycle) {
    bool res = false;
#ifdef HAS_PWM_DIAG
    LOG_DEBUG(PWM, "N:%u,Freq:%f Hz,Duty:%f %%", pwm_num, frequency_hz, duty_cycle);
#endif
    res = pwm_frequency_set(pwm_num, frequency_hz);
    if(res) {
        res = pwm_duty_set(pwm_num, duty_cycle);
    }
    return res;
}

bool pwm_frequency_set(uint8_t num, float frequency_hz) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        float period_s = 1.0f / frequency_hz;
        res = timer_period_set_s(Node->TimChan.timer, period_s);
    }
    return res;
}

bool pwm_polarity_set(const uint8_t num, const PwmPolarity_t polarity) {
    bool res = false;
    PwmHandle_t *Node = PwmGetNode(num);
    if (Node) {
        res = timer_polarity_set(Node->TimChan.timer, Node->TimChan.channel, (TimerPolarity_t) polarity);
    }
    return res;
}

bool pwm_polarity_get(const uint8_t num, PwmPolarity_t* const polarity) {
    bool res = false;
    PwmHandle_t *Node = PwmGetNode(num);
    if(Node) {
        if(polarity) {
            *polarity = PWM_POLARITY_UNDEF;
            TimerPolarity_t tim_polarity;
            res = timer_polarity_get(Node->TimChan.timer, Node->TimChan.channel, &tim_polarity);
            if(res) {
                *polarity = (PwmPolarity_t) tim_polarity;
            }
        }
    }
    return res;
}

bool pwm_phase_set_sw(uint8_t num, int32_t phase_us) {
    bool res = false;
    PwmHandle_t *Node = PwmGetNode(num);
    if(Node) {
        timer_ctrl(Node->PhaseComparator.timer, false);
        timer_ctrl(Node->TimChan.timer, false);

        int32_t compare_value = TimerPhaseUsToCompareValue(Node->PhaseComparator.timer, phase_us);
        int32_t counter_base = (int32_t) timer_counter_get(Node->PhaseComparator.timer);
        int32_t value = counter_base + compare_value;
        res = timer_counter_set(Node->TimChan.timer, (uint32_t) value);

        timer_ctrl(Node->PhaseComparator.timer, true);
        timer_ctrl(Node->TimChan.timer, true);

        LOG_INFO(PWM, "SetPhaSW:%d us,compareValue:%d,CNTMaster:%u,CNTslave:%u", phase_us, compare_value,counter_base,value);
    }
    return res;
}

bool pwm_phase_deg(uint8_t num,float phase_deg) {
    int32_t phase_us = pwm_phase_deg_to_phase_us(num, phase_deg);
    bool res = pwm_phase_set_hw(num,   phase_us);
    return res;
}

static bool pwm_phase_get_hw(const uint8_t num, uint32_t * const phase_us){
    bool res = false;
    PwmHandle_t *Node = PwmGetNode(num);
    if (Node) {
        if(phase_us) {
            uint32_t compare_value = timer_cc_val_get(Node->PhaseComparator.timer, Node->PhaseComparator.channel);
            *phase_us = (int32_t) timer_period_to_us(Node->PhaseComparator.timer, compare_value);
            LOG_DEBUG(PWM, "GetPha:PWM%u,PHA:%u cnt=%u us",num, compare_value, *phase_us);
            res = true;
        }
    }
    return res;
}

bool pwm_phase_get(uint8_t num, uint32_t* const phase_us){
    bool res=pwm_phase_get_hw(num, phase_us);
    return res;
}

bool pwm_phase_set_hw(const uint8_t num, const int32_t phase_us) {
    bool res = false;
    PwmHandle_t *Node = PwmGetNode(num);
    if (Node) {
        int32_t compare_value = TimerPhaseUsToCompareValue(Node->PhaseComparator.timer, phase_us);
        res = timer_compare_set(Node->PhaseComparator.timer,
                                Node->PhaseComparator.channel,
                                compare_value);
        LOG_DEBUG(PWM,"SetPhaHW:%u us,compareValue:%u,PHAcmp:%s",phase_us,compare_value,TimChanToStr(Node->PhaseComparator));
    }
    return res;
}


bool pwm_phase_set(uint8_t num, int32_t phase_us) {
    bool res = false;
    PwmHandle_t *Node = PwmGetNode(num);
    if (Node) {
        res = pwm_phase_set_hw(num, phase_us);
    }
    return res;
}

bool pwm_polarity_toggle(const uint8_t num) {
    bool res = false;
    PwmHandle_t *Node = PwmGetNode(num);
    if (Node) {
        Node->polarity = PwmPolarityToggle(Node->polarity);
        res = pwm_polarity_set(num, Node->polarity);
    }
    return res;
}

bool pwm_pad_get(const uint8_t num, Pad_t* const pad) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        *pad = Node->Pad;
        res = true;
    }
    return res;
}

bool pwm_duty_get(const uint8_t num, float* const duty_out) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        uint32_t comparator = timer_cc_val_get(Node->TimChan.timer, (TimerOutChannel_t)Node->TimChan.channel);
        uint32_t period = timer_period_get(Node->TimChan.timer);
        if(duty_out) {
            *duty_out = ( (float)comparator*100.0f ) / ((float)period);
            res = true;
        }
    }
    return res;
}

bool pwm_is_work(uint8_t num) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = timer_channel_is_work(Node->TimChan.timer, (TimerOutChannel_t)Node->TimChan.channel);
    }
    return res;
}

bool pwm_frequency_get(uint8_t num, float* const frequency_hz) {
    bool res = false;
    PwmHandle_t* Node = PwmGetNode(num);
    if(Node) {
        res = timer_frequency_get(Node->TimChan.timer, frequency_hz);
    }
    return res;
}

bool pwm_set_phase(uint8_t timer_num, uint32_t phase) {
    bool res = false;
    return res;
}

bool tim_oc_start(uint8_t timer_num, TimerOutChannel_t channel) {
    bool res = false;
    TimerHandle_t* Timer = TimerGetNode(timer_num);
    if(Timer) {
        uint32_t hal_channel = Channel2Code(channel);
        HAL_StatusTypeDef ret;
        ret = HAL_TIM_OC_Start(&Timer->Handle, hal_channel);
        res = HAL_retToRes(ret);
        if(res) {
#ifdef HAS_DIAG
            LOG_INFO(TIMER, "OcStartOk");
#endif
        } else {
#ifdef HAS_DIAG
            LOG_ERROR(TIMER, "OcStartErr %s", HalStatusToStr(ret));
#endif
        }
    }
    return res;
}

bool tim_oc_stop(uint8_t timer_num, TimerOutChannel_t channel) {
    bool res = false;
    TimerHandle_t* Timer = TimerGetNode(timer_num);
    if(Timer) {
        HAL_StatusTypeDef ret;
        uint32_t hal_channel = Channel2Code(channel);
        ret = HAL_TIM_OC_Stop(&Timer->Handle, hal_channel);
        if(HAL_OK == ret) {
#ifdef HAS_DIAG
            LOG_INFO(TIMER, "OcStopOk");
#endif
            res = true;
        } else {
#ifdef HAS_DIAG
            LOG_ERROR(TIMER, "OcStopErr %s", HalStatusToStr(ret));
#endif
            res = false;
        }
    }
    return res;
}

bool pwm_channel_stop(uint8_t timer_num, TimerOutChannel_t channel) {
    bool res = false;
    TimerHandle_t* Timer = TimerGetNode(timer_num);
    if(Timer) {
        HAL_StatusTypeDef ret;
        uint32_t hal_channel = Channel2Code(channel);
        ret = HAL_TIM_PWM_Stop(&Timer->Handle, hal_channel);
        if(HAL_OK == ret) {
#ifdef HAS_DIAG
            LOG_INFO(PWM, "StopOk");
#endif
            res = true;
        } else {
#ifdef HAS_DIAG
            LOG_ERROR(PWM, "StopErr %s", HalStatusToStr(ret));
#endif
            res = false;
        }
    }
    return res;
}

bool pwm_channel_ctrl(uint8_t num, TimerOutChannel_t channel, bool on) {
    bool res = false;
    if(on) {
        res = pwm_channel_start(num, (TimerOutChannel_t)channel);
    } else {
        res = pwm_channel_stop(num, (TimerOutChannel_t)channel);
    }
    return res;
}

bool timer_oc_ctrl(uint8_t timer_num, TimerOutChannel_t channel, bool on) {
    bool res = false;
    if(on) {
        res = tim_oc_start(timer_num, (TimerOutChannel_t)channel);
    } else {
        res = tim_oc_stop(timer_num, (TimerOutChannel_t)channel);
    }
    return res;
}

bool pwm_ctrl_ll(PwmHandle_t* Node, bool on_off) {
    bool res = false;
#ifdef HAS_DIAG
    LOG_DEBUG(PWM, "PWM%u,%s", Node->num, OnOffToStr(on_off));
#endif
    if(Node) {
        if(on_off) {
            gpio_pad_mux_set(Node->Pad, Node->pin_mux);
        } else {
            gpio_pad_mux_set(Node->Pad, 0);
        }
        res = timer_channel_ctrl(Node->TimChan.timer, (TimerOutChannel_t)Node->TimChan.channel, on_off);
        if(res) {
            Node->mode = PwmOnOffToMode(on_off);
#ifdef HAS_DIAG
            LOG_PARN(PWM, "TIMER%u,%s,CtrlOk", Node->TimChan.timer, OnOffToStr(on_off));
#endif
        } else {
#ifdef HAS_DIAG
            LOG_DEBUG(PWM, "TIMER%u CtrlErr", Node->TimChan.timer);
#endif
            res = false;
        }
    }

    return res;
}

bool pwm_init_custom(void) {
    bool res = false;
    return res;
}

static bool pwm_init_compose(const PwmConfig_t* const Config, TIM_OC_InitTypeDef* const sConfig) {
    bool res = false;
    if(Config) {
        if(sConfig) {
            sConfig->OCMode = TIM_OCMODE_PWM1;
            sConfig->OCPolarity = PwmPolarityToStm32OCPolarity(Config->polarity);
            sConfig->OCNPolarity = TIM_OCNPOLARITY_HIGH;
            sConfig->OCFastMode = TIM_OCFAST_DISABLE;
            sConfig->Pulse = (0xFFFF / 3)-1;
            sConfig->OCIdleState = TIM_OCIDLESTATE_RESET;
            sConfig->OCNIdleState = TIM_OCNIDLESTATE_RESET;
            res = true;
        }
    }
    return res;
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle) {}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle) {}



bool pwm_init_one(uint8_t num) {
    bool res = false;
#ifdef HAS_DIAG
    LOG_INFO(PWM, "Init:%u", num);
#endif
    const PwmConfig_t* Config = PwmGetConfig(num);
    if(Config) {
        res = PwmIsValidConfig(Config);
        if(res) {
#ifdef HAS_DIAG
            LOG_WARNING(PWM, "%s", PwmConfigToStr(Config));
#endif
            PwmHandle_t* Node = PwmGetNode(num);
            if(Node) {
                res = pwm_init_common(Config, Node);
                TimerHandle_t* Timer = TimerGetNode(Config->TimChan.timer);
                if(Timer) {
                    res = pwm_init_compose(Config, &Node->ConfigOC);
                    uint32_t hal_channel = Channel2Code((TimerOutChannel_t)Config->TimChan.channel);
                    HAL_StatusTypeDef ret = HAL_TIM_PWM_ConfigChannel(&Timer->Handle, &Node->ConfigOC, hal_channel);
                    res = HAL_retToRes(ret);
                    if(res) {
                        res = pwm_frequency_set(num, Config->frequency_hz);
                        if(res) {
                            res = pwm_duty_set(num, Config->duty);
                            if(res) {
                                res = pwm_frequency_set(num, Config->frequency_hz);
                                res = pwm_duty_set(num, Config->duty);
                                res = pwm_ctrl(num, Config->on);
                            }
                        }
                    }
                    // res = timer_duty_set(Config->TimChan.timer, (TimerOutChannel_t) Config->channel, (float)
                    // Config->duty);
                }
            }
        }
    }
    return res;
}
