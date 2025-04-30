#ifndef FIR_TYPES_H
#define FIR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "fir_const.h"
#include "circular_buffer_types.h"

typedef float FirSample_t;

#define FIR_COMMON_VARIABLE                  \
    FirMode_t mode;                          \
    double sample_rate_hz;                   \
    char* file_name_out;                     \
    char* file_name_in ;                     \
    double cut_off_freq_hz;                  \
    uint32_t num;                            \
    uint32_t size;    /*config Order M*/     \
    uint32_t max_size;    /*max Order M*/    \
    FirSample_t* b;     /*Array of default coefficients h[i]*/   \
    FirSample_t* x;    /*Array of memory*/      \
    bool valid;                \

typedef struct {
    FIR_COMMON_VARIABLE
    char* name;
    /*Array of coefficients*/
} FirConfig_t;

typedef struct {
    FIR_COMMON_VARIABLE
    bool init;
    CircularBufferIndexInfo_t indexer;
    uint32_t proc_cnt;
    /*Array of values*/
} FirHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* FIR_TYPES_H */
