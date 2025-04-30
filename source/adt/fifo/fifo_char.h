#ifndef FIFO_CHAR_H
#define FIFO_CHAR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#include <stddef.h>

#include "fifo_index.h"

#ifndef HAS_FIFO
#error "+HAS_FIFO"
#endif

#ifndef HAS_FIFO_INDEX
#error "+HAS_FIFO_INDEX"
#endif

#ifndef HAS_FIFO_CHAR
#error "+HAS_FIFO_CHAR"
#endif

#define ESCAPE_CHAR ((char)0x1B)
#define ESCAPE_SQ_BR_OP_CHAR ((char)0x5B)

typedef struct {
    uint32_t err_cnt;
    bool initDone;
    fifo_index_info_t fifoState; // not volatile!
    char* array;
} FifoChar_t;

FifoIndex_t fifo_get_count(FifoChar_t* const instance);
FifoIndex_t fifo_get_size(FifoChar_t* const instance);
FifoIndex_t fifo_get_spare(FifoChar_t* const instance);

bool fifo_clean(FifoChar_t* instance);
bool fifo_free(FifoChar_t* fifo, FifoIndex_t size);
bool fifo_reset(FifoChar_t* const instance);
bool fifo_init(FifoChar_t* const instance, char* const inArray, FifoIndex_t capacity);
bool fifo_push(FifoChar_t* const instance, char inChar);
bool fifo_pull(FifoChar_t* const instance, char* const outChar);
bool fifo_peek(FifoChar_t* const instance, char* const outChar);
bool has_fifo_valid_data(FifoChar_t* const instance);

bool fifo_push_array(FifoChar_t* const instance, char* const inArr, FifoIndex_t arrLen);
bool fifo_pull_array(FifoChar_t* instance, char* outArr, size_t arr_size, FifoIndex_t* const outLen);
bool fifo_peek_array(FifoChar_t* const instance, char* const outArr, FifoIndex_t* const outLen);

#ifdef __cplusplus
}
#endif

#endif /* FIFO_CHAR_H */
