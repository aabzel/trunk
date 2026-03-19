#ifndef ERM_COMMANDS_H
#define ERM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ostream.h"

#ifdef HAS_ERM_CUSTOM_COMMANDS
#include "erm_custom_commands.h"
#else
#define ERM_CUSTOM_COMMANDS
#endif

#ifndef HAS_ERM
#error "+HAS_ERM"
#endif /*HAS_ERM*/

#ifndef HAS_ERM_COMMANDS
#error "+HAS_ERM_COMMANDS"
#endif

bool erm_init_command(int32_t argc, char* argv[]);
bool erm_diag_command(int32_t argc, char* argv[]);

#define ERM_COMMANDS                                                                                                   \
    ERM_CUSTOM_COMMANDS                                                                                                \
    SHELL_CMD("erm_init", "ermn", erm_init_command, "ErmInit"),                                                        \
    SHELL_CMD("erm_diag", "spd", erm_diag_command, "Erm diag"),

#ifdef __cplusplus
}
#endif

#endif /* ERM_COMMANDS_H */
