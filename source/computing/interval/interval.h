#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>
#include <stdint.h>

#include "interval_types.h"
#ifdef HAS_INTERVAL_DIAG
#include "interval_diag.h"
#endif

bool IntervalConvert_2_1(const IntervalS_t* const in, IntervalE_t* const out);
bool IntervalConvert_e_s(const IntervalE_t* const in, IntervalS_t* const out);
bool IntervalConvert_s_e(const IntervalS_t* const in, IntervalE_t* const out);
bool intervals_overlaps(IntervalE_t* Interval1, IntervalE_t* Interval2);
bool is_interval_e(const IntervalE_t* const Interval);
bool intervals_shared(IntervalE_t* Interval1, IntervalE_t* Interval2);
bool intervals_merge(IntervalE_t* const Interval_a, IntervalE_t* const Interval_b, IntervalE_t* const Interval_new);

#endif
