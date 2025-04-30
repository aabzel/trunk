#ifndef IIR_FILT_TYPES_H
#define IIR_FILT_TYPES_H

#include "std_includes.h"
#include "iir_const.h"
#include "circular_buffer_index.h"

typedef float IirSample_t;

#define IIR_COMMON_VARIABLE                  \
    char* name;                              \
    double sample_rate_hz;                   \
    double cut_off_freq_hz;                  \
    uint32_t num;                            \
    uint32_t size;      /*config Order M*/     \
    uint32_t max_size;  /*max Order M*/        \
    IirSample_t* b;     /*Array of feedforward coefficients b[i]*/  \
    IirSample_t* a;     /*Array of feedback coefficients a[i]*/     \
    IirSample_t* x;     /*x Array of memory*/  \
    IirSample_t* y;     /*y Array of memory*/  \
    bool valid;


typedef struct {
    IIR_COMMON_VARIABLE
}IirConfig_t;

typedef struct {
    IIR_COMMON_VARIABLE
    CircularBufferIndexInfo_t xIndexer;
    //CircularBufferIndexInfo_t yIndexer;
    uint32_t proc_cnt;
    bool init;
}IirHandle_t;

#endif /* IIR_FILT_TYPES_H */
