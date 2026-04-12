#ifndef MAX_HEAP_DIAG_H
#define MAX_HEAP_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "max_heap_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_MAX_HEAP
#error "+HAS_MAX_HEAP"
#endif /*HAS_MAX_HEAP*/

#ifndef HAS_MAX_HEAP_DIAG
#error "+HAS_MAX_HEAP_DIAG"
#endif /*HAS_DIAG_MAX_HEAP*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

bool max_heap_diag(uint8_t num);
const char* MaxHeapConfigToStr(const MaxHeapConfig_t* const Config);
const char* MaxHeapNodeToStr(const MaxHeapHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* MAX_HEAP_DIAG_H  */
