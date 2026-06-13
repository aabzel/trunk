#include "smooth_lamp_config.h"

#include "pwm_config.h"
#include "data_utils.h"


const SmoothLampConfig_t SmoothLampConfig[] = {
    {
        .pid_num = 1,
        .delta_sigma_num = 1,
        .num = 1,
        .valid = true,
        .lamp_type = SMOOTH_LAPM_TYPE_PWM,
        .type_num = PWM_NUM_DRV8870_CH1_IN1,
        //.mult = 0.01,
        .scale = 0.95,// slm 1 0.02
        .logistic_shift_s = 5.0f,
        .limit_up = 40.0f,
        .limit_down = 0.0f,
        .sample_rate_hz = 1000.0f,
        .pwm_freq_hz = 400.0f,
        .cmd = SMOOTH_LAPM_CMD_ON,
        .name = "BikeLamp",
    },
#if 0
    {
        .num = 2,
        .valid = true,
        .lamp_type = SMOOTH_LAPM_TYPE_PWM,
        .type_num = 1,
        .mult = 0.01,
        .limit_up = 100.0,
        .limit_down = 0.0,
        .sample_rate_hz = 1000.0,
        .pwm_freq_hz = 400.0,
        .cmd = SMOOTH_LAPM_CMD_OFF,
        .name = "CarLamp",
    },
    {
        .num = 2,
        .valid = true,
        .lamp_type = SMOOTH_LAPM_TYPE_DRV8870,
        .type_num = 1,
        .mult = 0.01,
        .limit_up = 100.0,
        .limit_down = 0.0,
        .sample_rate_hz = 1000.0,
        .pwm_freq_hz = 15000.0,
        .cmd = SMOOTH_LAPM_CMD_OFF,
        .lamp_type = SMOOTH_LAPM_TYPE_DRV8870,
        .name = "BikeLamp",
    },
#endif
};

SmoothLampHandle_t SmoothLampInstance[] = {
    {        .num = 1,        .valid = true,    },
   // {        .num = 2,        .valid = true,    },
};

uint32_t smooth_lamp_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SmoothLampConfig);
    cnt2 = ARRAY_SIZE(SmoothLampInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
