#ifndef EIM_MCAL_TYPES_H
#define EIM_MCAL_TYPES_H

#include "std_includes.h"
#include "eim_const.h"
#ifdef HAS_EIM_CUSTOM
#include "eim_custom_types.h"
#else
#define EIM_CUSTOM_VARIABLES
#endif

#define EIM_COMMON_VARIABLES     \
    bool interrupt_on;           \
    uint8_t num;                 \
    char *name;                  \
    bool valid;

typedef struct {
    EIM_COMMON_VARIABLES
}EimConfig_t;

typedef struct {
    EIM_COMMON_VARIABLES
    EIM_CUSTOM_VARIABLES
    volatile bool it_done;
    volatile uint32_t it_cnt;
    bool init;
} EimHandle_t;

#endif /* EIM_MCAL_TYPES_H */
