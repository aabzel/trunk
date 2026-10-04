#ifndef SCHEDULER_CONFIG_H
#define SCHEDULER_CONFIG_H

#include "scheduler_types.h"

#ifdef HAS_SCHEDULER_CONFIG
extern const SchedulerConfig_t SchedulerConfig[];
#endif

extern SchedulerHandle_t SchedulerInstance[];
extern SchedulerTaskHandle_t SchedulerTaskSet1[] ;

uint32_t scheduler_task_get_cnt(void);
uint32_t scheduler_get_cnt(void);

#endif /*SCHEDULER_CONFIG_H*/
