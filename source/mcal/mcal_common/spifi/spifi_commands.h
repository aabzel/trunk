#ifndef SPIFI_COMMANDS_H
#define SPIFI_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "spifi_custom_commands.h"

#ifndef HAS_SPIFI
#error "+HAS_SPIFI"
#endif /*HAS_SPIFI*/

#ifndef HAS_SPIFI_COMMANDS
#error "+HAS_SPIFI_COMMANDS"
#endif

bool spifi_init_command(int32_t argc, char* argv[]);
bool spifi_diag_command(int32_t argc, char* argv[]);

#define SPIFI_COMMANDS                                                      \
    SPIFI_CUSTOM_COMMANDS                                                   \
    SHELL_CMD("spifi_init", "spin", spifi_init_command, "SpiFiInit"),       \
    SHELL_CMD("spifi_diag", "spd", spifi_diag_command, "SpiFi diag"),

#ifdef __cplusplus
}
#endif

#endif /* SPIFI_COMMANDS_H */
