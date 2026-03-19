#ifndef MULTICORE_COMMANDS_H
#define MULTICORE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_MULTICORE_CUSTOM_COMMANDS
#include "multicore_custom_commands.h"
#else
#define MULTICORE_CUSTOM_COMMANDS
#endif

#ifndef HAS_MULTICORE
#error "+HAS_MULTICORE"
#endif /*HAS_MULTICORE*/

#ifndef HAS_MULTICORE_COMMANDS
#error "+HAS_MULTICORE_COMMANDS"
#endif

bool multicore_diag_int_command(int32_t argc, char* argv[]);
bool multicore_init_command(int32_t argc, char* argv[]);
bool multicore_diag_command(int32_t argc, char* argv[]);
bool multicore_control_command(int32_t argc, char* argv[]);
bool multicore_all_command(int32_t argc, char* argv[]);

#define MULTICORE_COMMANDS                                                                     \
    MULTICORE_CUSTOM_COMMANDS                                                                  \
    SHELL_CMD("multicore_ctrl", "mcc", multicore_control_command, "MultiCoreControl"),        \
    SHELL_CMD("multicore_all", "mca", multicore_all_command, "MultiCoreTurnOnAll"),        \
    SHELL_CMD("multicore_init", "mci", multicore_init_command, "MultiCoreInit"),        \
    SHELL_CMD("multicore_diag", "mcd", multicore_diag_command, "MultiCoreDiag"),

#ifdef __cplusplus
}
#endif

#endif /* MULTICORE_COMMANDS_H */
