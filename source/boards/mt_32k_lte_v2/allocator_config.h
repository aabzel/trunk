#ifndef ALLOCATOR_CONFIG_H
#define ALLOCATOR_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_ALLOCATOR
#error "+HAS_ALLOCATOR"
#endif

#include "macro_utils.h"

#define TOTAL_HEAP_SIZE (10*K_BYTES)

#ifdef __cplusplus
}
#endif

#endif /* ALLOCATOR_CONFIG_H */
