#ifndef CIRCULAR_BUFFER_WORD_H
#define CIRCULAR_BUFFER_WORD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include "circular_buffer_word_types.h"

uint32_t circular_buffer_word_get_size(CircularBufferWord_t* const Node);
bool circular_buffer_word_clean(CircularBufferWord_t* Node);
bool circular_buffer_word_free(CircularBufferWord_t* Node, uint32_t size);
bool circular_buffer_word_reset(CircularBufferWord_t* const Node);
bool circular_buffer_word_init(CircularBufferWord_t* const Node, int16_t* const inArray, uint32_t capacity);
bool circular_buffer_word_push(CircularBufferWord_t* const Node, int16_t inChar);
bool circular_buffer_word_pull(CircularBufferWord_t* const Node, int16_t* const outChar);
bool circular_buffer_word_peek(CircularBufferWord_t* const Node, int16_t* const outChar);
bool circular_buffer_word_get(CircularBufferWord_t* const Node,
                              int32_t need,
                              int16_t* const sample);

#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_WORD_H */
