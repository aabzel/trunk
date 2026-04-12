#ifndef SCHEDULER_MCAL_H
#define SCHEDULER_MCAL_H

/*some cooperative RTOS implementation*/
/*Mainly for NoRtos builds except RTOSBareBone build*/
#include "std_includes.h"
#ifdef HAS_MISCELLANEOUS
//#include "data_utils.h"
#endif
#include "scheduler_config.h"
#include "scheduler_types.h"
#include "scheduler_diag.h"

#ifndef HAS_SCHEDULER
#error "need HAS_SCHEDULER"
#endif /*HAS_SCHEDULERS*/

#ifdef HAS_LOG_UTILS
#include "oprintf.h"
#endif

#include "limiter_types.h"

/*API*/
SchedulerHandle_t* SchedulerGetNode(uint8_t num);
bool scheduler_proc_one_stamp(const uint8_t num, const uint64_t loop_start_time_us);
SchedulerTaskHandle_t* SchedulerNunToTaskNode(const uint8_t num,
                                              const uint8_t task_num);

bool scheduler_mcal_init(void);

#ifdef HAS_SCHEDULER_CONFIG
const SchedulerConfig_t* SchedulerGetConfig(uint8_t num);
#endif
uint32_t scheduler_get_task_cnt(const uint8_t num);

//bool measure_scheduler_interval(uint16_t scheduler_id, uint64_t interval_us, SchedulerFunc_t scheduler_func, uint64_t loop_start_time_us);
/*setters*/
uint64_t scheduler_all_run_time_us(const uint8_t num);
bool scheduler_task_period_set(const uint8_t num, const uint32_t task_num, const uint32_t task_period_us);

/*getters*/
bool scheduler_task_period_get(const uint8_t num, const uint32_t task_num, uint32_t* const task_period_us) ;

#endif /* SCHEDULER_MCAL_H */
