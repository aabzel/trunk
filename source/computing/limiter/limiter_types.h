#ifndef LIMITER_TYPES_H
#define LIMITER_TYPES_H

#include "std_includes.h"

#ifdef HAS_DATA_MISC
#include "data_types.h"
#endif

typedef bool (*TaskFunc_t)(void);

typedef struct {
    uint32_t call_cnt;
    uint32_t idle_cnt;
#ifdef HAS_DATA_MISC
    U64Value_t duration_us;
    U64Value_t start_period_us;
#endif
    uint64_t start_time_next_us;
    uint64_t phase_us; /*Set default random within 0....period*/
    uint64_t run_time_total_us;
    uint64_t start_time_prev_us;
#ifdef HAS_LIMITER
    TaskFunc_t function;
#endif
    bool init;
    bool on_off;
} Limiter_t;

#endif /* LIMITER_TYPES_H */
