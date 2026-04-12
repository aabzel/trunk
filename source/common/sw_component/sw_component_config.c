#include "sw_component_config.h"

#include "data_utils.h"

const SwComponentConfig_t SwComponentConfig[] = {
    {
        .num = 1,
        .valid = true,
        .name = "SW_COMPONENT1",
    },

    {
        .num = 2,
        .valid = true,
        .name = "SW_COMPONENT2",
    },
};

SwComponentHandle_t SwComponentInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },

};

uint32_t sw_component_get_cnt(void) {
    uint8_t cnt1 = 0;
    uint8_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SwComponentConfig);
    cnt2 = ARRAY_SIZE(SwComponentInstance);
    if(cnt2 == cnt1) {
    }
    return cnt1;
}
