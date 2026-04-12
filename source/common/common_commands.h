#ifndef COMMON_COMMANDS_H
#define COMMON_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_COMMON
#error "+ HAS_COMMON"
#endif

#ifndef HAS_COMMON_COMMANDS
#error "+ HAS_COMMON_COMMANDS"
#endif

bool common_diag_command(int32_t argc, char* argv[]);

#define COMMON_COMMANDS                                                   \
        SHELL_CMD("common_diag", "comd", common_diag_command, "CommonDiag"),

#ifdef __cplusplus
}
#endif

#endif /* COMMON_COMMANDS_H */
