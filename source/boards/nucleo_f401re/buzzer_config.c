#include "buzzer_config.h"

#include "data_utils.h"

const BuzzerConfig_t BuzzerConfig[] = {
    {
        .num = 1,
        .valid = true,
        .mode = BUZZER_MODE_COUNTER,
#ifdef HAS_PWM
        .pwm_num = 6,
        .pwm_freq_hz = 3500.0,
#endif
        .Pad = {.port = PORT_A, .pin=15,},
        .name = "BUZZER1[CN7.17]",
    },
};

BuzzerHandle_t BuzzerInstance[] = {
    {        .num = 1,   
         .valid = true,    },
};

COMPONENT_GET_CNT(Buzzer, buzzer)
