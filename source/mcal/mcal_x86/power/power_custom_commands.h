#ifndef POWER_CUSTOM_COMMANDS_H
#define POWER_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_POWER
#error "+HAS_POWER"
#endif /*HAS_POWER*/

#ifndef HAS_POWER_COMMANDS
#error "+HAS_POWER_COMMANDS"
#endif /*HAS_POWER_COMMANDS*/

bool power_diag_low_level_command(int32_t argc, char* argv[]);
bool power_raw_reg_command(int32_t argc, char* argv[]);

#define POWER_CUSTOM_COMMANDS                                                                       \
    SHELL_CMD("power_raw_reg", "powerra", power_raw_reg_command, "PowerRawReg"),                          \
    SHELL_CMD("power_diag_low_level", "powerdl", power_diag_low_level_command, "PowerDiagLowLevel"),


#ifdef __cplusplus
}
#endif

#endif /* POWER_CUSTOM_COMMANDS_H */
