#ifndef ANALOG_CONST_H
#define ANALOG_CONST_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


typedef enum {
    ANALOG_MAX_VAL_6BIT = 63,
    ANALOG_MAX_VAL_8BIT = 255,
    ANALOG_MAX_VAL_10BIT = 1023,
    ANALOG_MAX_VAL_12BIT = 4095,
    ANALOG_MAX_VAL_14BIT = 16383,
    ANALOG_MAX_VAL_UNDEF = 0,
} AdcMaxVal_t;




#ifdef __cplusplus
}
#endif

#endif /* ANALOG_CONST_H */
