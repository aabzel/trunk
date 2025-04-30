#ifndef LIFO_ARRAY_DIAG_H
#define LIFO_ARRAY_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "array.h"
#include "lifo_array_types.h"
#include "lifo_index.h"
#include "protocol_const.h"

#ifndef HAS_LIFO
#error "+HAS_LIFO"
#endif

#ifndef HAS_LIFO_INDEX
#error "+HAS_LIFO_INDEX"
#endif

#ifndef HAS_LIFO_ARRAY
#error "+HAS_LIFO_ARRAY"
#endif

bool LivoIsValidItem(const  Array_t* const Item);
bool LifoArrayDiag(const LifoArray_t* const Node, Protocol_t protocol);
bool lifo_arr_diag(const LifoArray_t* const Node);
bool lifo_arr_peek(const LifoArray_t* const Node, Array_t* const item);
bool lifo_arr_peek_num(const LifoArray_t* const Node, uint32_t num, Array_t* const item);

#ifdef __cplusplus
}
#endif

#endif /* LIFO_ARRAY_DIAG_H */
