#include "pwm_drv.h"

#include <string.h>

#include "code_generator.h"
#include "log.h"
#include "pwm_config.h"

bool pwm_init_cache(const PwmConfig_t* const Config, PwmHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {

            memcpy(Node->pad, Config->pad, sizeof(Config->pad));
            Node->phase_us = Config->phase_us;
            Node->Channel = Config->Channel;
            Node->duty = Config->duty;
            Node->on = Config->on;
            Node->channel_cnt = Config->channel_cnt;
            Node->frequency_hz = Config->frequency_hz;
            res = true;
        }
    }
    return res;
}

COMPONENT_IS_VALID(Pwm, pwm)

COMPONENT_GET_NODE(Pwm, pwm)

COMPONENT_GET_CONFIG(Pwm, pwm)

COMPONENT_INIT_PATTERT(PWM, PWM, pwm)
