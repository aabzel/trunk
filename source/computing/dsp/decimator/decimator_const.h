#ifndef DECIMATOR_CONST_H
#define DECIMATOR_CONST_H

#include "decimator_dep.h"

#define DECIMATOR_DATA_INVALID (-3)

typedef enum {
    DECIMATOR_STATE_ONE = 1,
    DECIMATOR_STATE_ZERO = 2,
    DECIMATOR_STATE_IDLE = 3,
    DECIMATOR_STATE_UNDEF = 0,
}DecimatorState_t;

typedef enum {
    DECIMATOR_INPUT_ONE = 1,
    DECIMATOR_INPUT_ZERO = 2,
    DECIMATOR_INPUT_OVERFLOW = 3,
    DECIMATOR_INPUT_UNDEF = 0,
}DecimatorInput_t;

#endif /* DECIMATOR_CONST_H  */
