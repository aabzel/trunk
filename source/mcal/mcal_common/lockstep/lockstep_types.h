#ifndef LOCKSTEP_COMMON_TYPES_H
#define LOCKSTEP_COMMON_TYPES_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "lockstep_const.h"

#ifdef HAS_LOCKSTEP_CUSTOM
#include "lockstep_custom_types.h"
#else
#define LOCKSTEP_CUSTOM_VARIABLES
#endif

#ifndef HAS_LOCKSTEP
#error "+HAS_LOCKSTEP"
#endif /*HAS_LOCKSTEP*/

#define LOCKSTEP_COMMON_VARIABLES                                           \
    uint8_t num;                                                            \
    bool interrupt_on;                                                      \
    char* name;                                                             \
    bool valid;

typedef struct {
    LOCKSTEP_COMMON_VARIABLES
    /* irq_priority*/
} LockStepConfig_t;

#define LOCKSTEP_ISR_COMMON_IT_VARIABLES          \
        volatile bool it_done;                    \
        volatile uint32_t it_cnt;

#define LOCKSTEP_ISR_COMMON_VARIABLES             \
        LOCKSTEP_ISR_COMMON_IT_VARIABLES

typedef struct {
    LOCKSTEP_COMMON_VARIABLES
    LOCKSTEP_ISR_COMMON_VARIABLES
    LOCKSTEP_CUSTOM_VARIABLES
    bool init;
    uint32_t spin;
} LockStepHandle_t;

#ifdef __cplusplus
}
#endif

#endif /* LOCKSTEP_COMMON_TYPES_H */
