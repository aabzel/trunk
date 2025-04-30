#ifndef CORE_COMMANDS_H
#define CORE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool cmd_soft_reboot(int32_t argc, char* argv[]);
bool vector_table_command(int32_t argc, char* argv[]);
bool core_diag_command(int32_t argc, char* argv[]);
bool cmd_try_stack(int32_t argc, char* argv[]);

#define CORTEX_M4_COMMANDS                                                                                         \
    SHELL_CMD("vector_table", "vt", vector_table_command, "Cortex M4 vector table"),                               \
    SHELL_CMD("try_stack", "tstk", cmd_try_stack, "Explore stack RAM"),                                            \
    SHELL_CMD("soft_reboot", "reboot", cmd_soft_reboot, "Reboot board"),                                           \
    SHELL_CMD("core_diag", "cd", core_diag_command, "Cortex M4 diag"),

#ifdef __cplusplus
}
#endif

#endif /* CORE_COMMANDS_H */
