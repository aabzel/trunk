#ifndef CLOCK_CUSTOM_COMMANDS_H
#define CLOCK_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLOCK_COMMANDS
#error "+HAS_CLOCK_COMMANDS"
#endif

bool clock_custom_diag_command(int32_t argc, char* argv[]);

#define CLOCK_CUSTOM_COMMANDS                                                                                                 \
    SHELL_CMD("clock_custom_diag", "clsd", clock_custom_diag_command, "ClockCustomDiag"),

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_CUSTOM_COMMANDS_H */
