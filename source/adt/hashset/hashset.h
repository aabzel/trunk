#ifndef HASHSET_H
#define HASHSET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "hashset_types.h"

#ifndef HAS_HASHSET
#error "+HAS_HASHSET"
#endif

uint32_t hashset_get_spare(HashSet_t* const instance) ;
uint32_t hashset_get_count(HashSet_t* const instance);
uint32_t hashset_get_size(HashSet_t* const instance);
uint32_t hashset_check(HashSet_t* instance,  uint8_t* mem, uint32_t  size);

bool hashset_init(HashSet_t* const instance, HashSetEntry_t* heap, uint32_t size);
bool hashset_push(HashSet_t* const instance, const uint8_t* const mem, uint32_t  size);
bool hashset_pull(HashSet_t* const instance, uint8_t* mem, uint32_t  size);

#ifdef __cplusplus
}
#endif

#endif /* HASHSET_H */
