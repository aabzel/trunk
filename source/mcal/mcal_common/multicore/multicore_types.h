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

/* structure for selecting a config for a specific processing unit (PE) */
typedef union{
    uint8_t byte;
    struct {
        uint8_t core0 :1;
        uint8_t core1 :1;
        uint8_t core2 :1;
        uint8_t res:5;
    };
}Cores_t;

#define MULTICORE_COMMON_VARIABLES                                          \
    uint32_t vector_base;                                                   \
    uint32_t reset_handler;                                                 \
    uint8_t num;                                                            \
    char* name;                                                             \
    bool valid;

typedef struct {
    MULTICORE_COMMON_VARIABLES
} MultiCoreConfig_t;

typedef struct {
    MULTICORE_COMMON_VARIABLES
    MULTICORE_CUSTOM_VARIABLES
    bool init;
    bool ready;
} MultiCoreHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_COMMON_TYPES_H */
