#ifndef MAM_COMMANDS_H
#define MAM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_MAM_CUSTOM_COMMANDS
#include "mam_custom_commands.h"
#else
#define MAM_CUSTOM_COMMANDS
#endif


#ifndef HAS_MAM
#error "+ HAS_MAM"
#endif

#ifndef HAS_MAM_COMMANDS
#error "+ HAS_MAM_COMMANDS"
#endif

bool mam_diag_command(int32_t argc, char* argv[]);
bool mam_init_command(int32_t argc, char* argv[]);

#define MAM_COMMANDS                                                                                          \
        MAM_CUSTOM_COMMANDS                                                                                   \
        SHELL_CMD("mam_diag", "mamd", mam_diag_command, "MamDiag"),                           \
        SHELL_CMD("mam_init", "mami", mam_init_command, "MamInit"),

#ifdef __cplusplus
}
#endif

#endif /* MAM_COMMANDS_H */
