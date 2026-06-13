#include "encoder_lamp_mcal.h"

#include "pid.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "incremental_encoder_mcal.h"
#include "log.h"
#include "pwm_mcal.h"

#ifdef HAS_DELTA_SIGMA
#include "delta_sigma.h"
#endif

COMPONENT_GET_NODE(EncoderLamp, encoder_lamp)
COMPONENT_GET_CONFIG(EncoderLamp, encoder_lamp)

bool encoder_lamp_init_common(const EncoderLampConfig_t* const Config, EncoderLampHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->pid_num = Config->pid_num;
            Node->pwm_num = Config->pwm_num;
            Node->delta_sigma_num = Config->delta_sigma_num;
            Node->encoder_num = Config->encoder_num;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

/*ISO-26262 require verify configuration*/
bool EncoderLampIsValidConfig(const EncoderLampConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(ENCODER_LAMP, "ENCODER_LAMP_%u,Name,Err", Config->num);
            res = false;
        }

        res = incremental_encoder_is_valid(Config->pwm_num);
        ifn(res) {
            LOG_ERROR(ENCODER_LAMP, "ENCODER_LAMP_%u,IncEncNum,Err", Config->num);
            res = false;
        }

        res = pwm_is_valid(Config->encoder_num);
        ifn(res) {
            LOG_ERROR(ENCODER_LAMP, "ENCODER_LAMP_%u,PwmNum,Err", Config->num);
            res = false;
        }

        ifn(0.0f < Config->pwm_frequency_hz) {
            LOG_ERROR(ENCODER_LAMP, "ENCODER_LAMP_%u,pwm_frequency_hz,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool encoder_lamp_init_custom(void) {
    bool res = false;
    LOG_INFO(ENCODER_LAMP, "Version:%u", ENCODER_LAMP_VERSION);
    return res;
}

bool encoder_lamp_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(ENCODER_LAMP, "ENCODER_LAMP_%u,Proc", num);
    EncoderLampHandle_t* Node = EncoderLampGetNode(num);
    if(Node) {
        Node->duty = incremental_encoder_get_counter_limited(Node->encoder_num);
        if(Node->duty != Node->duty_prev) {

            float set_duty = ((float)Node->duty) / 16.0f;


            LOG_DEBUG(ENCODER_LAMP, "ENCODER_LAMP_%u,Duty:%f %%", num, set_duty);
            res = pid_target_set(Node->pid_num, set_duty);
#if 0
            res = pwm_duty_set(Node->pwm_num, set_duty);
            res = pwm_ctrl(Node->pwm_num, true);

            res = delta_sigma_target_set(Node->delta_sigma_num, set_duty);
#endif
        }
        Node->spin++;
        Node->duty_prev = Node->duty;
    }
    return res;
}

bool encoder_lamp_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(ENCODER_LAMP, "ENCODER_LAMP_%u", num);
    const EncoderLampConfig_t* Config = EncoderLampGetConfig(num);
    res = EncoderLampIsValidConfig(Config);
    if(res) {
#ifdef HAS_ENCODER_LAMP_DIAG
        LOG_WARNING(ENCODER_LAMP, "%s", EncoderLampConfigToStr(Config));
#endif
        EncoderLampHandle_t* Node = EncoderLampGetNode(num);
        if(Node) {
            res = encoder_lamp_init_common(Config, Node);
            res = pwm_frequency_set(Config->pwm_num, Config->pwm_frequency_hz);
            Node->valid = true;
            Node->init = true;
        } else {
            LOG_ERROR(ENCODER_LAMP, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(ENCODER_LAMP, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(ENCODER_LAMP, ENCODER_LAMP, encoder_lamp)
COMPONENT_PROC_PATTERT(ENCODER_LAMP, ENCODER_LAMP, encoder_lamp)
