#ifndef MIN_HEAP_MCAL_H
#define MIN_HEAP_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "min_heap_config.h"
#include "min_heap_types.h"

#ifdef HAS_MIN_HEAP_DIAG
#include "min_heap_diag.h"
#endif

/* API */
BinHeapHandle_t* MinHeapGetNode(uint8_t num);

const BinHeapConfig_t* MinHeapGetConfig(uint8_t num) ;

//bool MinHeapIsValidConfig(const BinHeapConfig_t* const Config);

#ifdef HAS_MIN_HEAP_CUSTOM
const MinHeapInfo_t* MinHeapGetInfo(uint8_t num);
#endif

bool min_heap_mcal_init(void);
bool min_heap_init_custom(void);
bool min_heap_init_one(uint8_t num);
bool min_heap_init_one_ll( BinHeapConfig_t* Config,
                           BinHeapHandle_t* Node ) ;

bool min_heap_proc_one(uint8_t num);
bool min_heap_proc(void);

/*setters*/
bool min_heap_push(BinHeapHandle_t* Node, const int32_t value);
bool min_heap_pull(BinHeapHandle_t* const Node, int32_t* const out_val);
bool min_heap_delete_root(BinHeapHandle_t* const Node);

/*getters*/
bool min_heap_peek(BinHeapHandle_t* const Node, int32_t* const out_val);
bool min_heap_check(const BinHeapHandle_t* const Node, int32_t const value);
bool min_heap_delete(BinHeapHandle_t* const Node, int32_t const value);
uint32_t min_heap_size(const BinHeapHandle_t* const Node);

bool min_heap_sort(uint8_t num, int32_t * const array, uint32_t size);
bool min_heap_check_h(uint8_t num, const int32_t val);
bool min_heap_delete_h(uint8_t num, const int32_t val);
bool min_heap_peek_h(uint8_t num, int32_t* const out_val);
bool min_heap_push_h(uint8_t num, const int32_t value);
bool min_heap_pull_h(uint8_t num, int32_t* const out_val);

#ifdef __cplusplus
}
#endif

#endif /* MIN_HEAP_MCAL_H */
