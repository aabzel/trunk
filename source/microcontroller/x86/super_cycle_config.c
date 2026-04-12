#include "super_cycle_config.h"

#include "data_utils.h"

#ifndef HAS_SUPER_CYCLE
#error "Add HAS_SUPER_CYCLE"
#endif

const SuperCycleConfig_t SuperCycleConfig[] = {
    {
        .num = SUPER_CYCLE_CORE_0,
        .max_duration_us = 1000000,
        .scheduler_num = 1,
        .valid = true,
    },
};

SuperCycleHandle_t SuperCycleInstance[] = {
    {
        .num = SUPER_CYCLE_CORE_0,
        .start_time_us = 0,
        .valid = true,
    },
};

uint32_t super_cycle_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(SuperCycleInstance);
    cnt2 = ARRAY_SIZE(SuperCycleConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
    return cnt;
}
