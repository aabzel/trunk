#ifndef FIFO_ARRAY_H
#define FIFO_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "fifo_index.h"

#include "array.h"

#ifndef HAS_FIFO_INDEX
#error "+HAS_FIFO_INDEX"
#endif

#ifndef HAS_FIFO_ARRAY
#error "+HAS_FIFO_ARRAY"
#endif

#define FIFO_ARR_NODE_CNT 10U

typedef struct  {
    fifo_index_info_t fifoState;
    Array_t* pDataArray;
    bool init_done;
} FifoArray_t;

bool fifo_arr_del_first(FifoArray_t* const instance);
bool fifo_arr_clean(FifoArray_t* instance);
bool fifo_arr_init(FifoArray_t* const instance, Array_t* const heap, FifoIndex_t capacity);
bool fifo_arr_peek(FifoArray_t* const instance, Array_t* const outChar);
bool fifo_arr_pull(FifoArray_t* const instance, Array_t* const node);
bool fifo_arr_push(const FifoArray_t* const instance, Array_t node);
bool fifo_arr_reset(FifoArray_t* const instance);
bool fifo_arr_pack_frame(uint8_t *tx_buf, uint32_t size, FifoArray_t* const instance, uint32_t *tx_len);
FifoIndex_t fifo_arr_get_count(FifoArray_t* const instance);
FifoIndex_t fifo_arr_get_size(FifoArray_t* const instance);
#ifdef __cplusplus
}
#endif

#endif /* FIFO_ARRAY_H */
