#ifndef CIRCULAR_BUFFER_WORD_TYPES_H
#define CIRCULAR_BUFFER_WORD_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "circular_buffer_index.h"

typedef struct {
    uint32_t err_cnt;
    bool init_done;
    CircularBufferIndexInfo_t state;
    int16_t* array;
} CircularBufferWord_t;

#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_WORD_TYPES_H */
