#ifndef INCREMENTAL_ENCODER_TYPES_H
#define INCREMENTAL_ENCODER_TYPES_H

#include "gpio_types.h"
#include "std_includes.h"
#include "incremental_encoder_const.h"
#include "storage_const.h"

#ifdef HAS_EXT_INT_EVENT_FIFO
#include "lib_iqueue.h"
#endif

typedef struct {
    IncrementalEncoderState_t state;
    IncrementalEncoderInput_t input;
    uint32_t timestamp_us;
}IncrementalEncoderEvent_t;

#define INCREMENTAL_ENCODER_COMMON_VARIABLES          \
    char* name;                                       \
    IncrementalEncoderEvent_t* EventMem;              \
    int32_t limit_up;                                 \
    int32_t limit_down;                               \
    uint32_t event_mem_size;                          \
    uint32_t cnt_pre_revolution;                      \
    uint8_t num;                                      \
    Pad_t PadA;                                       \
    StoragePhysicalQuantity_t physical_quantity; /*Length mass time current*/   \
    StorageUnits_t Units; /*Meter Foot Inch Yard mile*/    \
    StorageScale_t Scale;                          \
    Pad_t PadB;                                       \
    bool valid;


typedef struct {
    INCREMENTAL_ENCODER_COMMON_VARIABLES
}IncrementalEncoderConfig_t;

typedef struct {
    INCREMENTAL_ENCODER_COMMON_VARIABLES
    bool init;
    uint32_t spin;
    uint32_t error_cnt;
    uint32_t prev_event_time_us;
    int32_t cnt;
    int32_t cnt_limited;
    int32_t revolutions;
    IncrementalEncoderInput_t input;
    IncrementalEncoderState_t logic_state;
    IncrementalEncoderState_t new_state;
    IncrementalEncoderState_t prev_state;
#ifdef HAS_IQUEUE
    iqueue_t iQueue;
#endif
}IncrementalEncoderHandle_t;


#endif /* INCREMENTAL_ENCODER_TYPES_H */
