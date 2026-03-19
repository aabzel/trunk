#include "acc_config.h"

#include "data_utils.h"

const AccConfig_t AccConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "ACC1",
    },

};

AccHandle_t AccInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

uint32_t acc_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(AccConfig);
    cnt2 = ARRAY_SIZE(AccInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
