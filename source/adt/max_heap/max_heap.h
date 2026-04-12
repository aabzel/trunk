#ifndef MAX_HEAP_MCAL_H
#define MAX_HEAP_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "max_heap_config.h"
#include "max_heap_types.h"
#ifdef HAS_MAX_HEAP_DIAG
#include "max_heap_diag.h"
#endif

/* API */
const BinHeapConfig_t* MaxHeapGetConfig(uint8_t num);
BinHeapHandle_t* MaxHeapGetNode(uint8_t num);

bool MaxHeapIsValidConfig(const BinHeapConfig_t* const Config);

#ifdef HAS_MAX_HEAP_CUSTOM
const MaxHeapInfo_t* MaxHeapGetInfo(uint8_t num);
#endif

bool max_heap_mcal_init(void);
bool max_heap_init_custom(void);
bool max_heap_init_one(uint8_t num);
bool max_heap_init_one_ll(const BinHeapConfig_t* const Config, BinHeapHandle_t* const Node);

bool max_heap_proc_one(uint8_t num);
bool max_heap_proc(void);

/*setters*/
bool max_heap_push(BinHeapHandle_t* Node, const int32_t value);
bool max_heap_pull(BinHeapHandle_t* const Node, int32_t* const out_val);
bool max_heap_push_h(uint8_t num, const int32_t value);
bool max_heap_pull_h(uint8_t num, int32_t* const out_val);
bool max_heap_delete_root(BinHeapHandle_t* const Node);

bool max_heap_sort(uint8_t num, int32_t * const array, uint32_t size);

/*getters*/
bool max_heap_is_valid(const BinHeapHandle_t* const Node);
uint32_t max_heap_size(const BinHeapHandle_t* const Node);
bool max_heap_peek(BinHeapHandle_t* const Node, int32_t* const out_val);
bool max_heap_delete(BinHeapHandle_t* const Node, const int32_t value);
bool max_heap_check(BinHeapHandle_t* const Node, const int32_t value);
bool max_heap_peek_h(uint8_t num, int32_t* const out_val);
bool max_heap_check_h(uint8_t num, int32_t out_val);
bool max_heap_delete_h(uint8_t num, int32_t out_val);

#ifdef __cplusplus
}
#endif

#endif /* MAX_HEAP_MCAL_H */
