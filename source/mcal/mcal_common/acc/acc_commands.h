#ifndef ACC_COMMANDS_H
#define ACC_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_ACC_CUSTOM_COMMANDS
#include "acc_custom_commands.h"
#else
#define ACC_CUSTOM_COMMANDS
#endif


#ifndef HAS_ACC
#error "+ HAS_ACC"
#endif

#ifndef HAS_ACC_COMMANDS
#error "+ HAS_ACC_COMMANDS"
#endif

bool acc_diag_command(int32_t argc, char* argv[]);
bool acc_init_command(int32_t argc, char* argv[]);
bool acc_reg_map_command(int32_t argc, char* argv[]);

#define ACC_COMMANDS                                                                                          \
        ACC_CUSTOM_COMMANDS                                                                                   \
        SHELL_CMD("acc_diag", "acd", acc_diag_command, "AccDiag"),                           \
        SHELL_CMD("acc_init", "aci", acc_init_command, "AccInit"),                           \
        SHELL_CMD("acc_reg_map", "acrm", acc_reg_map_command, "AccRawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* ACC_COMMANDS_H */
