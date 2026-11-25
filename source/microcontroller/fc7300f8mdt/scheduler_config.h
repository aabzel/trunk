#ifndef SCHEDULER_CONFIG_H
#define SCHEDULER_CONFIG_H

#include "scheduler_types.h"

#ifdef HAS_SCHEDULER_CONFIG
extern const SchedulerConfig_t SchedulerConfig[];
#endif

extern SchedulerHandle_t SchedulerInstance[];

uint32_t scheduler_get_cnt(void);

#endif /*SCHEDULER_CONFIG_H*/
