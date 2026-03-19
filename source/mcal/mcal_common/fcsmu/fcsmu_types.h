#ifndef FCSMU_COMMON_TYPES_H
#define FCSMU_COMMON_TYPES_H

#include "std_includes.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "fcsmu_const.h"

#ifdef HAS_FCSMU_CUSTOM
#include "fcsmu_custom_types.h"
#else
#define FCSMU_CUSTOM_VARIABLES
#endif

#define FCSMU_COMMON_VARIABLES                         \
    uint8_t num;                                       \
    char* name;                                        \
    bool interrupt_on;                                 \
    bool valid;

typedef struct {
    FCSMU_COMMON_VARIABLES
} FcsmuConfig_t;


#define FCSMU_ISR_VARIABLES              \
    volatile uint32_t channel_mask;      \
    volatile uint32_t it_cnt;            \
    volatile bool it_done;

typedef struct {
    FCSMU_COMMON_VARIABLES
    FCSMU_CUSTOM_VARIABLES
    FCSMU_ISR_VARIABLES
    uint8_t init;
    uint32_t spin;
} FcsmuHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* FCSMU_COMMON_TYPES_H */
