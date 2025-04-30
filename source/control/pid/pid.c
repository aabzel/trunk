#include "pid.h"

#ifdef HAS_ADC
#include "adc_mcal.h"
#endif
#include "code_generator.h"
#include "common_diag.h"
#include "log.h"
#ifdef HAS_PWM_DAC
#include "pwm_dac.h"
#endif
#include "time_mcal.h"
#include "utils_math.h"

COMPONENT_GET_CONFIG(Pid, pid)

COMPONENT_GET_NODE(Pid, pid)

bool pid_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        if(on_off) {
#ifdef HAS_PWM
            log_level_get_set(PWM, LOG_LEVEL_ERROR);
            log_level_get_set(PWM_DAC, LOG_LEVEL_ERROR);
            log_level_get_set(TIMER, LOG_LEVEL_ERROR);
#endif


            log_level_get_set(PID, LOG_LEVEL_ERROR);
        } else {
#ifdef HAS_PWM
            log_level_get_set(PWM, LOG_LEVEL_INFO);
            log_level_get_set(PWM_DAC, LOG_LEVEL_INFO);
            log_level_get_set(TIMER, LOG_LEVEL_INFO);
#endif
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

bool pid_set_p(uint8_t num, double p) {
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

bool pid_set_i(uint8_t num, double i) {
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

bool pid_set_d(uint8_t num, double d) {
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

bool pid_target_set(uint8_t num, double target) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        LOG_DEBUG(PID, "PID:%u,Set,Target:%f", num, target);
        Node->target = target;
        res = true;
    } else {
        LOG_ERROR(PID, "NodeErr,PID%u", num);
    }
    return res;
}

static bool pid_proc_value_ll(PidHandle_t* const Node) {
    bool res = false;
    if(Node) {
            Node->out = 0.0;
            Node->error_diff = (Node->error - Node->error_prev);
            Node->error_sum += Node->i * Node->error;

            Node->out += Node->p * Node->error;
            Node->out += Node->error_sum;
            Node->out += Node->d * Node->error_diff;

            Node->error_prev = Node->error;
            LOG_DEBUG(PID, "%s", PidNodeToStr(Node));
            res = true;
    }
    return res;
}

bool pid_proc_value(uint8_t num, double error, double * const voltage_out) {
    bool res = false;
    PidHandle_t* Node = PidGetNode(num);
    if(Node) {
        Node->error = error;
        res = pid_proc_value_ll(Node) ;
        if(voltage_out) {
            *voltage_out = Node->out;
            res = true;
        }
        LOG_PARN(PID, "PID%u,Proc,In:%f,Out:%f", num, error, Node->out);
    } else {
        LOG_ERROR(PID, "NodeErr,PID%u", num);
    }
    return res;
}

static bool pid_init_custom(void) {
    bool res = true;
    return res;
}

static bool pid_init_node(const PidConfig_t* const Config, PidHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->period_us = Config->period_us;
            Node->adc_channel_num = Config->adc_channel_num;
            Node->pwm_dac_num = Config->pwm_dac_num;
            Node->unit = Config->unit;
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

                double voltage_scale = 0.0;
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
