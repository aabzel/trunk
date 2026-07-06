#ifndef CIRCULAR_BUFFER_INDEXER_H
#define CIRCULAR_BUFFER_INDEXER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "circular_buffer_types.h"

bool circular_buffer_index_init(CircularBufferIndexInfo_t* Node, int32_t size_init);
bool circular_buffer_index_diag(CircularBufferIndexInfo_t* Node);
uint32_t circular_buffer_index_get_size(const CircularBufferIndexInfo_t* Node);
uint32_t circular_buffer_index_add(CircularBufferIndexInfo_t* Node);
uint32_t circular_buffer_index_get(CircularBufferIndexInfo_t* Node);
int32_t circular_buffer_index_get_i(CircularBufferIndexInfo_t* Node, int32_t i);
int32_t circular_buffer_index_calc_phy_index(int32_t size, int32_t cur, int32_t need);

#ifdef __cplusplus
}
#endif

#endif /* CIRCULAR_BUFFER_INDEXER_H */
