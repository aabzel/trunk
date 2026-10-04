#include "buzzer_config.h"

#include "data_utils.h"

const BuzzerConfig_t BuzzerConfig[] = {
    {
        .num = 1,
        .valid = true,
        .pwm_num = 6,
        .pwm_freq_hz = 3500.0,
        .Pad = {.port = PORT_E, .pin=5,},
        .name = "BUZZER1",
    },

};

BuzzerHandle_t BuzzerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(Buzzer, buzzer)
