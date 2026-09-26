#include "probing_pulse_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_IS_VALID(ProbingPulse, probing_pulse)
COMPONENT_GET_NODE(ProbingPulse, probing_pulse)
COMPONENT_GET_CONFIG(ProbingPulse, probing_pulse)

/*ISO-26262 require verify configuration*/
bool ProbingPulseIsValidConfig(const ProbingPulseConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->sonar_signal_wav_name) {
            LOG_ERROR(PROBING_PULSE, "PROBING_PULSE_%u,sonar_signal_wav_name,Err", Config->num);
            res = false;
        }

        ifn(Config->name) {
            LOG_ERROR(PROBING_PULSE, "PROBING_PULSE_%u,name,Err", Config->num);
            res = false;
        }

        ifn(Config->zonding_impulse_type) {
            LOG_ERROR(PROBING_PULSE, "PROBING_PULSE_%u,zonding_impulse_type,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool probing_pulse_init_custom(void) {
    bool res = false;
    LOG_INFO(PROBING_PULSE, "Version:%u", PROBING_PULSE_VERSION);
    return res;
}

bool probing_pulse_init_common(const ProbingPulseConfig_t* const Config, ProbingPulseHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->amplitude = Config->amplitude;
            Node->signal_duration_s = Config->signal_duration_s;
            Node->frequency1 = Config->frequency1;
            Node->frequency2 = Config->frequency2;
            Node->periods_per_chip = Config->periods_per_chip;
            Node->zonding_impulse_type = Config->zonding_impulse_type;
            Node->sonar_signal_wav_name = Config->sonar_signal_wav_name;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool probing_pulse_init_node(ProbingPulseHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->tx_cnt = 0;
        Node->valid = true;
        res = true;
    }
    return res;
}

bool probing_pulse_init_one(uint8_t num) {
    bool res = false;
    const ProbingPulseConfig_t *Config = ProbingPulseGetConfig(num);
    res = ProbingPulseIsValidConfig(Config);
    if(res) {
#ifdef HAS_PROBING_PULSE_DIAG
        LOG_WARNING(PROBING_PULSE, "%s", ProbingPulseConfigToStr(Config));
#endif
        ProbingPulseHandle_t *Node = ProbingPulseGetNode(num);
        if(Node) {
            res = probing_pulse_init_common(Config, Node);
            res = probing_pulse_init_node(Node);
            Node->init = true;
            LOG_INFO(PROBING_PULSE, "PROBING_PULSE_%u,Init,Ok", num);
        } else {
            LOG_ERROR(PROBING_PULSE, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(PROBING_PULSE, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(PROBING_PULSE, PROBING_PULSE, probing_pulse)
