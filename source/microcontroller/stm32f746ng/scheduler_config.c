#include "scheduler_config.h"

#include "data_utils.h"
#include "scheduler_list_all.h"

SchedulerTaskHandle_t SchedulerTaskSet1[] = {SCHEDULER_CORE0_LIST_ALL};

#ifdef HAS_MULTICORE
SchedulerTaskHandle_t SchedulerTaskSet2[] = {SCHEDULER_CORE1_LIST_ALL};
SchedulerTaskHandle_t SchedulerTaskSet3[] = {SCHEDULER_CORE2_LIST_ALL};
#endif

#ifdef HAS_SCHEDULER_CONFIG

SchedulerTaskConfig_t SchedulerCfgTaskSet1[] = {SCHEDULER_CORE0_LIST_ALL};

#ifdef HAS_MULTICORE
SchedulerTaskConfig_t SchedulerCfgTaskSet2[] = {SCHEDULER_CORE1_LIST_ALL};
SchedulerTaskConfig_t SchedulerCfgTaskSet3[] = {SCHEDULER_CORE2_LIST_ALL};
#endif

const SchedulerConfig_t SchedulerConfig[] = {
    {
        .num = 1,
        .valid = true,
        .TaskArray = SchedulerCfgTaskSet1,
        .task_array_cnt = ARRAY_SIZE(SchedulerCfgTaskSet1),
    },

#ifdef HAS_MULTICORE

    {
        .num = 2,
        .valid = true,
        .TaskArray = SchedulerCfgTaskSet2,
        .task_array_cnt = ARRAY_SIZE(SchedulerCfgTaskSet2),
    },
    {
        .num = 3,
        .valid = true,
        .TaskArray = SchedulerCfgTaskSet3,
        .task_array_cnt = ARRAY_SIZE(SchedulerCfgTaskSet3),
    },
#endif
};
#endif

SchedulerHandle_t SchedulerInstance[] = {
    {
        .num = 1,
        .valid = true,
        .TaskArray = SchedulerTaskSet1,
        .task_array_cnt = ARRAY_SIZE(SchedulerTaskSet1),
    },

#ifdef HAS_MULTICORE

    {
        .num = 2,
        .valid = true,
        .TaskArray = SchedulerTaskSet2,
        .task_array_cnt = ARRAY_SIZE(SchedulerTaskSet2),
    },
    {
        .num = 3,
        .valid = true,
        .TaskArray = SchedulerTaskSet3,
        .task_array_cnt = ARRAY_SIZE(SchedulerTaskSet3),
    },
#endif
};

uint32_t scheduler_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    cnt1 = ARRAY_SIZE(SchedulerInstance);
    cnt = cnt1;
#ifdef HAS_SCHEDULER_CONFIG
    uint32_t cnt2 = 0;
    cnt2 = ARRAY_SIZE(SchedulerConfig);
    if(cnt1 == cnt2) {
        cnt = cnt1;
    }
#endif
    return cnt;
}
