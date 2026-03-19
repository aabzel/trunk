#ifndef EIM_GENERAL_COMMANDS_H
#define EIM_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_EIM_CUSTOM_COMMANDS
#include "eim_custom_commands.h"
#else
#define EIM_CUSTOM_COMMANDS
#endif

#ifndef HAS_EIM
#error "+ HAS_EIM"
#endif

#ifndef HAS_LOG
#error "+ HAS_LOG"
#endif

#ifndef HAS_CLI
#error "+ HAS_CLI"
#endif

bool eim_init_command(int32_t argc, char* argv[]);
bool eim_diag_command(int32_t argc, char* argv[]);

#define EIM_COMMANDS                                               \
    EIM_CUSTOM_COMMANDS                                            \
    SHELL_CMD("eim_diag", "eimd", eim_diag_command, "EimDiag"),    \
    SHELL_CMD("eim_init", "eimi", eim_init_command, "EimInit"),

#ifdef __cplusplus
}
#endif

#endif /* EIM_GENERAL_COMMANDS_H */
