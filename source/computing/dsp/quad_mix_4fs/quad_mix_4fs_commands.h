#ifndef QUAD_MIX_4FS_COMMANDS_H
#define QUAD_MIX_4FS_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <std_includes.h>

#include "ostream.h"

#ifndef HAS_QUAD_MIX_4FS_COMMANDS
#error "+HAS_QUAD_MIX_4FS_COMMANDS"
#endif

#ifndef HAS_QUAD_MIX_4FS
#error "+HAS_QUAD_MIX_4FS"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool quad_mix_4fs_init_command(int32_t argc, char* argv[]);
bool quad_mix_4fs_diag_command(int32_t argc, char* argv[]);

#define QUAD_MIX_4FS_COMMANDS                                                                 \
        SHELL_CMD("quad_mix_4fs_diag", "qmd", quad_mix_4fs_diag_command, "QuadMix4fsDiag"),                       \
        SHELL_CMD("quad_mix_4fs_init", "qmi", quad_mix_4fs_init_command, "QuadMix4fsInit"),

#ifdef __cplusplus
}
#endif

#endif /* QUAD_MIX_4FS_COMMANDS_H */
