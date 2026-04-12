#ifndef MEDIAN_FILTER_FILT_TYPES_H
#define MEDIAN_FILTER_FILT_TYPES_H

#include "std_includes.h"
#include "median_filter_const.h"
#include "dsp_types.h"
#include "circular_buffer_float_types.h"
#include "math_const.h"


//typedef double float;

#define MEDIAN_FILTER_COMMON_VARIABLE           \
    char* name;                                 \
    float sample_rate_hz;                       \
    uint32_t num;                               \
    uint32_t size;      /*config Order M*/      \
    uint32_t max_size;  /*max Order M*/         \
    float* temp;     /*x Array of memory to sort samples in*/  \
    bool valid;


typedef struct {
    MEDIAN_FILTER_COMMON_VARIABLE
    float* x;     /*x Array of memory*/  \
}MedianFilterConfig_t;

typedef struct {
    MEDIAN_FILTER_COMMON_VARIABLE
    CircularBufferFloat_t CircularBuffer;
    uint32_t proc_cnt;
    MathParity_t parity;
    bool init;
}MedianFilterHandle_t;

#endif /* MEDIAN_FILTER_FILT_TYPES_H */
