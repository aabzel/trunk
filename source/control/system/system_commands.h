#ifndef SYSTEM_COMMANDS_H
#define SYSTEM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool system_init_command(int32_t argc, char* argv[]);
bool sys_diag_command(int32_t argc, char* argv[]);
bool sys_rate_command(int32_t argc, char* argv[]);
bool sys_available_interfaces_command(int32_t argc, char* argv[]);

#define SYSTEM_COMMANDS                                                                     \
        SHELL_CMD("sys_init", "syi", system_init_command, "SystemInit"),                    \
        SHELL_CMD("sys_diag", "syd", sys_diag_command, "SystemDiag"),                       \
        SHELL_CMD("sys_if", "syf", sys_available_interfaces_command, "AvailableInterface"), \
        SHELL_CMD("sys_if_rates", "rate", sys_rate_command, "Rate"),

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_COMMANDS_H  */
