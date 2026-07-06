#ifndef FIFO_INDEXER_H
#define FIFO_INDEXER_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"

#ifndef HAS_FIFO_INDEX
#error "+HAS_FIFO_INDEX"
#endif

#define RING_INVALID_INDEX 0xFFFFU


typedef struct {
	uint32_t size;
	uint32_t start;
	uint32_t end;
	uint32_t count;
    bool errors;
} fifo_index_info_t;

#define FIFO_INDEX_INIT(size)                                           \
    { .size=(size), .start=0, .end=0, .count=0, .errors=false }

bool fifo_index_init(fifo_index_info_t* r_init, uint32_t size_init);
bool fifo_index_valid(const fifo_index_info_t* r_valid);

bool fifo_index_free(fifo_index_info_t* r_free, uint32_t size_free);
double fifo_index_get_used_pp(const fifo_index_info_t* fifo);
uint32_t fifo_index_add(fifo_index_info_t* r_add);
uint32_t fifo_index_get(fifo_index_info_t* r_get);
uint32_t fifo_index_continuus_used_size(const fifo_index_info_t* r_cus);
uint32_t fifo_index_get_used(const fifo_index_info_t* r_used);
uint32_t fifo_index_get_size(const fifo_index_info_t* r_size);
uint32_t fifo_index_get_spare(const fifo_index_info_t* r_spare);

#ifdef __cplusplus
}
#endif

#endif /* FIFO_INDEXER_H */
