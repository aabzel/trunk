#ifndef EXT_INT_COMMON_TYPES_H
#define EXT_INT_COMMON_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ext_int_const.h"
#include "gpio_types.h"
#include "microcontroller_const.h"
#include "mcal_types.h"

#ifdef HAS_IQUEUE
#include "lib_iqueue.h"
#endif

#ifdef HAS_EXT_INT_CUSTOM
#include "ext_int_custom_types.h"
#else
#define EXT_INT_CUSTOM_VARIABLES
#endif

typedef struct {
    PinIntDrop_t drop;
    uint32_t timestamp_us;
} ExtIntEvent_t;


#define EXT_INT_COMMON_VARIABLES                             \
    bool fifo_pull;                                          \
    uint8_t num;                                             \
    uint8_t irq_priority;                                    \
    McalCallBack_t CallBackRising;                           \
    McalCallBack_t CallBackFalling;                          \
    PinIntEdge_t edge;                                       \
    Pad_t Pad;                                               \
    ExtIntEvent_t* EventMem;                                 \
    uint32_t event_mem_size;                                 \
    char* name;                                              \
    bool valid;

typedef struct {
    EXT_INT_COMMON_VARIABLES
} ExtIntConfig_t;

#define EXT_INT_ISR_FALLING_VARIABLES                       \
    volatile bool falling_done;                             \
    volatile uint32_t falling_cnt;

#define EXT_INT_ISR_RISING_VARIABLES                        \
    volatile bool rising_done;                              \
    volatile uint32_t rising_cnt;


#define EXT_INT_ISR_BOTH_VARIABLES  \
    volatile bool it_done;                                  \
    volatile uint32_t both_cnt;                             \
    volatile uint32_t it_cnt;

#define EXT_INT_ISR_VARIABLES                               \
    EXT_INT_ISR_FALLING_VARIABLES                           \
    EXT_INT_ISR_RISING_VARIABLES                            \
    EXT_INT_ISR_BOTH_VARIABLES                              \
    volatile bool unprocessed;

typedef struct {
    EXT_INT_COMMON_VARIABLES
    EXT_INT_CUSTOM_VARIABLES
    EXT_INT_ISR_VARIABLES
    bool init_done;
    PinIntEdge_t edge_effective;
    ExtIntEvent_t PrevEvent;
    uint32_t prev_event_time_us;
    // TODO add event fifo TimeStamp and event ExtIntEvent_t
#ifdef HAS_IQUEUE
    iqueue_t iQueue;
#endif
} ExtIntHandle_t;


#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_COMMON_TYPES_H */
