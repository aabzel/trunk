#ifndef ARRAY_TYPES_H
#define ARRAY_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#include "array_dep.h"

typedef struct  {
    size_t size;
    uint8_t* pArr;
} Array_t;

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_TYPES_H */
