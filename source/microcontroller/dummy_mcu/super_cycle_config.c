#include "super_cycle_config.h"

#include "super_cycle_config.h"
#include "time_mcal.h"
#ifdef HAS_DATA_MISC
#include "data_utils.h"
#endif

#ifndef HAS_SUPER_CYCLE
#error "Add HAS_SUPER_CYCLE"
#endif /**/


const SuperCycleConfig_t SuperCycleConfig[] = {

    {
        .max_duration_us = MSEC_2_USEC(100),
        .num = SUPER_CYCLE_CORE_0,
        .scheduler_num = 1,
        .valid = true,
    },
#ifdef HAS_MULTICORE
    {
        .max_duration_us = MSEC_2_USEC(100),
        .num = SUPER_CYCLE_CORE_1,
        .scheduler_num = 2,
        .valid = true,
    },
#endif
};

SuperCycleHandle_t SuperCycleInstance[] = {
    {
        .num = SUPER_CYCLE_CORE_0,
        .valid = true,
        .start_time_us = 0,
    },
#ifdef HAS_MULTICORE
    {
        .num = SUPER_CYCLE_CORE_1,
        .valid = true,
        .start_time_us = 0,
    },
#endif
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
