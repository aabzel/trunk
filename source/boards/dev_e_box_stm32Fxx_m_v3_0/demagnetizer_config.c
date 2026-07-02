#include "demagnetizer_config.h"

#include "data_utils.h"

const DeMagnetizerConfig_t DeMagnetizerConfig[] = {
    {
        .num = 1,
        .led_num = 1,
        .drv8870_num = 1,
        .duty = 50.0,
        .duty_dx = 0.5,
        .duration_s = 0.25,
        .decay_duration_s = 0.25/2.0,
        .pwm_frequency_hz = 500.0,
        .valid = true,
        .name = "DEMAGNETIZER1",
    },

};

DeMagnetizerHandle_t DeMagnetizerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },

};

uint32_t demagnetizer_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DeMagnetizerConfig);
    cnt2 = ARRAY_SIZE(DeMagnetizerInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
