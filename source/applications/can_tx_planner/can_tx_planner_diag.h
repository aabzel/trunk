#ifndef CAN_TX_PLANNER_DIAG_H
#define CAN_TX_PLANNER_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_tx_planner_types.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_CAN_TX_PLANNER
#error "+HAS_CAN_TX_PLANNER"
#endif

#ifndef HAS_CAN_TX_PLANNER_DIAG
#error "+HAS_CAN_TX_PLANNER_DIAG"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

bool can_tx_planner_diag(void);
bool can_tx_planner_diag_one(uint8_t num);
const char* CanTxPlannerConfigToStr(const CanTxPlannerConfig_t* const Config);
const char* CanTxPlannerNodeToStr(const CanTxPlannerHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* CAN_TX_PLANNER_DIAG_H  */
