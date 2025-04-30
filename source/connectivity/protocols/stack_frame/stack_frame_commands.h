#ifndef STACK_FRAME_COMMAND_H
#define STACK_FRAME_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_STACK_FRAME
#error "+HAS_STACK_FRAME"
#endif

#ifndef HAS_STACK_FRAME_COMMANDS
#error "+HAS_STACK_FRAME_COMMANDS"
#endif

bool stack_frame_diag_command(int32_t argc, char* argv[]);
bool stack_frame_init_command(int32_t argc, char* argv[]);

#define STACK_FRAME_COMMANDS                                                                                        \
    SHELL_CMD("stack_frame_init", "dvi", stack_frame_init_command, "DecaWaveInit"),                              \
    SHELL_CMD("stack_frame_diag", "dewd", stack_frame_diag_command, "DecaWaveDiag"),                               \

#ifdef __cplusplus
}
#endif

#endif /* STACK_FRAME_COMMAND_H */
