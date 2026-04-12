#ifndef STORAGE_ROUTINES_H
#define STORAGE_ROUTINES_H

#include "std_includes.h"

#ifdef HAS_MEMORY_MANAGER_EHAL_PROC
#include "memory_manager_driver.h"

bool MEMORY_MANAGER_EHAL_Process(void);

#define MEMORY_MANAGER_ROUTINE                                    \
    {                                                             \
        .name = "TpMemMan",                                       \
        .period_us = MEMORY_MANAGER_POLLING_PERIOD_US,            \
        .limiter.function = MEMORY_MANAGER_EHAL_Process,          \
    },

#else
#define MEMORY_MANAGER_ROUTINE
#endif

#define STORAGE_ROUTINE         \
    MEMORY_MANAGER_ROUTINE

#endif /* STORAGE_ROUTINES_H */
