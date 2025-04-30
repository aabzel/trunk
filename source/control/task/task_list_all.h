#ifndef TASK_LIST_ALL_H
#define TASK_LIST_ALL_H

#ifdef HAS_APPLICATIONS
#include "applications_tasks.h"
#else /*HAS_APPLICATIONS*/
#define APPLICATIONS_TASKS
#endif /*HAS_APPLICATIONS*/

#ifdef HAS_ASICS
#include "asics_tasks.h"
#else
#define ASICS_TASK
#endif

#ifdef HAS_BOOTLOADER
#include "bootloader.h"
#define TASK_BOOTLOADER {.name="BOOTLOADER", .period_us=BOOTLOADER_PERIOD_US, .limiter.function=bootloader_proc,},
#else /*HAS_BOOTLOADER*/
#define TASK_BOOTLOADER
#endif /*HAS_BOOTLOADER*/


#ifdef HAS_BOARD
#include "board_task.h"
#else
#define BOARD_TASKS
#endif /**/

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
#define TASK_CONTROL
#endif

#ifdef HAS_GAMES
#include "games_tasks.h"
#else
#define GAMES_TASKS
#endif

#ifdef HAS_WATCHDOG_PROC
#include "watchdog_mcal.h"
#define TASK_WATCHDOG {.name="IWDG", .period_us=WATCHDOG_POLL_PERIOD_US, .limiter.function=watchdog_proc,},
#else
#define TASK_WATCHDOG
#endif /**/

#ifdef HAS_MULTIMEDIA
#include "multimedia_tasks.h"
#else
#define MULTIMEDIA_TASKS
#endif

#ifdef HAS_MCAL
#include "mcal_tasks.h"
#else
#define MCAL_TASKS
#endif

#ifdef HAS_SENSITIVITY
#include "sensitivity_tasks.h"
#else
#define TASK_SENSITIVITY
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

#define TASK_CORE      \
    TASK_WATCHDOG

#define TASKS_BASE_TASKS         \
    BOOT_TASK                    \
    CLI_TASK                     \
    FLASH_FS_TASK                \
    HEAL_MON_TASK

#define TASK_LIST_ALL     \
    ASICS_TASK            \
    APPLICATIONS_TASKS    \
    BOARD_TASKS           \
    TASK_BOOTLOADER       \
    MCAL_TASKS            \
    TASK_CORE             \
    COMPUTING_TASKS       \
    CONNECTIVITY_TASKS    \
    CONTROL_TASKS         \
    GAMES_TASKS           \
    MULTIMEDIA_TASKS      \
    TASK_SENSITIVITY      \
    THIRD_PARTY_TASKS     \
    STORAGE_TASKS

#endif /* TASK_LIST_ALL_H */
