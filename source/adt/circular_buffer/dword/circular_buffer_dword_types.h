#ifndef CIRCULAR_BUFFER_DWORD_TYPES_H
#define CIRCULAR_BUFFER_DWORD_TYPES_H

#include "std_includes.h"
#include "circular_buffer_index.h"

typedef struct {
    uint32_t err_cnt;
    bool init_done;
    CircularBufferIndexInfo_t state;
    int32_t* array;
} CircularBufferDword_t;

#endif /* CIRCULAR_BUFFER_DWORD_TYPES_H */
