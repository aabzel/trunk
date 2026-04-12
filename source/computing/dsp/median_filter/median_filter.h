#ifndef MEDIAN_FILTER_SWC_H
#define MEDIAN_FILTER_SWC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "median_filter_config.h"
#include "median_filter_types.h"
#include "median_filter_isr.h"
#ifdef HAS_MEDIAN_FILTER_DIAG
#include "median_filter_diag.h"
#endif

#define MIDDLE_3(a,b,c) \
    ((a)>(b)? \
    ((b)>(c)?(b):((a)<(c)?(a):(c))): \
    ((b)<(c)?(b):((a)<(c)?(c):(a))))

// API
const MedianFilterConfig_t* MedianFilterGetConfig(uint8_t num);
MedianFilterHandle_t* MedianFilterGetNode(uint8_t num);

bool median_filter_mcal_init(void);
bool median_filter_init_one(uint8_t num);

/*getter*/
int32_t median_of_3_sort(const int32_t a,
                         const int32_t b,
                         const int32_t c);

int32_t median_of_3_if(const int32_t a,
                       const int32_t b,
                       const int32_t c);


#ifdef __cplusplus
}
#endif

#endif /* MEDIAN_FILTER_SWC_H */
