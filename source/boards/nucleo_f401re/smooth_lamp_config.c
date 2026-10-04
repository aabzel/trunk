#include "smooth_lamp_config.h"

#include "data_utils.h"

const SmoothLampConfig_t SmoothLampConfig[] = {
    {
        .num = 1,
        .valid = true,
        .lamp_type = SMOOTH_LAPM_TYPE_PWM,
        .type_num = 7,
        .mult = 0.02,
        .limit_up = 100.0,
        .limit_down = 0.0,
        .sample_rate_hz = 1000.0,
        .pwm_freq_hz = 15000.0,
        .cmd = SMOOTH_LAPM_CMD_OFF,
        .name = "CarLamp",
    },
    {
        .num = 2,
        .valid = true,
        .lamp_type = SMOOTH_LAPM_TYPE_PWM,
        .type_num = 1,
        .mult = 0.01,
        .limit_up = 100.0,
        .limit_down = 0.0,
        .sample_rate_hz = 1000.0,
        .pwm_freq_hz = 15000.0,
        .cmd = SMOOTH_LAPM_CMD_OFF,
        .name = "CarLamp",
    },
#if 0
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
    {        .num = 2,        .valid = true,    },
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
