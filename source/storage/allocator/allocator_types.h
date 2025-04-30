#ifndef ALLOCATOR_TYPES_H
#define ALLOCATOR_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t size; /*number of bytes*/
    void* addr;    /*or crc of addr and size*/
} MemoryChunkHeader_t;

typedef struct {
    uint32_t in_heap;
    uint32_t out_heap;
} LinkCounter_t;

#ifdef __cplusplus
}
#endif

#endif /* ALLOCATOR_TYPES_H */
