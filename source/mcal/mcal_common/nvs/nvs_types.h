#ifndef NVS_MCAL_TYPES_H
#define NVS_MCAL_TYPES_H

#include "std_includes.h"

#include "nvs_const.h"

#define NVS_COMMON_VARIABLE   \
    uint32_t num;             \
    uint32_t start;           \
    uint32_t size;            \
    bool valid;

typedef struct{
    NVS_COMMON_VARIABLE
}NvsConfig_t;

typedef struct{
    NVS_COMMON_VARIABLE
}NvsItem_t;



#endif /* NVS_MCAL_TYPES_H  */
