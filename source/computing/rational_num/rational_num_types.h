#ifndef RATIONAL_NUM_TYPES_H
#define RATIONAL_NUM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

typedef struct {
    int32_t integer;
    uint32_t fractional;
    uint32_t accurancy; /*number of digits after the decimal point*/
} FloatFixPoint_t;


#ifdef __cplusplus
}
#endif

#endif /*RATIONAL_NUM_TYPES_H*/
