#ifndef CAN_TX_PLANNER_CONFIG_H
#define CAN_TX_PLANNER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_tx_planner_types.h"
#include "can_tx_planner_dep.h"

extern const CanTxPlannerConfig_t CanTxPlannerConfig[];
extern CanTxPlannerHandle_t CanTxPlannerInstance[];

uint32_t can_tx_planner_get_cnt(void);
uint32_t can_tx_planner_get_cells(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_TX_PLANNER_CONFIG_H */
