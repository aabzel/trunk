#include "clock_divider_config.h"

#include "data_utils.h"

const ClockDividerConfig_t ClockDividerConfig[] = {
    {
        .num = 1,
        .valid = true,
        .amp = 10,
        .divider = 2,
        .schmitt_trigger_num = 2,
    },
    {
        .num = 2,
        .valid = true,
        .amp = 10,
        .divider = 2,
        .schmitt_trigger_num = 3,
    },
};

ClockDividerHandle_t ClockDividerInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
    {
        .num = 2,
        .valid = true,
    },
};

uint32_t clock_divider_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(ClockDividerInstance);
    cnt2 = ARRAY_SIZE(ClockDividerConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
