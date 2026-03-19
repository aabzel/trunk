#ifndef POWER_TYPES_H
#define POWER_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#include "power_const.h"

#ifdef HAS_POWER_CUSTOM
#include "power_custom_types.h"
#else
#define POWER_CUSTOM_VARIABLES
#endif


#define POWER_COMMON_VARIABLES             \
    uint8_t num;                           \
    bool valid;

typedef struct {
    POWER_COMMON_VARIABLES
    PowerMode_t mode;
    char* name;
} PowerConfig_t;

typedef struct {
    POWER_COMMON_VARIABLES
    POWER_CUSTOM_VARIABLES
} PowerHandle_t;

#endif /* POWER_TYPES_H */
