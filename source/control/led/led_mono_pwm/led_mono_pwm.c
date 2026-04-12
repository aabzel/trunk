#include "led_mono_pwm_mcal.h"

#include "code_generator.h"
#include "float_utils.h"
#include "gpio_mcal.h"
#include "led_drv.h"
#include "log.h"
#include "pwm_mcal.h"

static float led_mono_pwm_val_to_duty(const uint8_t val) {
    float duty = 0.0;
    switch(val) {
    case 0:
        duty = 10.0;
        break;
    case 1:
        duty = 90.0;
        break;
    default:
        duty = 0.0;
        break;
    }
    return duty;
}

static bool led_mono_pwm_init_common(const LedMonoPwmConfig_t* const Config, LedMonoPwmHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->pwm_num = Config->pwm_num;
            Node->Pad = Config->Pad;
            Node->duty_on = Config->duty_on;
            Node->duty_off = Config->duty_off;
            Node->color = Config->color;
            Node->name = Config->name;
            Node->phase_ms = Config->phase_ms;
            Node->group = Config->group;
            Node->on_time_ms = Config->on_time_ms;
            Node->period_ms = Config->period_ms;
            Node->duration_ms = Config->duration_ms;
            Node->mode = Config->mode;
            Node->num = Config->num;
            Node->duty = Config->duty;
            Node->active = Config->active;
            res = true;
        }
    }
    return res;
}

static bool led_mono_pwm_set_duty_ll(LedMonoPwmHandle_t* Node, float duty) {
    bool res = false;
    if(Node) {
        res = pwm_duty_set(Node->pwm_num, duty);
        res = pwm_ctrl(Node->pwm_num, true);
    }
    return res;
}

bool led_mono_pwm_set_duty(uint8_t num, float duty) {
    bool res = false;
    LedMonoPwmHandle_t* Node = LedMonoPwmGetNode(num);
    if(Node) {
        Node->mode=LED_MODE_HW_PWM;
        res = led_mono_pwm_set_duty_ll(Node, duty);

    }
    return res;
}


COMPONENT_GET_NODE(LedMonoPwm, led_mono_pwm)
COMPONENT_GET_CONFIG(LedMonoPwm, led_mono_pwm)

LedMonoPwmHandle_t* LedMonoPwmPadToNode(const Pad_t Pad) {
    LedMonoPwmHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = led_mono_pwm_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(Pad.byte == LedMonoPwmInstance[i].Pad.byte) {
            if(LedMonoPwmInstance[i].valid) {
                Node = &LedMonoPwmInstance[i];
                break;
            }
        }
    }
    return Node;
}

static bool led_mono_pwm_blink_ll(LedMonoPwmHandle_t* Node, uint32_t duration_ms) {
    bool res = false;
    if(Node && (0 < duration_ms)) {
        //Node->prev = GPIO_LVL_UNDEF;
#ifdef HAS_TIME
        Node->on_time_ms = time_get_ms32();
#endif
        Node->duration_ms = duration_ms;
        Node->prev_mode = Node->mode;
        Node->mode = LED_MODE_BLINK;
        //res = led_set_state_ll(Node, GPIO_LVL_HI);
    }
    return res;
}

bool led_mono_pwm_blink(uint8_t num, uint32_t duration_ms) {
    bool res = false;
#ifdef HAS_LOG
    LOG_DEBUG(LED_MONO_PWM, "LED_%u Blink %u ms", num, duration_ms);
#endif
    LedMonoPwmHandle_t* Node = LedMonoPwmGetNode(num);
    if(Node) {
        res = led_mono_pwm_blink_ll(Node, duration_ms);
    } else {
#ifdef HAS_LOG
        LOG_DEBUG(LED_MONO_PWM, "%u Blink,NodeErr", num);
#endif
    }
    return res;
}

bool led_mono_pwm_ctrl(const Pad_t Pad, const bool on_off) {
    bool res = false;
    LedMonoPwmHandle_t* Node = LedMonoPwmPadToNode(Pad);
    if(Node) {
        GpioLogicLevel_t volt = LedLogicLevel2Voltage(on_off, Node->active);
        res = gpio_logic_level_set(Pad, volt);
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool LedMonoPwmIsValidConfig(const LedMonoPwmConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            res = false;
            LOG_ERROR(LED_MONO_PWM, "%u,NameErr", Config->num);
        }
        ifn(Config->color) {
            res = false;
            LOG_ERROR(LED_MONO_PWM, "%u,color,Err", Config->num);
        }
    }
    return res;
}

bool led_mono_pwm_init_custom(void) {
    bool res = false;
    LOG_INFO(LED_MONO_PWM, "Version:%s", LED_MONO_PWM_VERSION);
    return res;
}

bool led_mono_pwm_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(LED_MONO_PWM, "Proc:%u", i);
    LedMonoPwmHandle_t* Node = LedMonoPwmGetNode(i);
    if(Node) {
        uint64_t time_us = 0;
#ifdef HAS_TIME
        time_us = time_get_us();
        Node->cur_time_ms = (uint32_t)(time_us / 1000);
#else
        Node->cur_time_ms++;
        time_us = Node->cur_time_ms;
#endif /*HAS_TIME*/
        float duty = 0.0;
        switch(Node->mode) {
        case LED_MODE_OFF: {
            duty = 10.0;
            res = true;
        } break;
        case LED_MODE_ON: {
            duty = 90.0;
            res = true;
        } break;
        case LED_MODE_SW_PWM: {
#ifdef HAS_MATH
            uint8_t val = calc_pwm_sample_num(time_us, Node->period_ms, Node->duty, Node->phase_ms);
#else
            uint8_t val = led_calc_pwm_sample_num((int32_t)time_us, Node->period_ms, Node->duty);
#endif
            duty = led_mono_pwm_val_to_duty(val);
            res = true;
        } break;
        case LED_MODE_BLINK: {
            uint32_t cur_duration_ms = 0;
            cur_duration_ms = Node->cur_time_ms - Node->on_time_ms;
            if(Node->duration_ms < cur_duration_ms) {
                res = true;
                duty = 10.0;
                const LedMonoPwmConfig_t* Config = LedMonoPwmGetConfig(Node->num);
                if(Config) {
                    Node->mode = Config->mode;
                }
            } else {
                duty = 90.0;
            }
        } break;

        case LED_MODE_SIGMA_DELTA: {
        } break;

        case LED_MODE_BAM: {
        } break;

        case LED_MODE_HW_PWM: {
            res = false ;
        } break;

        default: {
            res = false ;
        } break;
        } // switch(Node->mode)

        if(res) {
            res = is_floats_equal(duty, Node->prev_duty);
            if(!res) {
#ifdef HAS_GPIO_DIAG
                LOG_NOTICE(LED_MONO_PWM, "%s NewVal: %f", GpioPadToStr(Node->Pad), duty);
#endif
                res = led_mono_pwm_set_duty_ll(Node, duty);
            }
        }
        Node->prev_duty = duty;
        Node->spin++;
    }
    return res;
}

bool led_mono_pwm_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LED_MONO_PWM, "LED_MONO_PWM%u", num);
    const LedMonoPwmConfig_t* Config = LedMonoPwmGetConfig(num);
    if(Config) {
        res = LedMonoPwmIsValidConfig(Config);
        if(res) {
#ifdef HAS_LED_MONO_PWM_DIAG
            LOG_WARNING(LED_MONO_PWM, "%s", LedMonoPwmConfigToStr(Config));
#endif
            LedMonoPwmHandle_t* Node = LedMonoPwmGetNode(num);
            if(Node) {
                res = led_mono_pwm_init_common(Config, Node);
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(LED_MONO_PWM, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(LED_MONO_PWM, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(LED_MONO_PWM, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(LED_MONO_PWM, LED_MONO_PWM, led_mono_pwm)
COMPONENT_PROC_PATTERT(LED_MONO_PWM, LED_MONO_PWM, led_mono_pwm)
