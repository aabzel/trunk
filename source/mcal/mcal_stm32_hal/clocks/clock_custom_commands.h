#ifndef CLOCK_CUSTOM_COMMANDS_H
#define CLOCK_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLOCK_COMMANDS
#error "+HAS_CLOCK_COMMANDS"
#endif

bool clock_custom_periph_diag_command(int32_t argc, char* argv[]);
bool clock_custom_core_diag_command(int32_t argc, char* argv[]);

#define CLOCK_CUSTOM_COMMANDS                                                                                          \
    SHELL_CMD("clock_custom_core_diag", "cccd", clock_custom_core_diag_command, "ClockCoreDiag"),                      \
    SHELL_CMD("clock_custom_periph_diag", "ccpd", clock_custom_periph_diag_command, "ClockPeriphDiag"),

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_CUSTOM_COMMANDS_H */
