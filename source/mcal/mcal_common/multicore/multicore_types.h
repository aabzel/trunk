#ifndef MULTICORE_COMMON_TYPES_H
#define MULTICORE_COMMON_TYPES_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "multicore_const.h"

#ifdef HAS_MULTICORE_CUSTOM
#include "multicore_custom_types.h"
#else
#define MULTICORE_CUSTOM_VARIABLES
#endif

#define MULTICORE_COMMON_VARIABLES                                          \
    uint8_t num;                                                            \
    char* name;                                                             \
    bool valid;

typedef struct {
    MULTICORE_COMMON_VARIABLES
} MultiCoreConfig_t;

typedef struct {
    MULTICORE_COMMON_VARIABLES
    MULTICORE_CUSTOM_VARIABLES
    uint8_t init;
    bool ready;
} MultiCoreHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_COMMON_TYPES_H */
