#ifndef CIRCULAR_BUFFER_TYPES_H
#define CIRCULAR_BUFFER_TYPES_H

#include <stddef.h>

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int32_t size;
    volatile int32_t cur;
    bool init;
} CircularBufferIndexInfo_t;


#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_TYPES_H */
