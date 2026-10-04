#include "drv8870_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "float_utils.h"
#include "log.h"
#include "pwm_mcal.h"

COMPONENT_GET_NODE(Drv8870, drv8870)
COMPONENT_GET_CONFIG(Drv8870, drv8870)

/*ISO-26262 require verify configuration*/
bool Drv8870IsValidConfig(const Drv8870Config_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(Config->name) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(DRV8870, "%u,NameErr", Config->num);
            }
        }
    }
    return res;
}

bool drv8870_init_custom(void) {
    bool res = false;
    LOG_WARNING(DRV8870, "Version:%s", DRV8870_VERSION);
    return res;
}

bool drv8870_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(DRV8870, "Proc %u", i);
    Drv8870Handle_t* Node = Drv8870GetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

static bool drv8870_init_common(const Drv8870Config_t* const Config, Drv8870Handle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->pwm_frequency_hz = Config->pwm_frequency_hz;
            Node->in1_pwm_num = Config->in1_pwm_num;
            Node->in2_pwm_num = Config->in2_pwm_num;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool drv8870_deploy(uint8_t num) {
    bool res = false;
    Drv8870Handle_t* Node = Drv8870GetNode(num);
    if(Node) {
        res = pwm_ctrl(Node->in1_pwm_num, false);
        res = pwm_ctrl(Node->in2_pwm_num, false);

        res = pwm_frequency_set(Node->in1_pwm_num, Node->pwm_frequency_hz);
        res = pwm_frequency_set(Node->in2_pwm_num, Node->pwm_frequency_hz);
        switch(Node->mode) {
        case DRV8870_MODE_BRAKE: {
            res = pwm_duty_set(Node->in1_pwm_num, 100.0);
            res = pwm_duty_set(Node->in2_pwm_num, 100.0);
        } break;
        case DRV8870_MODE_FORWARD: {
            res = pwm_duty_set(Node->in1_pwm_num, Node->duty);
            res = pwm_duty_set(Node->in2_pwm_num, 0.0);
        } break;
        case DRV8870_MODE_REVERSE: {
            res = pwm_duty_set(Node->in1_pwm_num, 0.0);
            res = pwm_duty_set(Node->in2_pwm_num, Node->duty);
        } break;
        case DRV8870_MODE_HI_Z: {
            res = pwm_duty_set(Node->in1_pwm_num, 0.0);
            res = pwm_duty_set(Node->in2_pwm_num, 0.0);
        } break;
        default: {
            res = false;
        } break;
        }
        res = pwm_ctrl(Node->in1_pwm_num, true);
        res = pwm_ctrl(Node->in2_pwm_num, true);
        LOG_DEBUG(DRV8870, "%s", Drv8870NodeToStr(Node));
    }
    return res;
}

bool drv8870_freq_set(uint8_t num, float freq_hz) {
    bool res = false;
    Drv8870Handle_t* Node = Drv8870GetNode(num);
    if(Node) {
        Node->pwm_frequency_hz = freq_hz;
        res = drv8870_deploy(num);
    }
    return res;
}

bool drv8870_set(uint8_t num, Drv8870Mode_t mode, float duty) {
    bool res = false;
    Drv8870Handle_t* Node = Drv8870GetNode(num);
    if(Node) {
        // TODO limit
        Node->duty = float_limiter2(0.0, duty, 100.0);
        Node->mode = mode;
        res = drv8870_deploy(num);
    }
    return res;
}

bool drv8870_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DRV8870, "DRV8870%u", num);
    const Drv8870Config_t* Config = Drv8870GetConfig(num);
    if(Config) {
        res = Drv8870IsValidConfig(Config);
        if(res) {
#ifdef HAS_DRV8870_DIAG
            LOG_WARNING(DRV8870, "%s", Drv8870ConfigToStr(Config));
#endif
            Drv8870Handle_t* Node = Drv8870GetNode(num);
            if(Node) {
                res = drv8870_init_common(Config, Node);
                res = pwm_frequency_set(Node->in1_pwm_num, Config->pwm_frequency_hz);
                res = pwm_frequency_set(Node->in2_pwm_num, Config->pwm_frequency_hz);
                res = pwm_duty_set(Node->in1_pwm_num, 0.0);
                res = pwm_duty_set(Node->in2_pwm_num, 0.0);
                Node->mode = DRV8870_MODE_BRAKE;
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(DRV8870, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(DRV8870, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(DRV8870, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(DRV8870, DRV8870, drv8870)
COMPONENT_PROC_PATTERT(DRV8870, DRV8870, drv8870)
