#include "trng_config.h"

#include "data_utils.h"

const tRngConfig_t tRngConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "TRNG1",
    },

};

tRngHandle_t tRngInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t trng_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(tRngConfig);
    cnt2 = ARRAY_SIZE(tRngInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
