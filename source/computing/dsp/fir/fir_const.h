#ifndef FIR_CONST_H
#define FIR_CONST_H

#include "fir_dep.h"
#define EPSILONT 0.00001

typedef enum{
    FIR_MODE_MOVE_AVARAGE = 1,
    FIR_MODE_CLASSIC = 2,
    FIR_MODE_INTEGRATION= 3,
    FIR_MODE_CORRELATION = 4,
    FIR_MODE_UNDEF= 0,
}FirMode_t;

#endif /* FIR_CONST_H */





