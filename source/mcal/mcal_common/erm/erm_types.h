#ifndef ERM_COMMON_TYPES_H
#define ERM_COMMON_TYPES_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "erm_const.h"

#ifdef HAS_ERM_CUSTOM
#include "erm_custom_types.h"
#else
#define ERM_CUSTOM_VARIABLES
#endif

#define ERM_COMMON_VARIABLES                                                \
    uint8_t num;                                                            \
    bool interrupt_on;                                                      \
    char* name;                                                             \
    bool valid;

typedef struct {
    ERM_COMMON_VARIABLES
} ErmConfig_t;

#define ERM_ISR_VARIABLES        \
    volatile bool it_done;       \
    volatile uint32_t it_cnt;

typedef struct {
    ERM_COMMON_VARIABLES
    ERM_CUSTOM_VARIABLES
    ERM_ISR_VARIABLES
    bool init_done;
} ErmHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* ERM_COMMON_TYPES_H */
