#ifndef HASHSET_CONFIG_H
#define HASHSET_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "hashset.h"

#ifndef HAS_HASHSET
#error "+HAS_HASHSET"
#endif

extern HashSet_t HashSetInstance;

#ifdef __cplusplus
}
#endif

#endif /* HASHSET_CONFIG_H */
