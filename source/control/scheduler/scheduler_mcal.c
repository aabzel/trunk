#include "scheduler_mcal.h"

#include <inttypes.h>
#include <string.h>

#ifndef HAS_SCHEDULER
#error "need HAS_SCHEDULERS"
#endif /**/

#include "code_generator.h"
#include "data_utils.h"
#include "scheduler_list_all.h"
#include "system.h"

#ifdef HAS_LOG_UTILS
#include "table_utils.h"
//#include "writer.h"
#endif

#ifdef HAS_LIMITER
#include "limiter.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_SCHEDULER_DIAG
#include "scheduler_diag.h"
#endif

#ifdef HAS_SYSTIC
#include "systick.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

COMPONENT_GET_NODE(Scheduler, scheduler)

#ifdef HAS_SCHEDULER_CONFIG
COMPONENT_GET_CONFIG(Scheduler, scheduler)
#endif
bool scheduler_task_period_get(const uint8_t num, const uint32_t task_num, uint32_t* const task_period_us) {
    bool res = false;
    SchedulerHandle_t* Node = SchedulerGetNode(num);
    if(Node) {
        if(task_num < Node->task_array_cnt) {
            *task_period_us = (uint32_t)Node->TaskArray[task_num].period_us;
            res = true;
        }
    }
    return res;
}

bool scheduler_task_period_set(const uint8_t num, const uint32_t task_num, const uint32_t task_period_us) {
    bool res = false;
    SchedulerHandle_t* Node = SchedulerGetNode(num);
    if(Node) {
        if(task_num < Node->task_array_cnt) {
#ifdef HAS_LOG
            LOG_INFO(SCHEDULER, "SCHEDULER%u,Task:%s,SetPeriodUs:%u", num, TaskNumToName(num, task_num),
                     task_period_us);
#endif
            Node->TaskArray[task_num].period_us = (uint64_t)task_period_us;
            res = true;
        }
    }
    return res;
}

SchedulerTaskHandle_t* SchedulerNunToTaskNode(const uint8_t num, const uint8_t task_num) {
    SchedulerTaskHandle_t* TaskHandle = NULL;
    SchedulerHandle_t* Node = SchedulerGetNode(num);
    if(Node) {
        if(task_num < Node->task_array_cnt) {
            TaskHandle = &(Node->TaskArray[task_num]);
        }
    }
    return TaskHandle;
}

uint32_t scheduler_get_task_cnt(const uint8_t num) {
    uint32_t task_array_cnt = 0;
    const SchedulerHandle_t* Node = SchedulerGetNode(num);
    if(Node) {
        task_array_cnt = Node->task_array_cnt;
    }
    return task_array_cnt;
}

uint64_t scheduler_all_run_time_us(const uint8_t num) {
    uint64_t tot_run_time_us = UINT64_MAX;
    SchedulerHandle_t* Node = SchedulerGetNode(num);
    if(Node) {
        uint32_t t = 0;
        for(t = 0; t < Node->task_array_cnt; t++) {
            tot_run_time_us += Node->TaskArray[t].limiter.run_time_total_us;
        }
    }

    return tot_run_time_us;
}

#if 0
bool measure_scheduler_interval(uint16_t scheduler_id,
                                uint64_t period_us,
                                SchedulerFunc_t scheduler_func,
                                uint64_t loop_start_time_us) {
    bool res = false;
    if(SchedulerInstance[scheduler_id].limiter.on_off) {
        SchedulerInstance[scheduler_id].period_us = period_us;
        SchedulerInstance[scheduler_id].limiter.function = scheduler_func;
        res = limiter(&SchedulerInstance[scheduler_id].limiter, period_us, loop_start_time_us);
    }
    return res;
}
#endif

#ifdef HAS_SCHEDULER_EXT
static bool scheduler_is_equal(const SchedulerTaskHandle_t* const NodeA, const SchedulerTaskHandle_t* const NodeB) {
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

#ifdef HAS_SCHEDULER_EXT
static bool scheduler_is_uniq(SchedulerHandle_t* Node, const SchedulerTaskHandle_t* const Task) {
    bool res = false;
    uint32_t match = 0;
    uint32_t t = 0;
    for(t = 0; t < Node->task_array_cnt; t++) {
        res = scheduler_is_equal(&(Node->TaskArray[t]), Task);
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

static bool scheduler_init_one(const uint8_t num) {
    bool res = false;
    SchedulerHandle_t* Node = SchedulerGetNode(num);
    if(Node) {
#ifdef HAS_SCHEDULER_DIAG
        LOG_WARNING(SCHEDULER, "%s", SchedulerNodeToStr(Node));
#endif
        /*There shouldn't be a situation where there are no schedulers.*/
        while(0 == Node->task_array_cnt) {
        };

        uint32_t uniq_cnt = 0;
#ifdef HAS_LOG
        LOG_INFO(SCHEDULER, "SchedulersCnt %u", Node->task_array_cnt);
#endif
        if(Node->task_array_cnt) {
            uint32_t t = 0;
            for(t = 0; t < Node->task_array_cnt; t++) {
                res = true;
#ifdef HAS_SCHEDULER_EXT
                res = scheduler_is_uniq(Node, &Node->TaskArray[t]);
#endif
                if(res) {
                    Node->TaskArray[t].limiter.on_off = true;
                    Node->TaskArray[t].init = true;
#ifdef HAS_LIMITER
                    res = limiter_init(&Node->TaskArray[t].limiter, Node->TaskArray[t].period_us);
#endif

#ifdef HAS_SCHEDULER_DIAG
                    LOG_DEBUG(SCHEDULER, "SpotScheduler ID:%u, %s", t, SchedulerTaskToStr(&(Node->TaskArray[t])));
#endif
                    uniq_cnt++;
                } else {
#ifdef HAS_SCHEDULER_DIAG
                    LOG_ERROR(SCHEDULER, "DoubleScheduler %u,%s", t, SchedulerTaskToStr(&(Node->TaskArray[t])));
#endif
                }
            }

            if(uniq_cnt == Node->task_array_cnt) {
                res = true;
            } else {
                res = false;
#ifdef HAS_LOG
                LOG_ERROR(SCHEDULER, "DoubleSchedulers");
#endif
            }
        }
    }
    return res;
}

bool scheduler_proc_one_stamp(const uint8_t num, const uint64_t loop_start_time_us) {
    bool res = false;
    SchedulerHandle_t* Node = SchedulerGetNode(num);
    if(Node) {
        uint32_t t = 0;
        for(t = 0; t < Node->task_array_cnt; t++) {
            if(Node->TaskArray[t].limiter.on_off) {
                res = limiter(&Node->TaskArray[t].limiter, Node->TaskArray[t].period_us, loop_start_time_us);
            }
        }
    }
    return res;
}

static bool scheduler_init_custom(void) {
    bool res = false;
#ifdef HAS_LOG
    LOG_WARNING(SCHEDULER, "InitCustom");
#endif
    return res;
}

COMPONENT_INIT_PATTERT(SCHEDULER, SCHEDULER, scheduler)
// COMPONENT_PROC_PATTERT(SCHEDULER, SCHEDULER, scheduler)
