#ifndef FIFO_CHAR_H
#define FIFO_CHAR_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stddef.h>

#include "std_includes.h"
#include "fifo_index.h"
#include "fifo_char_types.h"

#ifndef HAS_FIFO
#error "+HAS_FIFO"
#endif

#ifndef HAS_FIFO_INDEX
#error "+HAS_FIFO_INDEX"
#endif

#ifndef HAS_FIFO_CHAR
#error "+HAS_FIFO_CHAR"
#endif

uint32_t fifo_get_count(FifoChar_t* const instance);
uint32_t fifo_get_size(FifoChar_t* const instance);
uint32_t fifo_get_spare(FifoChar_t* const instance);

bool fifo_clean(FifoChar_t* instance);
bool fifo_free(FifoChar_t* fifo, uint32_t size);
bool fifo_reset(FifoChar_t* const instance);
bool fifo_init(FifoChar_t* const instance, uint8_t* const inArray, uint32_t capacity);
bool fifo_push(FifoChar_t* const instance, uint8_t inChar);
bool fifo_pull(FifoChar_t* const instance, uint8_t* const outChar);
bool fifo_peek(FifoChar_t* const instance, uint8_t* const outChar);
bool has_fifo_valid_data(FifoChar_t* const instance);

bool fifo_push_array(FifoChar_t* const instance, uint8_t* const inArr, uint32_t arrLen);
bool fifo_pull_array(FifoChar_t* instance, uint8_t* outArr, uint32_t arr_size, uint32_t* const outLen);
bool fifo_peek_array(FifoChar_t* const instance, uint8_t* const outArr, uint32_t* const outLen);

#ifdef __cplusplus
}
#endif

#endif /* FIFO_CHAR_H */
