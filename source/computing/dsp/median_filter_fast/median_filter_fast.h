#ifndef MEDIAN_FILTER_FAST_SWC_H
#define MEDIAN_FILTER_FAST_SWC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "median_filter_fast_config.h"
#include "median_filter_fast_types.h"
#include "median_filter_fast_isr.h"

#ifdef HAS_MEDIAN_FILTER_FAST_DIAG
#include "median_filter_fast_diag.h"
#endif

// API
MedianFilterFastHandle_t* MedianFilterFastGetNode(uint8_t num);
const MedianFilterFastConfig_t* MedianFilterFastGetConfig(uint8_t num);

bool median_filter_fast_mcal_init(void);
bool median_filter_fast_init_one(uint8_t num);

/*getter*/
/*Main filter function*/
bool median_filter_fast_proc_in_out(uint8_t num, const int32_t in_val, float* const out_val);

uint32_t median_filter_fast_get_tolal_size(const MedianFilterFastHandle_t* const Node);

bool median_filter_fast_delete_old_force_dig_out_ll(MedianFilterFastHandle_t* const Node,
                                                    const int32_t old_elememt);
/*setters*/
bool prune_both(MedianFilterFastHandle_t* const Node) ;
bool median_filter_fast_delete_old_force_ll(MedianFilterFastHandle_t* const Node,
                                             const int32_t old_elememt);

#ifdef __cplusplus
}
#endif

#endif /* MEDIAN_FILTER_FAST_SWC_H */
