#ifndef SCHEDULER_CONFIG_H
#define SCHEDULER_CONFIG_H

#include "scheduler_types.h"

extern SchedulerTaskHandle_t SchedulerTaskSet1[];

extern SchedulerHandle_t SchedulerInstance[];

uint32_t scheduler_get_cnt(void);
uint32_t scheduler_task_get_cnt(void);


#endif /*SCHEDULER_CONFIG_H*/
