#include "task_info.h"

#include <inttypes.h>
#include <string.h>

#ifdef HAS_CLOCK
#include "clock.h" //TODO DEL
#endif

#ifdef HAS_LOG_UTILS
#include "table_utils.h"
#include "writer_generic.h"
#endif

#ifdef HAS_LIMITER
#include "limiter.h"
#endif

#ifndef HAS_TASK
#error "need HAS_TASKS"
#endif /*HAS_TASKS*/

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif
#include "system.h"
#ifdef HAS_TASK_DIAG
#include "task_diag.h"
#endif
#include "data_utils.h"

#ifdef HAS_SYSTIC
#include "systick.h"
#endif
#include "task_config.h"
#include "task_list_all.h"
#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

TaskConfig_t TaskInstance[] = {TASK_LIST_ALL};

uint16_t task_get_cnt(void) {
    uint16_t cnt = ARRAY_SIZE(TaskInstance);
    return cnt;
}

uint64_t task_all_run_time_us(void) {
    uint64_t tot_run_time_us = UINT64_MAX;
    uint16_t cnt = task_get_cnt();
    int32_t id = 0;
    for(id = 0; id < cnt; id++) {
        tot_run_time_us += TaskInstance[id].limiter.run_time_total_us;
    }

    return tot_run_time_us;
}

#if 0
bool measure_task_interval(uint16_t task_id,
		                   uint64_t period_us,
						   TaskFunc_t task_func,
		                   uint64_t loop_start_time_us) {
    bool res = false;
    if(TaskInstance[task_id].limiter.on_off) {
        TaskInstance[task_id].period_us = period_us;
        TaskInstance[task_id].limiter.function = task_func;
        res = limiter(&TaskInstance[task_id].limiter, period_us, loop_start_time_us);
    }
    return res;
}
#endif

#ifdef HAS_TASK_EXT
static bool task_is_equal(const TaskConfig_t* const NodeA, const TaskConfig_t* const NodeB) {
    bool res = false;
    if(NodeA->limiter.function == NodeB->limiter.function) {
        if(NodeA->period_us == NodeB->period_us) {
            int ret = strcmp(NodeA->name, NodeB->name);
            if(0 == ret) {
                res = true;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_TASK_EXT
static bool task_is_uniq(const TaskConfig_t* const Node) {
    bool res = false;
    uint32_t cnt = task_get_cnt();
    uint32_t t = 0;
    uint32_t match = 0;
    for(t = 0; t < cnt; t++) {
        res = task_is_equal(&TaskInstance[t], Node);
        if(res) {
            match++;
        }
        if(2 < match) {
            res = false;
            break;
        }
    }

    if(1 == match) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

bool tasks_init(void) {
    bool res = false;
    uint32_t cnt = task_get_cnt();
    /*There shouldn't be a situation where there are no tasks.*/
    while(0 == cnt) {
    };

    uint32_t uniq_cnt = 0;
#ifdef HAS_LOG
    LOG_INFO(SCHEDULER, "TasksCnt %u", cnt);
#endif
    if(cnt) {
        uint32_t t = 0;
        for(t = 0; t < cnt; t++) {
            TaskInstance[t].limiter.on_off = true;
            TaskInstance[t].init = true;

            res = true;
#ifdef HAS_TASK_EXT
            res = task_is_uniq(&TaskInstance[t]);
#endif
            if(res) {
#ifdef HAS_LIMITER
                res = limiter_init(&TaskInstance[t].limiter, TaskInstance[t].period_us);
#endif

#ifdef HAS_TASK_DIAG
                LOG_DEBUG(SCHEDULER, "SpotTask ID:%u, %s", t, TaskNode2Str(&TaskInstance[t]));
#endif
                uniq_cnt++;
            } else {
#ifdef HAS_TASK_DIAG
                LOG_ERROR(SCHEDULER, "DoubleTask %u,%s", t, TaskNode2Str(&TaskInstance[t]));
#endif
            }
        }

        if(uniq_cnt == cnt) {
            res = true;
        } else {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(SCHEDULER, "DoubleTasks");
#endif
        }
    }
    return res;
}

bool task_init(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(SCHEDULER, "TaskInit");
#endif
    res = tasks_init();
    return res;
}

bool tasks_proc(uint64_t loop_start_time_us) {
    bool res = false;
    uint32_t cnt = task_get_cnt();
    uint32_t t = 0;
    for(t = 0; t < cnt; t++) {
        if(TaskInstance[t].limiter.on_off) {
            res = limiter(&TaskInstance[t].limiter, TaskInstance[t].period_us, loop_start_time_us);
        }
    }
    return res;
}
