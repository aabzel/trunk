#ifndef SCHEDULER_LIST_ALL_H
#define SCHEDULER_LIST_ALL_H

#ifdef HAS_APPLICATIONS
#include "applications_tasks.h"
#else
#define APPLICATIONS_TASKS
#endif

#ifdef HAS_ASICS
#include "asics_tasks.h"
#else
#define ASICS_TASK
#endif

#ifdef HAS_BOARD
#include "board_task.h"
#else
#define BOARD_TASKS
#endif

#ifdef HAS_COMPUTING
#include "computing_tasks.h"
#else
#define COMPUTING_TASKS
#endif

#ifdef HAS_CONNECTIVITY
#include "connectivity_tasks.h"
#else
#define CONNECTIVITY_TASKS
#endif

#ifdef HAS_CONTROL
#include "control_tasks.h"
#else
#define SCHEDULER_CONTROL
#endif

#ifdef HAS_WATCHDOG_PROC
#include "watchdog_mcal.h"
#define SCHEDULER_WATCHDOG {.name="iWDG", .period_us=WATCHDOG_POLL_PERIOD_US, .limiter.function = watchdog_proc,},
#else
#define SCHEDULER_WATCHDOG
#endif

#ifdef HAS_MCAL
#include "mcal_tasks.h"
#else
#define MCAL_TASKS
#endif

#ifdef HAS_SENSITIVITY
#include "sensitivity_tasks.h"
#else
#define SENSITIVITY_TASKS
#endif

#ifdef HAS_CORE
#include "core_tasks.h"
#else
#define CORE_TASKS
#endif

#ifdef HAS_STORAGE
#include "storage_tasks.h"
#else
#define STORAGE_TASKS
#endif

#ifdef HAS_THIRD_PARTY
#include "third_party_tasks.h"
#else
#define THIRD_PARTY_TASKS
#endif

#define SCHEDULER_CORE      \
    SCHEDULER_WATCHDOG

#define SCHEDULERS_BASE_SCHEDULERS         \
    BOOT_SCHEDULER                         \
    CLI_TASK                               \
    FLASH_FS_TASK                          \
    CORE_TASKS                             \
    HEAL_MON_TASK

#define SCHEDULER_CORE0_LIST_ALL     \
    ASICS_TASK                       \
    APPLICATIONS_TASKS               \
    BOARD_TASKS                      \
    CORE_TASKS                       \
    COMPUTING_TASKS                  \
    CONNECTIVITY_TASKS               \
    CONTROL_TASKS                    \
    MCAL_TASKS                       \
    SENSITIVITY_TASKS                \
    SCHEDULER_CORE                   \
    STORAGE_TASKS                    \
    THIRD_PARTY_TASKS

#ifdef HAS_MULTICORE

#define SCHEDULER_CORE1_LIST_ALL     \
    STRING_READER2_TASK              \
    MAILBOX2_TASK                    \
    LED_MONO_SET2_TASK

#define SCHEDULER_CORE2_LIST_ALL     \
    STRING_READER3_TASK              \
    MAILBOX3_TASK                    \
    LED_MONO_SET3_TASK
#endif

#endif /* SCHEDULER_LIST_ALL_H */
