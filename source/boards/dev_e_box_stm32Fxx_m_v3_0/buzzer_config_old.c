#include "buzzer_config.h"

#include "data_utils.h"

const BuzzerConfig_t BuzzerConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "BUZZER1",
    },

    {
        .num = 2,
        .valid = true,
        .name = "BUZZER2",
    },
};

BuzzerHandle_t BuzzerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
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
