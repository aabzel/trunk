#ifndef EXT_INT_COMMON_TYPES_H
#define EXT_INT_COMMON_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ext_int_const.h"
#include "ext_int_custom_types.h"
#include "sys_config.h"

#define EXT_INT_COMMON_VARIABLES                             \
    uint8_t num;                                             \
    bool interrupt_on;                                       \
    Pad_t Pad;                                               \
    uint8_t irq_priority;                                    \
    PinIntEdge_t edge;                                       \
    bool valid;

typedef struct {
    EXT_INT_COMMON_VARIABLES
    char* name;
} ExtIntConfig_t;

#define EXT_INT_ISR_VARIABLES                               \
    volatile bool it_done;                                  \
    volatile bool rising_done;                              \
    volatile bool falling_done;                             \
    volatile uint32_t rising_cnt;                           \
    volatile uint32_t falling_cnt;                          \
    volatile uint32_t both_cnt;                             \
    volatile uint32_t it_cnt;

typedef struct {
    EXT_INT_COMMON_VARIABLES
    EXT_INT_ISR_VARIABLES
    EXT_INT_CUSTOM_VARIABLES
    bool init_done;
} ExtIntHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_COMMON_TYPES_H */
