#ifndef MAX_HEAP_CONFIG_H
#define MAX_HEAP_CONFIG_H

#include "std_includes.h"
#include "max_heap_types.h"
#include "max_heap_dep.h"

extern const BinHeapConfig_t MaxHeapConfig[];
extern MaxHeapHandle_t MaxHeapInstance[];

uint32_t max_heap_get_cnt(void);

#endif /* MAX_HEAP_CONFIG_H */
