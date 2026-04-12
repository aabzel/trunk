#ifndef MEDIAN_FILTER_FILT_CONFIG_H
#define MEDIAN_FILTER_FILT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "median_filter_types.h"


extern const MedianFilterConfig_t MedianFilterConfig[];
extern MedianFilterHandle_t MedianFilterInstance[];

uint32_t median_filter_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* MEDIAN_FILTER_FILT_CONFIG_H */
