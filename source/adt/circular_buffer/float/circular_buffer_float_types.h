#ifndef CIRCULAR_BUFFER_FLOAT_TYPES_H
#define CIRCULAR_BUFFER_FLOAT_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "circular_buffer_index.h"

typedef struct {
    CircularBufferIndexInfo_t state;
    float* array;
    bool init_done;
    uint32_t err_cnt;
} CircularBufferFloat_t;

#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_FLOAT_TYPES_H */
