#ifndef TASK_INFO_H
#define TASK_INFO_H

/*Mainly for NoRtos builds except RTOSBareBone build*/
#include "std_includes.h"
#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif
#include "task_types.h"

#ifndef HAS_TASK
#error "need HAS_TASK"
#endif /*HAS_TASKS*/


#ifdef HAS_LOG_UTILS
#include "oprintf.h"
#endif


#include "limiter_types.h"
#include "task_config.h"

/*some cooperative RTOS implementation*/

extern TaskConfig_t TaskInstance[];

uint64_t task_all_run_time_us(void);
uint16_t task_get_cnt(void);
bool task_init(void);
bool measure_task_interval(uint16_t task_id, uint64_t interval_us, TaskFunc_t task_func, uint64_t loop_start_time_us);
bool tasks_init(void);
bool tasks_proc(uint64_t loop_start_time_us);


#endif /* TASK_INFO_H */
