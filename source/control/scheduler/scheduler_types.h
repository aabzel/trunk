#ifndef SCHEDULER_GENERAL_TYPES_H
#define SCHEDULER_GENERAL_TYPES_H

/*Mainly for NoRtos builds except RTOSBareBone build*/
#include "std_includes.h"
#include "scheduler_const.h"

#ifdef HAS_MISCELLANEOUS
#include "data_utils.h"
#endif
#include "scheduler_const.h"

#ifdef HAS_LIMITER
#include "limiter.h"
#endif

typedef bool (*TaskFunc_t)(void);

/*RAM node*/
typedef struct  {
#ifdef HAS_LIMITER
    Limiter_t limiter;
#endif

#ifdef HAS_LOG
    const char* const name;
#endif
    uint64_t period_us; /* mininum task invocation period in microseconds*/
    bool on;
    bool init;
}SchedulerTaskHandle_t;

#ifdef HAS_SCHEDULER_CONFIG
/*ROM node*/
typedef struct  {
#ifdef HAS_LIMITER
    Limiter_t limiter;
#endif
    TaskFunc_t function;
#ifdef HAS_LOG
    const char* const name;
#endif
    uint64_t period_us;
}SchedulerTaskConfig_t;

#define SCHEDULER_TASK_ARRAY SchedulerTaskConfig_t* TaskArray;
#else
#define SCHEDULER_TASK_ARRAY SchedulerTaskHandle_t* TaskArray;
#endif



#define SCHEDULER_COMMON_VARIABLES     \
    SCHEDULER_TASK_ARRAY               \
    uint32_t num;                      \
    bool valid;                        \
    uint32_t task_array_cnt;


#ifdef HAS_SCHEDULER_CONFIG
/*ROM node*/
typedef struct  {
    SCHEDULER_COMMON_VARIABLES
} SchedulerConfig_t;
#endif


typedef struct  {
    SCHEDULER_COMMON_VARIABLES

    bool init;
} SchedulerHandle_t;

#endif /* SCHEDULER_GENERAL_TYPES_H */
