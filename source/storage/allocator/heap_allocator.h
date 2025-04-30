#ifndef HEAP_ALLOCATOR_H
#define HEAP_ALLOCATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "allocator_config.h"
#include "allocator_types.h"

#ifndef HAS_HEAP
#error "It is needed HAS_HEAP option for that component"
#endif

#ifndef HAS_ALLOCATOR
#error "It is needed HAS_ALLOCATOR"
#endif

extern uint8_t ucHeap[TOTAL_HEAP_SIZE];

bool h_is_heap_addr(void* addr);
bool h_count_link(void* addr, LinkCounter_t* LinkCounter);
bool h_is_allocated(void* addr);
bool h_free(void* addr);
bool h_init(void);
void* h_malloc(size_t bytes);
uint32_t h_count(void);

#ifdef __cplusplus
}
#endif

#endif /* HEAP_ALLOCATOR_H */
