#ifndef FLOAT_TYPES_H
#define FLOAT_TYPES_H

#include <stdint.h>


typedef union{
    uint32_t u32;
    float flt;
    struct {
    	uint32_t significand :23;
		uint32_t exponent :8;
		uint32_t sign :1;
    };
} FloatUnion_t;

typedef struct{
    int32_t integer;
    uint32_t  fractional;
}FloatFixPoint_t;



#endif /* FLOAT_TYPES_H */
