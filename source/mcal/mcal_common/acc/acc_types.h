#ifndef ACC_TYPES_H
#define ACC_TYPES_H

#include "std_includes.h"
#include "acc_const.h"


#ifdef HAS_ACC_CUSTOM
#include "acc_custom_types.h"
#else
#define ACC_CUSTOM_VARIABLES
#endif


#define ACC_COMMON_VARIABLES                  \
    char* name;                               \
    uint8_t num;                              \
    bool valid;

typedef struct {
    ACC_COMMON_VARIABLES
}AccConfig_t;

typedef struct {
    ACC_COMMON_VARIABLES
    ACC_CUSTOM_VARIABLES
    bool init;
}AccHandle_t;


#endif /* ACC_TYPES_H */
