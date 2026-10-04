#include "bts724g_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "ext_int_mcal.h"
#include "gpio_mcal.h"
#include "log.h"
#include "adc_channel_mcal.h"
#include "utils_math.h"
#include "pwm_mcal.h"

COMPONENT_GET_NODE(Bts724g, bts724g)
COMPONENT_GET_CONFIG(Bts724g, bts724g)

bool Bts724gIsValidConfigPwmMode(const Bts724gConfig_t* const Config) {
    bool out_res = false;
    if(Config) {
        bool res = false;
        out_res = true;

        ifn(CONTROL_MODE_PWM == Config->ctrl_mode) {
            LOG_ERROR(BTS724G, "%u,mode,Err", Config->num);
            out_res = false;
        }

        ifn(Config->pwm_num) {
            LOG_WARNING(BTS724G, "%u,pwm_num,Err", Config->num);
            out_res = false;
        }

        res = pwm_is_valid_duty_cycle(Config->duty);
        ifn(res) {
            LOG_WARNING(BTS724G, "%u,duty,Err", Config->num);
            out_res = false;
        }

        ifn(0.0 < Config->frequency_hz) {
            LOG_WARNING(BTS724G, "%u,frequency,Err", Config->num);
            out_res = false;
        }
    }
    return out_res;
}

/*ISO-26262 require verify configuration*/
bool Bts724gIsValidConfig(const Bts724gConfig_t* const Config) {
    bool out_res = false;
    if(Config) {
        bool res = false;
        out_res = true;
        ifn(Config->name) {
            LOG_ERROR(BTS724G, "%u,Name,Err", Config->num);
            out_res = false;
        }

        ifn(Config->con_name) {
            LOG_ERROR(BTS724G, "%u,conn,Err", Config->num);
            out_res = false;
        }

        ifn(Config->mode) {
            LOG_ERROR(BTS724G, "%u,mode,Err", Config->num);
            out_res = false;
        }

        ifn(Config->ctrl_mode) {
            LOG_ERROR(BTS724G, "%u,CrtlMode,Err", Config->num);
            out_res = false;
        }

        if(CONTROL_MODE_PWM == Config->ctrl_mode) {
            res = Bts724gIsValidConfigPwmMode(Config);
            ifn(res) { out_res = false; }
        }

        res = gpio_is_valid_pad(Config->pad_set);
        ifn(res) {
            LOG_WARNING(BTS724G, "%u,padSet,Err", Config->num);
            out_res = false;
        }

        ifn(Config->shared_num) { LOG_WARNING(BTS724G, "%u,shared_num,Err", Config->num); }
    }
    return out_res;
}

bool bts724g_set(uint8_t num, bool on_off) {
    bool res = false;
    Bts724gHandle_t* Node = Bts724gGetNode(num);
    if(Node) {
        switch(Node->ctrl_mode) {
        case CONTROL_MODE_GPIO: {
            res = gpio_logic_level_set(Node->pad_set, (GpioLogicLevel_t)on_off);
        } break;
        case CONTROL_MODE_PWM: {
            // res = pwm_freq_duty_set(Node->pwm_num, Node->frequency_hz, Node->duty);
            res = pwm_ctrl(Node->pwm_num, on_off);
        } break;
        default:
            break;
        }
    }
    return res;
}

bool bts724g_init_custom(void) {
    bool res = false;
    LOG_INFO(BTS724G, "Version:%u", BTS724G_VERSION);
    return res;
}

static bool bts724g_detect_fault_reason( Bts724gHandle_t * const Node){
    bool res = false;
    GpioLogicLevel_t ll = gpio_get_state_short(Node->pad_set);
    if(GPIO_LVL_LOW == ll) {
        LOG_WARNING(BTS724G, "OpenLoad,[%s]", Bts724gNodeToStrShort(Node));
    } else {
        // res = gpio_logic_level_set(Node->pad_set, GPIO_LVL_LOW);
        LOG_ERROR(BTS724G, "OverTemperature!,[%s]", Bts724gNodeToStrShort(Node));
    }
    return res;
}

bool bts724g_init_common(const Bts724gConfig_t* const Config, Bts724gHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->chip_id = Config->chip_id;
            Node->con_name = Config->con_name;
            Node->ctrl_mode = Config->ctrl_mode;
            Node->feedback_scaler = Config->feedback_scaler;
            Node->feedback_mode = Config->feedback_mode;
            Node->mode = Config->mode;
            Node->name = Config->name;
            Node->num = Config->num;
            Node->opposite_num = Config->opposite_num;
            Node->pwm_num = Config->pwm_num;
            Node->pad_set = Config->pad_set;
            Node->pad_diag = Config->pad_diag;
            Node->pad_feedback = Config->pad_feedback;
            Node->shared_num = Config->shared_num;
            res = true;
        }
    }
    return res;
}

bool bts724g_init_node(Bts724gHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->valid = true;
        Node->error_cnt = 0;
        Node->init = true;
        res = true;
    }
    return res;
}

bool bts724g_frequency_set(uint8_t num, float frequency_hz) {
    bool res = false;
    Bts724gHandle_t* Node = Bts724gGetNode(num);
    if(Node) {
        res = pwm_frequency_set(Node->pwm_num, frequency_hz);
    }
    return res;
}

bool bts724g_duty_set(uint8_t num, float duty_cycle) {
    bool res = false;
    Bts724gHandle_t* Node = Bts724gGetNode(num);
    if(Node) {
        res = pwm_duty_set(Node->pwm_num, duty_cycle);
    }
    return res;
}

bool bts724g_frequency_get(uint8_t num, float* const frequency_hz) {
    bool res = false;
    Bts724gHandle_t* Node = Bts724gGetNode(num);
    if(Node) {
        res = pwm_frequency_get(Node->pwm_num, frequency_hz);
    }
    return res;
}

bool bts724g_duty_get(uint8_t num, float* const duty_cycle) {
    bool res = false;
    Bts724gHandle_t* Node = Bts724gGetNode(num);
    if(Node) {
        res = pwm_duty_get(Node->pwm_num, duty_cycle);
    }
    return res;
}

bool bts724g_effective_get(const uint8_t num) {
    bool res = false;
    Bts724gHandle_t* Node = Bts724gGetNode(num);
    if(Node) {
        switch(Node->feedback_mode) {
            case BTS724G_FEEDBACK_MODE_GPIO:{
                GpioLogicLevel_t logic_level = gpio_get_state_short(Node->pad_feedback);
                res = (bool) logic_level;
            } break;

            case BTS724G_FEEDBACK_MODE_ADC:{
                float feedback_voltage = Node->feedback_scaler*adc_pad_read_voltage_short(Node->pad_feedback);
                res = math_comparator(feedback_voltage, BTS724G_HALF_MAX_OUT_VOLTAGE);
            } break;

            default:{
                float feedback_voltage = adc_pad_read_voltage_short(Node->pad_feedback);
                res = math_comparator(feedback_voltage, BTS724G_HALF_MAX_OUT_VOLTAGE);
            } break;
        }

    }
    return res;
}

bool bts724g_state_get(uint8_t num) {
    bool res = false;
    Bts724gHandle_t* Node = Bts724gGetNode(num);
    if(Node) {
        switch(Node->ctrl_mode) {
        case CONTROL_MODE_GPIO: {
            res = gpio_get_state_short(Node->pad_set);
        } break;
        case CONTROL_MODE_PWM: {
            res = pwm_is_work(Node->pwm_num);
        } break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

bool bts724g_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(BTS724G, "Proc:%u", num);
    Bts724gHandle_t *Node = Bts724gGetNode(num);
    if(Node) {
        if(Node->init) {
            GpioLogicLevel_t pad_diag_ll = gpio_get_state_short(Node->pad_diag);
            if(GPIO_LVL_LOW == pad_diag_ll) {
                if(Node->prev_pad_diag_ll != pad_diag_ll) {
                    /* Diagnostic feedback 1/2,3/4 of channel 1,2,3,4  open drain, low on failure */
                    LOG_DEBUG(BTS724G, "failure:[%s]", Bts724gNodeToStrShort(Node));
                    Node->error_cnt++;
                    res = bts724g_detect_fault_reason(Node);
                }
            }

            ExtIntHandle_t *IntPad = ExtIntPadToNode(Node->pad_diag);
            if(IntPad->falling_done) {
                LOG_DEBUG(BTS724G, "failure:[%s]", ExtIntNodeToStr(IntPad));
                IntPad->falling_done = false;
            }
            Node->prev_pad_diag_ll = pad_diag_ll;
            Node->spin++;
        }
    }
    return res;
}

bool bts724g_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(BTS724G, "BTS724G_%u", num);
    const Bts724gConfig_t* Config = Bts724gGetConfig(num);
    if(Config) {
        res = Bts724gIsValidConfig(Config);
        if(res) {
#ifdef HAS_BTS724G_DIAG
            LOG_WARNING(BTS724G, "Config:%s", Bts724gConfigToStr(Config));
#endif
            Bts724gHandle_t* Node = Bts724gGetNode(num);
            if(Node) {
                res = bts724g_init_common(Config, Node);
                res = bts724g_init_node(Node);
                LOG_INFO(BTS724G, "Init,Ok,%u", num);
                res = true;
            } else {
                LOG_ERROR(BTS724G, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(BTS724G, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(BTS724G, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(BTS724G, BTS724G, bts724g)
COMPONENT_PROC_PATTERT(BTS724G, BTS724G, bts724g)
