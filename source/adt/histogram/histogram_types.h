#ifndef HISTOGRAM_TYPES_H
#define HISTOGRAM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "histogram_const.h"

#define HISTOGRAM_COMMON_VARIABLE        \
    uint8_t num;                         \
    uint32_t resolution;                 \
    int32_t min_val;                     \
    int32_t max_val;                     \
    uint32_t* frequency;                 \
    int32_t size;                        \
    bool valid;

typedef struct {
    HISTOGRAM_COMMON_VARIABLE
} HistogramConfig_t;

typedef struct {
    HISTOGRAM_COMMON_VARIABLE
    uint32_t err_cnt;
    uint32_t add_cnt;
    int32_t range;
    int32_t bin_cnt; /**/
    int32_t in_cnt; /*add counter*/
    int64_t sum; /*sum of all inputs values*/
    bool init;
    int32_t expected_value;
} HistogramHandle_t;


typedef struct {
    uint32_t index; //value
    uint32_t frequency; //frequency
    int64_t expected_value;
} HistogramItem_t;

#ifdef __cplusplus
}
#endif

#endif /* HISTOGRAM_TYPES_H */


