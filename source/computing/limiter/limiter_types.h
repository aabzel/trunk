#ifndef LIMITER_TYPES_H
#define LIMITER_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "data_types.h"

typedef bool (*TaskFunc_t)(void);

typedef struct {
    uint32_t call_cnt;
    uint32_t idle_cnt;
    U64Value_t duration_us;
    U64Value_t start_period_us;
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
