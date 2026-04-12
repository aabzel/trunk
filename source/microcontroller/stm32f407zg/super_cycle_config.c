#include "super_cycle_config.h"

#include "super_cycle_config.h"
#include "time_mcal.h"
#ifdef HAS_DATA_MISC
#include "data_utils.h"
#endif

#ifndef HAS_SUPER_CYCLE
#error "Add HAS_SUPER_CYCLE"
#endif /**/

const SuperCycleConfig_t SECTION_CFG_DATA SuperCycleConfig[] = {

    {
        .max_duration_us = MSEC_2_USEC(100),
        .num = SUPER_CYCLE_CORE_0,
        .scheduler_num = 1,
        .valid = true,
    },
};

SuperCycleHandle_t SuperCycleInstance[] = {
    {
        .num = SUPER_CYCLE_CORE_0,
        .valid = true,
        .start_time_us = 0,
    },
};

COMPONENT_GET_CNT(SuperCycle, super_cycle)


