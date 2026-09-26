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

uint32_t buzzer_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(BuzzerConfig);
    cnt2 = ARRAY_SIZE(BuzzerInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
