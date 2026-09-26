#ifndef CLOCK_CUSTOM_COMMANDS_H
#define CLOCK_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLOCK_COMMANDS
#error "+HAS_CLOCK_COMMANDS"
#endif

bool clock_custom_diag_command(int32_t argc, char* argv[]);
bool clock_raw_reg_command(int32_t argc, char* argv[]);
bool clock_peripheral_diag_command(int32_t argc, char* argv[]);
bool clock_diag_frequency_command(int32_t argc, char* argv[]);
bool clock_frequency_get_command(int32_t argc, char* argv[]);

#define CLOCK_CUSTOM_COMMANDS                                                                     \
    SHELL_CMD("clock_peripheral_diag", "clpd", clock_peripheral_diag_command, "ClockPeriphDiag"), \
    SHELL_CMD("clock_frequency_get", "clfg", clock_frequency_get_command, "ClockFreqGet"),        \
    SHELL_CMD("clock_diag_frequency", "cldf", clock_diag_frequency_command, "ClockDiagFreq"),     \
    SHELL_CMD("clock_custom_diag", "clsd", clock_custom_diag_command, "ClockCustomDiag"),         \
    SHELL_CMD("clock_raw_reg", "creg", clock_raw_reg_command, "ClockRawReg"),

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_CUSTOM_COMMANDS_H */
