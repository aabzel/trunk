#ifndef MIN_HEAP_DIAG_H
#define MIN_HEAP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "min_heap_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_MIN_HEAP
#error "+HAS_MIN_HEAP"
#endif

#ifndef HAS_MIN_HEAP_DIAG
#error "+HAS_MIN_HEAP_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool min_heap_diag(uint8_t num);
const char* MinHeapConfigToStr(const BinHeapConfig_t* const Config);
const char* MinHeapNodeToStr(const BinHeapHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* MIN_HEAP_DIAG_H  */
