#include "pid.h"

#include "float_utils.h"
#include "code_generator.h"
#include "common_diag.h"
#include "log.h"
#include "utils_math.h"
#include "time_mcal.h"
#include "utils_math.h"

#ifdef HAS_PWM_DAC
#include "pwm_dac.h"
#endif

#ifdef HAS_ADC
#include "adc_mcal.h"
#endif

COMPONENT_GET_CONFIG(Pid, pid)

COMPONENT_GET_NODE(Pid, pid)

static bool pid_init_node(const PidConfig_t* const Config, PidHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->target = Config->target;
            Node->name = Config->name;
            Node->manual = Config->manual;
            Node->period_s = Config->period_s;
            Node->adc_channel_num = Config->adc_channel_num;
            Node->pwm_dac_num = Config->pwm_dac_num;
            Node->units = Config->units;
            Node->on = Config->on;
            Node->p = Config->p;
            Node->i = Config->i;
            Node->d = Config->d;
            res = true;
        }
    }
    return res;
}

static bool pid_reset_node(PidHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->error_sum = 0.0;
        Node->error_prev = 0.0;
        Node->error_diff = 0;
        Node->read = 0.0;
        Node->target = 0.0;
        Node->next_us = 0;
        Node->valid = true;
        res = true;
    }
    return res;
}

bool pid_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        if(on_off) {
            //log_level_get_set(PID, LOG_LEVEL_ERROR);
        } else {
            log_level_get_set(PID, LOG_LEVEL_INFO);
        }
        Node->on = on_off;
        LOG_INFO(PID, "PID:%u,%s", num, OnOffToStr(on_off));
        res = true;
    } else {
        LOG_ERROR(PID, "NodeErr,PID%u", num);
    }
    return res;
}

bool pid_set_p(uint8_t num, float p) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        LOG_INFO(PID, "PID:%u,Set,P:%f", num, p);
        Node->p = p;
        res = true;
    } else {
        LOG_ERROR(PID, "NodeErr,PID%u", num);
    }
    return res;
}

bool pid_set_i(uint8_t num, float i) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        LOG_INFO(PID, "PID:%u,Set,I:%f", num, i);
        Node->i = i;
        res = true;
    } else {
        LOG_ERROR(PID, "NodeErr,PID%u", num);
    }
    return res;
}

bool pid_set_d(uint8_t num, float d) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        LOG_INFO(PID, "PID:%u,Set,D:%f", num, d);
        Node->d = d;
        res = true;
    } else {
        LOG_ERROR(PID, "NodeErr,PID%u", num);
    }
    return res;
}

bool pid_target_set(uint8_t num, float target) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        res = is_float_equal_absolute(target, Node->target,0.0001);
        if(!res) {
            LOG_INFO(PID, "PID:%u,Set,Target:%f->%f", num, Node->target,target);
            Node->last_target = Node->target;
            Node->target = target;
            res = true;
        }
    } else {
        LOG_ERROR(PID, "NodeErr,PID%u", num);
    }
    return res;
}

static bool pid_proc_value_ll(PidHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->shift = Node->last_target - Node->out;
        Node->error_diff = (Node->error - Node->error_prev);
        Node->d_sum = 0.0f;
        if(0.0<Node->error) {
            Node->d_sum = MATH_MIN(fabsf(Node->shift),Node->error);
        }else {
            Node->d_sum = MATH_MAX(-fabsf(Node->shift),Node->error);
        }
        Node->error_sum += Node->d_sum;
        Node->error_prev = Node->error;
        if(false == Node->manual) {
            Node->out = 0.0f;
            Node->out += Node->p * Node->error;
            Node->out += Node->i * Node->error_sum;
            Node->out += Node->d * Node->error_diff;
        }
        LOG_DEBUG(PID, "%s", PidNodeToStr(Node));
        res = true;
    }
    return res;
}

bool pid_manual(uint8_t num, bool on_off, float value) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        Node->manual = on_off;
        if(on_off) {
            Node->out = value;
        }
        LOG_DEBUG(PID, "Manual:%s", PidNodeManualToStr(Node));
        res = true;
    }
    return res;
}

bool pid_proc_value_lll(PidHandle_t* Node, float error, float* const voltage_out) {
    bool res = false;
    Node->error = error;
    res = pid_proc_value_ll(Node);
    if (voltage_out) {
        *voltage_out = Node->out;
        res = true;
    }
    //LOG_DEBUG(PID, "PID%u,Proc,[%s]", num, PidNodeToStr(Node));
    return res;
}

bool pid_proc_value(uint8_t num, float error, float* const voltage_out) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        res = pid_proc_value_lll( Node , error, voltage_out);
    } else {
        LOG_ERROR(PID, "NodeErr,PID%u", num);
    }
    return res;
}

static bool pid_init_custom(void) {
    bool res = true;
    return res;
}


static bool pid_init_one(uint8_t num) {
    bool res = false;
    const PidConfig_t* Config = PidGetConfig(num);
    if(Config) {
        LOG_WARNING(PID, "Init:%s", PidConfigToStr(Config));
        PidHandle_t* Node = PidGetNode(num);
        if(Node) {
            res = pid_init_node(Config, Node);
            res = pid_reset_node(Node);

            res = pid_target_set(num, 0.0);
            res = pid_ctrl(num, Config->on);

            Node->init = true;
            res = true;
        } else {
            LOG_ERROR(PID, "NodeErr,PID%u", num);
        }
    }

    return res;
}

COMPONENT_INIT_PATTERT(PID, PID, pid)

#ifdef HAS_PID_PROC
bool pid_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(PID, "Proc:%u", num);
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        if(Node->on) {
            uint64_t up_time_us = time_get_us();

            if(Node->next_us < up_time_us) {
                Node->next_us = up_time_us + Node->period_us;

                float voltage_scale = 0.0;
                res = AdcChannelGetVoltage(Node->adc_channel_num, &voltage_scale);
                if(res) {
                    Node->read = voltage_scale;
                    Node->error = Node->target - Node->read;
                    res = pid_proc_value_ll(Node);
                    res = pwm_dac_duty_set(Node->pwm_dac_num, Node->out);
                    res = true;
                    LOG_DEBUG(PID, "%s", PidNodeToStr(Node));
                } else {
                    LOG_PARN(PID, "WaitAdc:%u", Node->adc_channel_num);
                }
            }
        }
    }
    return res;
}

COMPONENT_PROC_PATTERT(PID, PID, pid)
#endif
