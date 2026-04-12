#ifndef INTERVAL_H
#define INTERVAL_H

#include "std_includes.h"
#include "interval_types.h"
#ifdef HAS_INTERVAL_DIAG
#include "interval_diag.h"
#endif

int comp_points(const void* elem1, const void* elem2) ;
int comp_num(const void* elem1, const void* elem2) ;
int comp_bracket(const void* elem1, const void* elem2);

bool interval_intersect( const IntervalE_t*  const A, const  IntervalE_t* const  B) ;
bool IntervalConvert_2_1(const IntervalS_t* const in, IntervalE_t* const out);
bool IntervalConvert_e_s(const IntervalE_t* const in, IntervalS_t* const out);
bool IntervalConvert_s_e(const IntervalS_t* const in, IntervalE_t* const out);
bool intervals_intersect(const IntervalE_t* A, const  IntervalE_t* B);

bool intervals_overlaps(IntervalE_t* Interval1, IntervalE_t* Interval2);
bool is_interval_e(const IntervalE_t* const Interval);
bool intervals_shared(IntervalE_t* Interval1, IntervalE_t* Interval2);
bool intervals_merge(IntervalE_t* const Interval_a, IntervalE_t* const Interval_b, IntervalE_t* const Interval_new);
bool interval_is_dock(const IntervalE_t* const pA, const IntervalE_t* const pB) ;
bool interval_is_a_in_b(const IntervalE_t* const pA, const IntervalE_t* const pB) ;
bool interval_is_embrace(const IntervalE_t* const pA,
                         const IntervalE_t* const pB) ;
bool interval_is_merge(IntervalE_t* const pA, IntervalE_t* const pB);

bool interval_merge(IntervalE_t* const pA, IntervalE_t* const pB, IntervalE_t* const Interval_new);

bool interval_intersect_continuum(const IntervalE_t *const A,
		                           const IntervalE_t * const B);
#endif
