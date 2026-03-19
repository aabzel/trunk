#ifndef POWER_MCAL_COMMANDS_H
#define POWER_MCAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_POWER
#error "+HAS_POWER"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_POWER_COMMANDS
#error "+HAS_POWER_COMMANDS"
#endif

#ifdef HAS_POWER_CUSTOM_COMMANDS
#include "power_custom_commands.h"
#else
#define POWER_CUSTOM_COMMANDS
#endif

bool power_diag_command(int32_t argc, char* argv[]);
bool power_init_command(int32_t argc, char* argv[]);

#define POWER_COMMANDS                                                              \
    POWER_CUSTOM_COMMANDS                                                           \
    SHELL_CMD("power_diag", "pdd", power_diag_command, "PowerDiag"),                    \
    SHELL_CMD("power_init", "pdi", power_init_command, "PowerInit"),

#ifdef __cplusplus
}
#endif

#endif /* POWER_CUSTOM_COMMANDS_H */
