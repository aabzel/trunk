#ifndef CAN_RX_HIST_COMMANDS_H
#define CAN_RX_HIST_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CAN_RX_HIST
#error "+ HAS_CAN_RX_HIST"
#endif

#ifndef HAS_CAN_RX_HIST_COMMANDS
#error "+ HAS_CAN_RX_HIST_COMMANDS"
#endif

bool can_rx_hist_diag_command(int32_t argc, char* argv[]);
bool can_rx_hist_init_command(int32_t argc, char* argv[]);
bool can_traffx_diag_command(int32_t argc, char* argv[]);

#define CAN_RX_HIST_COMMANDS                                                                                        \
        SHELL_CMD("can_traffic", "ctd", can_traffx_diag_command, "CanDiagTraffic"),                           \
        SHELL_CMD("can_rx_hist_diag", "crhd", can_rx_hist_diag_command, "CanRxHistDiag"),                           \
        SHELL_CMD("can_rx_hist_init", "crhi", can_rx_hist_init_command, "CanRxHistInit"),

#ifdef __cplusplus
}
#endif

#endif /* CAN_RX_HIST_COMMANDS_H */
