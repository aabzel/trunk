#ifndef LIFO_INDEXER_H
#define LIFO_INDEXER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef HAS_LIFO_INDEX
#error "+HAS_LIFO_INDEX"
#endif

#define RING_INVALID_INDEX 0xFFFFU

typedef int32_t LifoIndex_t;

typedef struct {
    LifoIndex_t size;
    volatile LifoIndex_t count;
    volatile bool errors;
} LifoIndexInfo_t;

#define LIFO_INDEX_INIT(size)                                           \
    { .size=(size), .start=0, .end=0, .count=0, .errors=false }

bool lifo_index_init(LifoIndexInfo_t* r_init, LifoIndex_t size_init);
bool lifo_index_valid(const LifoIndexInfo_t* r_valid);

bool lifo_index_free(LifoIndexInfo_t* r_free, LifoIndex_t size_free);
double lifo_index_get_used_pp(const LifoIndexInfo_t* lifo);
LifoIndex_t lifo_index_add(LifoIndexInfo_t* item);
LifoIndex_t lifo_index_get(LifoIndexInfo_t* item);
LifoIndex_t lifo_index_continuus_used_size(const LifoIndexInfo_t* item);
LifoIndex_t lifo_index_get_cnt(const LifoIndexInfo_t* item);
LifoIndex_t lifo_index_get_size(const LifoIndexInfo_t* item);
LifoIndex_t lifo_index_get_spare(const LifoIndexInfo_t* item);

#ifdef __cplusplus
}
#endif

#endif /* LIFO_INDEXER_H */
