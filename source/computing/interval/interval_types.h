#ifndef INTERVAL_TYPES_H
#define INTERVAL_TYPES_H

#include <stdint.h>

#include "interval_const.h"

typedef struct {
    uint32_t val;
    IntervalPoint_t type;
} IntervalPoints_t;

typedef struct {
    uint32_t start;
    uint32_t end;
} IntervalE_t;

typedef struct {
    uint32_t start;
    uint32_t size;
} IntervalS_t;

#endif
