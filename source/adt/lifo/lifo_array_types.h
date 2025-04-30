#ifndef LIFO_ARRAY_TYPES_H
#define LIFO_ARRAY_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "array.h"
#include "lifo_index.h"

#ifndef HAS_LIFO
#error "+HAS_LIFO"
#endif

#ifndef HAS_LIFO_INDEX
#error "+HAS_LIFO_INDEX"
#endif

#ifndef HAS_LIFO_ARRAY
#error "+HAS_LIFO_ARRAY"
#endif

#define LIFO_ARR_NODE_CNT 10U

typedef struct {
    LifoIndexInfo_t lifoState;
    Array_t* pDataArray;
    bool init_done;
} LifoArray_t;

#ifdef __cplusplus
}
#endif

#endif /* LIFO_ARRAY_TYPES_H */
