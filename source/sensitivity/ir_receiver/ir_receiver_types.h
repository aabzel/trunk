#ifndef IR_RECEIVER_TYPES_H
#define IR_RECEIVER_TYPES_H

#include "std_includes.h"
#include "ir_receiver_const.h"
#include "gpio_types.h"

typedef struct {
    PinIntEdge_t event;
    uint32_t up_time_us;
}IrReceiverEvent_t;

#define IR_RECEIVER_COMMON_VARIABLES                   \
    char* name;                                        \
    uint8_t num;                                       \
    Pad_t IrPad;                                       \
    IrReceiverEvent_t* signal_cur;                     \
    IrReceiverEvent_t* signal_fix;                     \
    uint32_t signal_size;                              \
    uint32_t exp_size;                                 \
    uint8_t timer_num;                                 \
    bool valid;

typedef struct {
    IR_RECEIVER_COMMON_VARIABLES
}IrReceiverConfig_t;



typedef struct {
    IR_RECEIVER_COMMON_VARIABLES
    bool init;
    bool spot_frame;
    uint32_t time_stamp_prev_us;
    uint32_t rx_time_ms;
    uint32_t spin;
    uint32_t event_i;
}IrReceiverHandle_t;


#endif /* IR_RECEIVER_TYPES_H */
