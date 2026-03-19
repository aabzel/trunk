#ifndef NVS_MCAL_TYPES_H
#define NVS_MCAL_TYPES_H

#include "std_includes.h"
#include "nvs_const.h"

#define NVS_COMMON_VARIABLES                           \
    uint32_t start;                                    \
    uint32_t size;                                     \
    bool valid;                                        \
    uint8_t num;                                       \
    char* name;                                        \

typedef struct {
    NVS_COMMON_VARIABLES
}NvsConfig_t;

typedef struct {
    NVS_COMMON_VARIABLES
    bool init;
    uint32_t spin;
}NvsHandle_t;



#endif /* NVS_MCAL_TYPES_H  */
