#ifndef CLOCK_MIK32_COMMANDS_H
#define CLOCK_MIK32_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLOCK_COMMANDS
#error "+HAS_CLOCK_COMMANDS"
#endif

bool clock_mik_diag_command(int32_t argc, char* argv[]);

#define CLOCK_CUSTOM_COMMANDS                                                    \
    SHELL_CMD("clock_mik_diag", "clsd", clock_mik_diag_command, "ClockMikDiag"),

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_MIK32_COMMANDS_H */
