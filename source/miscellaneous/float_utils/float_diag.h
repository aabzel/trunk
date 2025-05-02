#ifndef FLOAT_DIAG_H
#define FLOAT_DIAG_H


#include "float_types.h"


char * FloatToStr(const float real_val, const  uint32_t digit);

char * FloatFixToStr(const FloatFixPoint_t* const  Node,
                     const uint32_t digit);


#endif /* FLOAT_DIAG_H */









