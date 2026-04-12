#ifndef MIN_HEAP_CONFIG_H
#define MIN_HEAP_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "min_heap_types.h"
#include "min_heap_dep.h"

extern const BinHeapConfig_t MinHeapConfig[];
extern BinHeapHandle_t MinHeapInstance[];

uint32_t min_heap_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* MIN_HEAP_CONFIG_H */
