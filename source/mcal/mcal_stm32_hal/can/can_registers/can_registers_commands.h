#ifndef CAN_REGISTER_COMMANDS_H
#define CAN_REGISTER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool can_raw_reg_command(int32_t argc, char* argv[]);
bool can_diag_low_level_command(int32_t argc, char* argv[]);


#define CAN_REGISTERS_DIAG_COMMANDS                                                                    \
    SHELL_CMD("can_diag_low_level", "candl", can_diag_low_level_command, "CanDiagLowLevel"),           \
    SHELL_CMD("can_raw_reg", "canra", can_raw_reg_command, "CanDiagRawReg"),

#ifdef __cplusplus
}
#endif

#endif /* CAN_REGISTER_COMMANDS_H */
