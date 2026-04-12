#ifndef CIRCULAR_BUFFER_FLOAT_H
#define CIRCULAR_BUFFER_FLOAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "circular_buffer_float_types.h"

uint32_t circular_buffer_float_get_size(CircularBufferFloat_t* const Node);
bool circular_buffer_float_clean(CircularBufferFloat_t* Node);
bool circular_buffer_float_free(CircularBufferFloat_t* Node, uint32_t size);
bool circular_buffer_float_reset(CircularBufferFloat_t* const Node);
bool circular_buffer_float_init(CircularBufferFloat_t* const Node, float* const inArray, uint32_t capacity);
bool circular_buffer_float_push(CircularBufferFloat_t* const Node, float inChar);
bool circular_buffer_float_pull(CircularBufferFloat_t* const Node, float* const outChar);
bool circular_buffer_float_peek(CircularBufferFloat_t* const Node, float* const outChar);
bool circular_buffer_float_get(CircularBufferFloat_t* const Node,
                              int32_t need,
                              float* const sample);

#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_FLOAT_H */
