#ifndef FLOAT_DIAG_H
#define FLOAT_DIAG_H

#include "float_types.h"

#ifdef HAS_RATIONAL_NUM
#include "rational_num_types.h"
#endif

#define VAL_TO_NANO_VAL(VALUE) ((VALUE) * 1000000000.0)

const char* FloatBigToStr(const float value);
const char * FloatToStr(const float real_val, const  uint32_t digit);

#ifdef HAS_RATIONAL_NUM
const char * FloatFixToStr(const FloatFixPoint_t* const  Node);
#endif


#endif /* FLOAT_DIAG_H */









