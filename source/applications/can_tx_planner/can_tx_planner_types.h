#ifndef CAN_TX_PLANNER_TYPES_H
#define CAN_TX_PLANNER_TYPES_H

#include "std_includes.h"
#include "can_tx_planner_const.h"
#include "can_types.h"


#define CAN_TX_PLANNER_COMMON_VARIABLES                \
    uint8_t num;                                       \
    char* name;                                        \
    CanMessage_t TxMessage;                            \
    uint32_t tx_period_ms;                             \
    bool on;                                           \
    bool valid;

typedef struct {
    CAN_TX_PLANNER_COMMON_VARIABLES
}CanTxPlannerConfig_t;

typedef struct {
    CAN_TX_PLANNER_COMMON_VARIABLES
    bool init;
    uint32_t tx_cnt;
    uint32_t tx_next_ms;
    uint32_t time_stamp_prev_ms;
    uint32_t tx_period_real_ms;
    uint32_t spin;
}CanTxPlannerHandle_t;


#endif /* CAN_TX_PLANNER_TYPES_H */
