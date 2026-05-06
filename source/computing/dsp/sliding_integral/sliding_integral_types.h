#ifndef SLIDING_INTEGRAL_TYPES_H
#define SLIDING_INTEGRAL_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sliding_integral_const.h"
#include "circular_buffer_types.h"

#define SLIDING_INTEGRAL_COMMON_VARIABLE       \
    uint32_t sample_rate_hz;                   \
    char* name;                                \
    uint32_t num;                              \
    uint32_t size;    /*config Order M*/       \
    uint32_t max_size;    /*max Order M*/      \
    int32_t* x;    /*Array of memory*/         \
    bool valid;                                \

typedef struct {
    SLIDING_INTEGRAL_COMMON_VARIABLE
} SlidingIntegralConfig_t;

typedef struct {
    SLIDING_INTEGRAL_COMMON_VARIABLE
    bool init;
    CircularBufferIndexInfo_t indexer;
    uint32_t proc_cnt;
    int32_t sum;
    /*Array of values*/
} SlidingIntegralHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* SLIDING_INTEGRAL_TYPES_H */
