#ifndef FIFO_WORD_H
#define FIFO_WORD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "fifo_index.h"

typedef struct {
    uint32_t err_cnt;
    bool init_done;
    fifo_index_info_t state;
    int16_t* array;
} FifoWord_t;

FifoIndex_t fifo_word_get_count(FifoWord_t* const instance);
FifoIndex_t fifo_word_get_size(FifoWord_t* const instance);
FifoIndex_t fifo_word_get_spare(FifoWord_t* const instance);

bool fifo_word_clean(FifoWord_t* instance);
bool fifo_word_free(FifoWord_t* fifo, FifoIndex_t size);
bool fifo_word_reset(FifoWord_t* const instance);
bool fifo_word_init(FifoWord_t* const instance, int16_t* const inArray, FifoIndex_t capacity);
bool fifo_word_push(FifoWord_t* const instance, int16_t inChar);
bool fifo_word_pull(FifoWord_t* const instance, int16_t* const outChar);
bool fifo_word_peek(FifoWord_t* const instance, int16_t* const outChar);
bool has_fifo_word_valid_data(FifoWord_t* const instance);

#ifdef __cplusplus
}
#endif

#endif /* FIFO_WORD_H */
