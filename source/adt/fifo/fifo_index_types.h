#ifndef FIFO_INDEXER_TYPES_H
#define FIFO_INDEXER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_FIFO_INDEX
#error "+HAS_FIFO_INDEX"
#endif

#define RING_INVALID_INDEX 0xFFFFU

//typedef uint32_t uint32_t;

typedef struct {
	uint32_t size;
	uint32_t start;
	uint32_t end;
	uint32_t count;
    bool errors;
} fifo_index_info_t;

#ifdef __cplusplus
}
#endif

#endif /* FIFO_INDEXER_TYPES_H */
