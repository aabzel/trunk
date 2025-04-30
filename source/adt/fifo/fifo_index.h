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

typedef uint16_t FifoIndex_t;

typedef struct {
	FifoIndex_t size;
	FifoIndex_t start;
	FifoIndex_t end;
	FifoIndex_t count;
    bool errors;
} fifo_index_info_t;

#define FIFO_INDEX_INIT(size)                                           \
    { .size=(size), .start=0, .end=0, .count=0, .errors=false }

bool fifo_index_init(fifo_index_info_t* r_init, FifoIndex_t size_init);
bool fifo_index_valid(const fifo_index_info_t* r_valid);

bool fifo_index_free(fifo_index_info_t* r_free, FifoIndex_t size_free);
double fifo_index_get_used_pp(const fifo_index_info_t* fifo);
FifoIndex_t fifo_index_add(fifo_index_info_t* r_add);
FifoIndex_t fifo_index_get(fifo_index_info_t* r_get);
FifoIndex_t fifo_index_continuus_used_size(const fifo_index_info_t* r_cus);
FifoIndex_t fifo_index_get_used(const fifo_index_info_t* r_used);
FifoIndex_t fifo_index_get_size(const fifo_index_info_t* r_size);
FifoIndex_t fifo_index_get_spare(const fifo_index_info_t* r_spare);

#ifdef __cplusplus
}
#endif

#endif /* FIFO_INDEXER_H */
