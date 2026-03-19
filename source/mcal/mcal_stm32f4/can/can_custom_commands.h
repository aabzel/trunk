#ifndef CAN_CUSTOM_COMMANDS_H
#define CAN_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "can_registers_commands.h"

bool can_diag_custom_command(int32_t argc, char* argv[]);
bool can_diag_tx_mailbox_command(int32_t argc, char* argv[]);
bool can_diag_filters_command(int32_t argc, char* argv[]);

#define CAN_CUSTOM_DIAG_COMMANDS                                                              \
    SHELL_CMD("can_diag_filers", "cdf", can_diag_filters_command, "CanDiagFilters"),          \
    SHELL_CMD("can_diag_custom", "cdc", can_diag_custom_command, "CanDiagCustom"),            \
    SHELL_CMD("can_diag_tx_mailbox", "cdtm", can_diag_tx_mailbox_command, "CanDiagTxMailBox"),

bool can_interrupt_command(int32_t argc, char* argv[]);

#define CAN_CUSTOM_COMMANDS                                                        \
    CAN_CUSTOM_DIAG_COMMANDS                                                       \
    CAN_REGISTERS_DIAG_COMMANDS                                                    \
    SHELL_CMD("can_interrupt", "cani", can_interrupt_command, "CanInterrupt"),




#ifdef __cplusplus
}
#endif

#endif /* CAN_CUSTOM_COMMANDS_H */
