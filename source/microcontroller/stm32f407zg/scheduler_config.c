#include "scheduler_config.h"

#include "data_utils.h"
#include "scheduler_list_all.h"

SchedulerTaskHandle_t SchedulerTaskSet1[] = {SCHEDULER_CORE0_LIST_ALL};

#ifdef HAS_SCHEDULER_CONFIG
SchedulerTaskConfig_t SchedulerCfgTaskSet1[] = {SCHEDULER_CORE0_LIST_ALL};
#endif

#ifdef HAS_SCHEDULER_CONFIG
const SchedulerConfig_t SchedulerConfig[] = {
    {
        .num = 1,
        .valid = true,
        .TaskArray = SchedulerCfgTaskSet1,
        .task_array_cnt = ARRAY_SIZE(SchedulerCfgTaskSet1),
    },
};
#endif

SchedulerHandle_t SchedulerInstance[] = {
    {
        .num = 1,
        .valid = true,
        .TaskArray = SchedulerTaskSet1,
        .task_array_cnt = ARRAY_SIZE(SchedulerTaskSet1),
    },

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
