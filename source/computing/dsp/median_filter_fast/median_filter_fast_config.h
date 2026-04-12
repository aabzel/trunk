#ifndef MEDIAN_FILTER_FAST_FILT_CONFIG_H
#define MEDIAN_FILTER_FAST_FILT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "median_filter_fast_types.h"

extern const MedianFilterFastConfig_t MedianFilterFastConfig[];
extern MedianFilterFastHandle_t MedianFilterFastInstance[];

uint32_t median_filter_fast_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* MEDIAN_FILTER_FAST_FILT_CONFIG_H */
