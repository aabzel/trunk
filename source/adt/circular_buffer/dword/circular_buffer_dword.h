#ifndef CIRCULAR_BUFFER_DWORD_H
#define CIRCULAR_BUFFER_DWORD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "circular_buffer_dword_types.h"

bool circular_buffer_dword_init(CircularBufferDword_t* const Node, int32_t* const inArray, uint32_t capacity);

/*getter*/
uint32_t circular_buffer_dword_get_size(CircularBufferDword_t* const Node);
bool circular_buffer_dword_peek(CircularBufferDword_t* const Node, int32_t* const outChar);
bool circular_buffer_dword_get(CircularBufferDword_t* const Node,
                              int32_t need,
                              int32_t* const sample);
bool circular_buffer_dword_pull(CircularBufferDword_t* const Node, int32_t* const outChar);

/*setter*/
bool circular_buffer_dword_clean(CircularBufferDword_t* Node);
bool circular_buffer_dword_free(CircularBufferDword_t* Node, uint32_t size);
bool circular_buffer_dword_reset(CircularBufferDword_t* const Node);
bool circular_buffer_dword_push(CircularBufferDword_t* const Node, int32_t inChar);

bool circular_buffer_push_pull(CircularBufferDword_t* Node,
                               const int32_t in_dword,
                               int32_t* const out_dword);
#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_DWORD_H */
