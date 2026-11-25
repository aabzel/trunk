#ifndef CAN_TX_PLANNER_MCAL_H
#define CAN_TX_PLANNER_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_tx_planner_config.h"
#include "can_tx_planner_types.h"
#ifdef HAS_CAN_TX_PLANNER_DIAG
#include "can_tx_planner_diag.h"
#endif

/* API */
CanTxPlannerHandle_t* CanTxPlannerGetNode(uint8_t num);
CanTxPlannerHandle_t* CanTxPlannerCanNumToNode(uint8_t num);
const CanTxPlannerConfig_t* CanTxPlannerGetConfig(uint8_t num);
bool CanTxPlannerIsValidConfig(const CanTxPlannerConfig_t* const Config);

#ifdef HAS_CAN_TX_PLANNER_CUSTOM
const CanTxPlannerInfo_t* CanTxPlannerGetInfo(uint8_t num);
#endif

bool can_tx_planner_mcal_init(void);
bool can_tx_planner_init_custom(void);
bool can_tx_planner_init_one(uint8_t num);

bool can_tx_planner_proc_one(uint8_t num);
bool can_tx_planner_proc(void);

/*setters*/
bool can_tx_planner_set(const uint8_t num, const bool en, const uint32_t tx_period_ms, const CanMessage_t* const Messg);
bool can_tx_planner_set_period(const uint8_t num,
                               const uint32_t tx_period_ms);

/*getters*/

#ifdef __cplusplus
}
#endif

#endif /* CAN_TX_PLANNER_MCAL_H */
