#ifndef MEDIAN_FILTER_ISR_H
#define MEDIAN_FILTER_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "median_filter_types.h"

bool median_filter_proc_fast_in_out(uint8_t num, float x0, float* const y);
bool median_filter_proc_in_out(uint8_t num, const float in_val, float* const out_val);

#ifdef __cplusplus
}
#endif

#endif /* MEDIAN_FILTER_ISR_H */
