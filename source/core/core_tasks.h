#ifndef CORE_TASKS_H
#define CORE_TASKS_H


#ifdef HAS_CORE_STACK_MONITOR_PROC
#include "core_driver.h"
#define STACK_MONITOR_TASK  {                        \
        .period_us = STACK_MONITOR_POLL_PERIOD_US,   \
        .limiter.function = core_stack_monitor_proc, \
        .name = "StackMo",                           \
    },
#else
#define STACK_MONITOR_TASK
#endif

#ifdef HAS_DWT_PROC
#include "dwt_mcal.h"
#define DWT_TASK  {                        \
          .period_us = DWT_POLL_PERIOD_US, \
          .limiter.function = dwt_proc,    \
          DWT_NAME                         \
    },
#else
#define DWT_TASK
#endif

#define CORE_TASKS       \
    STACK_MONITOR_TASK   \
    DWT_TASK


#endif /* CORE_TASKS_H */
