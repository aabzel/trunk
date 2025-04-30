#ifndef EXT_INT_COMMANDS_H
#define EXT_INT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_EXT_INT
#error "+HAS_EXT_INT"
#endif /*HAS_EXT_INT*/

#ifndef HAS_EXT_INT_COMMANDS
#error "+HAS_EXT_INT_COMMANDS"
#endif

bool ext_int_init_command(int32_t argc, char* argv[]);
bool ext_int_diag_command(int32_t argc, char* argv[]);

#define EXT_INT_COMMANDS                                                                                \
    SHELL_CMD("ext_int_init", "eii", ext_int_init_command, "ExtIntInit"),                               \
    SHELL_CMD("ext_int_diag", "eid", ext_int_diag_command, "ExtInt diag"),

#ifdef __cplusplus
}
#endif

#endif /* EXT_INT_COMMANDS_H */
