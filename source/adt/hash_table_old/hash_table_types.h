#ifndef HASH_TABLE_TYPES_H
#define HASH_TABLE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "std_includes.h"
#include "fifo_index.h"
#include "fifo_char_dep.h"


typedef struct {
    int32_t value;
    uint32_t cnt;
    //bool valid;
} HashTable_t;


#ifdef __cplusplus
}
#endif

#endif /* HASH_TABLE_TYPES_H */
