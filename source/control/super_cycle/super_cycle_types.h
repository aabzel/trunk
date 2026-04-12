#ifndef SUPER_CYCLE_TYPES_H
#define SUPER_CYCLE_TYPES_H

#include "std_includes.h"
#include "super_cycle_const.h"
#include "super_cycle_dep.h"

#ifdef HAS_MISCELLANEOUS
#include "data_types.h"
#endif



#define SUPER_CYCLE_COMMON_VARIABLE   \
    uint32_t num;                     \
    uint32_t max_duration_us;         \
    bool valid;                       \
    uint32_t scheduler_num;

typedef struct {
    SUPER_CYCLE_COMMON_VARIABLE
}SuperCycleConfig_t;

typedef struct {
    SUPER_CYCLE_COMMON_VARIABLE
    uint64_t init_end_time_us;
    uint32_t init_end_time_ms;
    volatile uint32_t start_time_ms;
    volatile uint64_t start_time_us;
    uint32_t error;
    uint64_t prev_start_time_us;
    uint64_t spin_cnt;
#ifdef HAS_MISCELLANEOUS
    U32Value_t duration_us;
#endif
    int32_t iteration_sleep_ms;
    bool run;
    bool init;
}SuperCycleHandle_t;


#endif /* SUPER_CYCLE_TYPES_H */
