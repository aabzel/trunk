#ifndef CAN_CUSTOM_COMMANDS_H
#define CAN_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "can_registers_commands.h"
#include "std_includes.h"

bool can_diag_mail_box_command(int32_t argc, char* argv[]) ;
bool can_diag_custom_command(int32_t argc, char* argv[]);

#define CAN_CUSTOM_DIAG_COMMANDS                                                                       \
    SHELL_CMD("can_diag_custom", "cdc", can_diag_custom_command, "CanDiagCustom"),

bool can_send_sdk_command(int32_t argc, char* argv[]);

#define CAN_CUSTOM_COMMANDS                                                                          \
   CAN_REGISTERS_DIAG_COMMANDS                                                                       \
   CAN_CUSTOM_DIAG_COMMANDS                                                                          \
   SHELL_CMD("can_send_sdk", "css", can_send_sdk_command, "CanSendSdkHexStr"),

#ifdef __cplusplus
}
#endif

#endif /* CAN_CUSTOM_COMMANDS_H */
