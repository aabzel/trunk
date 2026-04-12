#ifndef MEDIAN_FILTER_FAST_FILT_TYPES_H
#define MEDIAN_FILTER_FAST_FILT_TYPES_H

#include "std_includes.h"
#include "median_filter_fast_const.h"
#include "dsp_types.h"
#include "circular_buffer_dword_types.h"
#include "math_const.h"
#include "min_heap_types.h"
#include "max_heap_types.h"
#include "hash_table_s8_types.h"

//typedef double float;

#define MEDIAN_FILTER_FAST_COMMON_VARIABLE           \
    char* name;                                      \
    float sample_rate_hz;                            \
    uint32_t num;                                    \
    uint32_t size;      /*config Order K*/           \
    uint32_t bin_heap_size;  /**/                    \
    uint32_t max_size;  /*max Order M*/              \
    int32_t* tempLarge;     /*x Array of memory to sort samples in*/  \
    int32_t* tempSmall;     /*x Array of memory to sort samples in*/  \
    bool valid;


typedef struct {
    MEDIAN_FILTER_FAST_COMMON_VARIABLE
    int32_t* x;     /*x Array of memory*/  \
}MedianFilterFastConfig_t;

typedef struct {
    MEDIAN_FILTER_FAST_COMMON_VARIABLE
    uint32_t proc_cnt;
    int32_t old_elememt;
    CircularBufferDword_t SlidingWindow;
    MathParity_t k_parity;
    MinHeapHandle_t Large;
    MaxHeapHandle_t Small;
    int32_t small_size;
    int32_t large_size;
    int32_t flush_cnt;
#ifdef HAS_MEDIAN_FILTER_FAST_HASH_TABLE
    HashTableS8Handle_t ToDelete;
#endif
    bool init;
}MedianFilterFastHandle_t;

#endif /* MEDIAN_FILTER_FAST_FILT_TYPES_H */
