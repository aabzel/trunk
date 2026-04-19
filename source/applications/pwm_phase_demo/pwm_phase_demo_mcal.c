#include "pwm_phase_demo_mcal.h"

#include "pwm_mcal.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "time_mcal.h"
#include "log.h"

COMPONENT_GET_NODE(PwmPhaseDemo, pwm_phase_demo)
COMPONENT_GET_CONFIG(PwmPhaseDemo, pwm_phase_demo)

/*ISO-26262 require verify configuration*/
bool PwmPhaseDemoIsValidConfig(const PwmPhaseDemoConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(PWM_PHASE_DEMO, "%u,Name,Err", Config->num);
            res = false;
        }
        ifn(0.0f<Config->signal_amplitude) {
            LOG_ERROR(PWM_PHASE_DEMO, "%u,signal_amplitude,Err", Config->num);
            res = false;
        }
        ifn(0<Config->pwm_num) {
            LOG_ERROR(PWM_PHASE_DEMO, "%u,pwm_num,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool pwm_phase_demo_init_custom(void) {
    bool res = false;
    LOG_INFO(PWM_PHASE_DEMO, "Version:%u", PWM_PHASE_DEMO_VERSION);
    return res;
}

bool pwm_phase_demo_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(PWM_PHASE_DEMO, "Proc %u", i);
    PwmPhaseDemoHandle_t* Node = PwmPhaseDemoGetNode(i);
    if(Node) {
        float time_s = time_get_s(TIME_MAIN_NUM);
        float phase_deg = math_calc_sin_sample(  time_s, Node->signal_frequency, Node->signal_phase_ms, Node->signal_amplitude, Node->signal_offset);
        LOG_DEBUG(PWM_PHASE_DEMO, "PWM_PHASE_DEMO%u,T:%7.2f s,Signal,Pha:%f deg", i,time_s,phase_deg);
        res= pwm_phase_deg(Node->pwm_num,  phase_deg);
        Node->spin++;
    }
    return res;
}


bool pwm_phase_demo_init_common(const PwmPhaseDemoConfig_t* const Config, PwmPhaseDemoHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->pwm_num = Config->pwm_num;
            Node->num = Config->num;
            Node->signal_amplitude = Config->signal_amplitude;
            Node->signal_offset = Config->signal_offset;
            Node->signal_frequency = Config->signal_frequency;
            Node->signal_phase_ms = Config->signal_phase_ms;
            res = true;
        }
    }
    return res;
}


static bool pwm_phase_demo_init_node(PwmPhaseDemoHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->valid = true;
        res = true;
    }
    return res;
}


bool pwm_phase_demo_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(PWM_PHASE_DEMO, "PWM_PHASE_DEMO%u", num);
    const PwmPhaseDemoConfig_t* Config = PwmPhaseDemoGetConfig(num);
    if(Config) {
        res = PwmPhaseDemoIsValidConfig(Config);
        if(res) {
#ifdef HAS_PWM_PHASE_DEMO_DIAG
            LOG_WARNING(PWM_PHASE_DEMO, "%s", PwmPhaseDemoConfigToStr(Config));
#endif
            PwmPhaseDemoHandle_t* Node = PwmPhaseDemoGetNode(num);
            if(Node) {
                res = pwm_phase_demo_init_common(Config, Node);
                res = pwm_phase_demo_init_node(Node);
               // res = pwm_frequency_set(Node->pwm_num, Node->pwm_frequency_hz);
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(PWM_PHASE_DEMO, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(PWM_PHASE_DEMO, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(PWM_PHASE_DEMO, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(PWM_PHASE_DEMO, PWM_PHASE_DEMO, pwm_phase_demo)
COMPONENT_PROC_PATTERT(PWM_PHASE_DEMO, PWM_PHASE_DEMO, pwm_phase_demo)
