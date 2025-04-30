#ifndef CORE_COMMANDS_H
#define CORE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


#ifdef HAS_LOG_UTILS
#include "ostream.h"
#endif


#ifdef HAS_RV32IMC
#include "rv32imc_commands.h"
#else
#define RV32IMC_COMMANDS
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool core_exeption_command(int32_t argc, char* argv[]);
bool cmd_soft_reboot(int32_t argc, char* argv[]);
bool core_diag_command(int32_t argc, char* argv[]);
bool cmd_try_stack(int32_t argc, char* argv[]);

#define CORE_COMMANDS                                                           \
    RV32IMC_COMMANDS                                                            \
    SHELL_CMD("try_stack", "tstk", cmd_try_stack, "Explore stack RAM"),         \
    SHELL_CMD("soft_reboot", "reboot", cmd_soft_reboot, "Reboot board"),        \
    SHELL_CMD("core_diag", "cd", core_diag_command, "Cortex M4 diag"),

#ifdef __cplusplus
}
#endif

#endif /* CORE_COMMANDS_H */
