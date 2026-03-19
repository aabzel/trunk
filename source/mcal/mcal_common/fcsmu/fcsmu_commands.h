#ifndef FCSMU_COMMANDS_H
#define FCSMU_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_FCSMU_CUSTOM_COMMANDS
#include "fcsmu_custom_commands.h"
#else
#define FCSMU_CUSTOM_COMMANDS
#endif

#ifndef HAS_FCSMU
#error "+HAS_FCSMU"
#endif /*HAS_FCSMU*/

#ifndef HAS_FCSMU_COMMANDS
#error "+HAS_FCSMU_COMMANDS"
#endif

bool fcsmu_diag_int_command(int32_t argc, char* argv[]);
bool fcsmu_init_command(int32_t argc, char* argv[]);
bool fcsmu_diag_command(int32_t argc, char* argv[]);

#define FCSMU_COMMANDS                                                                     \
    FCSMU_CUSTOM_COMMANDS                                                                  \
    SHELL_CMD("fcsmu_init", "fci", fcsmu_init_command, "FcsmuInit"),                       \
    SHELL_CMD("fcsmu_diag", "fcsd", fcsmu_diag_command, "FcsmuDiag"),

#ifdef __cplusplus
}
#endif

#endif /* FCSMU_COMMANDS_H */
