#ifndef CAN_TX_PLANNER_COMMANDS_H
#define CAN_TX_PLANNER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CAN_TX_PLANNER
#error "+ HAS_CAN_TX_PLANNER"
#endif

#ifndef HAS_CAN_TX_PLANNER_COMMANDS
#error "+ HAS_CAN_TX_PLANNER_COMMANDS"
#endif

bool can_tx_planner_set_period_command(int32_t argc, char* argv[]);
bool can_tx_planner_diag_command(int32_t argc, char* argv[]);
bool can_tx_planner_init_command(int32_t argc, char* argv[]);
bool can_tx_planner_set_command(int32_t argc, char* argv[]);

#define CAN_TX_PLANNER_COMMANDS                                                                       \
        SHELL_CMD("can_tx_planner_set_period", "ctpsp", can_tx_planner_set_period_command, "CanTxPlannerSetPeriod"),       \
        SHELL_CMD("can_tx_planner_set", "ctps", can_tx_planner_set_command, "CanTxPlannerSet"),       \
        SHELL_CMD("can_tx_planner_diag", "ctpd", can_tx_planner_diag_command, "CanTxPlannerDiag"),    \
        SHELL_CMD("can_tx_planner_init", "ctpi", can_tx_planner_init_command, "CanTxPlannerInit"),

#ifdef __cplusplus
}
#endif

#endif /* CAN_TX_PLANNER_COMMANDS_H */
