#include "pwm_phase_demo_config.h"

#include "data_utils.h"

const PwmPhaseDemoConfig_t PwmPhaseDemoConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "PWM_PHASE_DEMO1",
        .signal_amplitude=180.0f,
        .signal_offset=180.0f ,
        .signal_frequency=0.2f ,
        .pwm_num=3,
    },
};

PwmPhaseDemoHandle_t PwmPhaseDemoInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(PwmPhaseDemo, pwm_phase_demo)


