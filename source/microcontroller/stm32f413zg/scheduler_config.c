#include "scheduler_config.h"

#include "scheduler_list_all.h"

#ifdef HAS_DATA_MISC
#include "data_utils.h"
#endif

SchedulerTaskHandle_t SchedulerTaskSet1[] = {SCHEDULER_CORE0_LIST_ALL};


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
    cnt = ARRAY_SIZE(SchedulerInstance);
    return cnt;
}
