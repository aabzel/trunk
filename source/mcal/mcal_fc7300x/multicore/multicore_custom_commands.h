#ifndef MULTICORE_CUSTOM_COMMANDS_H
#define MULTICORE_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool multicore_custom_diag_command(int32_t argc, char* argv[]);
bool multicore_reset_command(int32_t argc, char* argv[]);

#define MULTICORE_CUSTOM_COMMANDS     \
    SHELL_CMD("multicore_reset", "mcr", multicore_reset_command, "MultiCoreCustomReset"),       \
    SHELL_CMD("multicore_custom_diag", "mccd", multicore_custom_diag_command, "MultiCoreCustomDiag"),

#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_CUSTOM_COMMANDS_H */
