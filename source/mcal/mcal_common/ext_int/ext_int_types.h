#ifndef EXT_INT_COMMON_TYPES_H
#define EXT_INT_COMMON_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ext_int_const.h"
#include "gpio_types.h"
#include "microcontroller_const.h"

#ifdef HAS_EXT_INT_CUSTOM
#include "ext_int_custom_types.h"
#else
#define EXT_INT_CUSTOM_VARIABLES
#endif

#define EXT_INT_COMMON_VARIABLES                             \
    uint8_t num;                                             \
    uint8_t irq_priority;                                    \
    bool interrupt_on;                                       \
    Pad_t Pad;                                               \
    char* name;                                              \
    PinIntEdge_t edge;                                       \
    bool valid;

typedef struct {
    EXT_INT_COMMON_VARIABLES
} ExtIntConfig_t;

#define EXT_INT_ISR_VARIABLES                               \
    volatile bool it_done;                                  \
    volatile bool unprocessed;                              \
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
