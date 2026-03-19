#ifndef LOCKSTEP_COMMANDS_H
#define LOCKSTEP_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#ifdef HAS_LOCKSTEP_CUSTOM_COMMANDS
#include "lockstep_custom_commands.h"
#else
#define LOCKSTEP_CUSTOM_COMMANDS
#endif

#ifndef HAS_LOCKSTEP
#error "+HAS_LOCKSTEP"
#endif /*HAS_LOCKSTEP*/

#ifndef HAS_LOCKSTEP_COMMANDS
#error "+HAS_LOCKSTEP_COMMANDS"
#endif

bool lockstep_init_command(int32_t argc, char* argv[]);
bool lockstep_diag_command(int32_t argc, char* argv[]);

#define LOCKSTEP_COMMANDS                                                        \
    LOCKSTEP_CUSTOM_COMMANDS                                                     \
    SHELL_CMD("lockstep_init", "lsi", lockstep_init_command, "LockStepInit"),     \
    SHELL_CMD("lockstep_diag", "lsd", lockstep_diag_command, "LockStepDiag"),

#ifdef __cplusplus
}
#endif

#endif /* LOCKSTEP_COMMANDS_H */
