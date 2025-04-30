#ifndef LIFO_ARRAY_H
#define LIFO_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "lifo_index.h"
#include "lifo_array_types.h"
#include "array.h"

#ifndef HAS_LIFO
#error "+HAS_LIFO"
#endif

#ifndef HAS_LIFO_INDEX
#error "+HAS_LIFO_INDEX"
#endif

#ifndef HAS_LIFO_ARRAY
#error "+HAS_LIFO_ARRAY"
#endif

// API
bool lifo_arr_init(LifoArray_t* const Node, Array_t* const heap, LifoIndex_t capacity);

//set
bool lifo_arr_del_first(LifoArray_t* const Node);
bool lifo_arr_delete_cnt(const LifoArray_t* const Node, uint32_t cnt) ;
bool lifo_arr_clean(LifoArray_t* Node);
bool lifo_arr_push(LifoArray_t* const Node, Array_t node);
bool lifo_arr_reset(LifoArray_t* const Node);
bool lifo_arr_pack_frame(uint8_t *tx_buf, uint32_t size, LifoArray_t* const Node, uint32_t *tx_len);


//get
bool is_lifo_arr_valid(LifoArray_t* const Node);
bool lifo_arr_pull(LifoArray_t* const Node, Array_t* const node);
LifoIndex_t lifo_arr_get_count(LifoArray_t* const Node);
LifoIndex_t lifo_arr_get_size(LifoArray_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* LIFO_ARRAY_H */
