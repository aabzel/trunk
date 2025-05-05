#ifndef NOR_AUTO_VERSION_TYPES_H
#define NOR_AUTO_VERSION_TYPES_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "data_types.h"
#include "auto_version_const.h"

#define AUTO_VERSION_COMMON_VARIABLES                                                                               \
    bool valid;                                                                                                        \
    char filename[30];

typedef struct {
    AUTO_VERSION_COMMON_VARIABLES
} AutoVersionConfig_t;

typedef struct {
    AUTO_VERSION_COMMON_VARIABLES
    bool init;
    bool spot_version;
    uint32_t number_of_builds;
    uint32_t number_of_builds_new;
} AutoVersionHandle_t;

#endif /* NOR_AUTO_VERSION_TYPES_H */
