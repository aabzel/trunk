#ifndef EXT_INT_COMMANDS_H
#define EXT_INT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_EXT_INT
#error "+HAS_EXT_INT"
#endif

#ifndef HAS_EXT_INT_COMMANDS
#error "+HAS_EXT_INT_COMMANDS"
#endif

#ifdef HAS_EXT_INT_CUSTOM_COMMANDS
#include "ext_int_custom_commands.h"
#else
#define EXT_INT_CUSTOM_COMMANDS
#endif

bool ext_int_init_command(int32_t argc, char* argv[]);
bool ext_int_diag_command(int32_t argc, char* argv[]);

#define EXT_INT_COMMANDS                                                         \
    EXT_INT_CUSTOM_COMMANDS                                                      \
    SHELL_CMD("ext_int_init", "eii", ext_int_init_command, "ExtIntInit"),        \
    SHELL_CMD("ext_int_diag", "eid", ext_int_diag_command, "ExtInt diag"),

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_COMMANDS_H */
