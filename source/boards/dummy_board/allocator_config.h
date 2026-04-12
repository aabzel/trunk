#ifndef ALLOCATOR_CONFIGURATION_H
#define ALLOCATOR_CONFIGURATION_H

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

#endif /* ALLOCATOR_CONFIGURATION_H */
