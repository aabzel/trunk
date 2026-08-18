#ifndef GM67_COMMANDS_H
#define GM67_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_GM67
#error "+ HAS_GM67"
#endif

#ifndef HAS_GM67_COMMANDS
#error "+ HAS_GM67_COMMANDS"
#endif

bool gm67_diag_command(int32_t argc, char* argv[]);
bool gm67_init_command(int32_t argc, char* argv[]);

#define GM67_COMMANDS                                                         \
        SHELL_CMD("gm67_diag", "gm6d", gm67_diag_command, "Gm67Diag"),   \
        SHELL_CMD("gm67_init", "gm6i", gm67_init_command, "Gm67Init"),

#ifdef __cplusplus
}
#endif

#endif /* GM67_COMMANDS_H */

