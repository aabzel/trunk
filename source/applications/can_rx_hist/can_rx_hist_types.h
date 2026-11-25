#ifndef CAN_RX_HIST_TYPES_H
#define CAN_RX_HIST_TYPES_H

#include "std_includes.h"
#include "can_types.h"
#include "can_rx_hist_const.h"

typedef struct {
    uint32_t up_time_prev_ms;
    uint32_t rx_period_ms;
    uint32_t rx_cnt;
    CanMessage_t Message;
}CanRxMesgInfo_t;


#define CAN_RX_HIST_COMMON_VARIABLES                   \
    char* name;                                        \
    uint8_t num;                                       \
    uint8_t can_num;                                   \
    uint32_t rx_mesg_array_cnt;                        \
    CanRxMesgInfo_t* RxMesgArray;                      \
    bool valid;

typedef struct {
    CAN_RX_HIST_COMMON_VARIABLES
}CanRxHistConfig_t;

typedef struct {
    CAN_RX_HIST_COMMON_VARIABLES
    bool init;
    uint32_t spin;
}CanRxHistHandle_t;


#endif /* CAN_RX_HIST_TYPES_H */
