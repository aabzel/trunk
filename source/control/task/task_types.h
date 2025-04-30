#ifndef TASK_GENERAL_TYPES_H
#define TASK_GENERAL_TYPES_H

/*Mainly for NoRtos builds except RTOSBareBone build*/
#include <stdint.h>

#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif
#include "task_const.h"

#ifdef HAS_LIMITER
#include "limiter.h"
#endif

typedef struct  {
    uint64_t period_us; /*TODO Is that need to move To limiter ?*/
    bool init;
#ifdef HAS_LIMITER
    Limiter_t limiter;
#endif

#ifdef HAS_LOG
    const char* const name;
#endif
} TaskConfig_t;


#if 0
typedef struct  {
    bool init;
    uint64_t period_us;
    bool on;
#ifdef HAS_LIMITER
    Limiter_t limiter;
#endif
    const char* const name;
} TaskData_t;
#endif


#endif /* TASK_GENERAL_TYPES_H */
