#ifndef FIR_INT_TYPES_H
#define FIR_INT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "fir_int_const.h"
#include "fir_int_dep.h"
#include "circular_buffer_types.h"

typedef int16_t FirIntSample_t;  /*-32k .....   32k*/

#define FIR_INT_COMMON_VARIABLE    \
    double sample_rate_hz;     \
    double cut_off_freq_hz;     \
    uint32_t num;              \
    uint32_t max_size;    /*max Order M*/ \
    volatile uint32_t size;    /*config Order M*/     \
    volatile FirIntSample_t denominator;   \
    volatile FirIntSample_t* a_numerator;     /*Array of default coefficients h[i]*/ \
    volatile FirIntSample_t* x;/*Array of memory*/ \
    float* a_real;     /*Array of default coefficients h[i]*/ \
    bool valid;

typedef struct {
    FIR_INT_COMMON_VARIABLE
    char* name;
    /*Array of coefficients*/
} FirIntConfig_t;

typedef struct {
    FIR_INT_COMMON_VARIABLE
    bool init;
    volatile CircularBufferIndexInfo_t indexer;
    uint32_t pop_cnt;
    /*Array of values*/
} FirIntHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* FIR_INT_TYPES_H */
