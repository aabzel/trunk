#include "encoder_lamp_config.h"

#include "data_utils.h"
#include "pwm_config.h"

const EncoderLampConfig_t EncoderLampConfig[] = {
    {
        .pwm_num = PWM_NUM_DRV8870_CH1_IN1,
        .pwm_frequency_hz = 150.0,
        .pid_num = 1,
        .encoder_num = 1,
        .delta_sigma_num = 1,
        .num = 1,
        .valid = true,
        .name = "EncoderLamp1",
    },
};

EncoderLampHandle_t EncoderLampInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(EncoderLamp, encoder_lamp)


