#ifndef DECAWAVE_COMMAND_H
#define DECAWAVE_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_DECAWAVE
#error "+HAS_DECAWAVE"
#endif

#ifndef HAS_DECAWAVE_COMMANDS
#error "+HAS_DECAWAVE_COMMANDS"
#endif

bool decawave_diag_command(int32_t argc, char* argv[]);
bool decawave_protocol_diag_command(int32_t argc, char* argv[]);
bool decawave_diag_flow_command(int32_t argc, char* argv[]);
bool decawave_init_command(int32_t argc, char* argv[]);

#define DECAWAVE_COMMANDS                                                                                        \
    SHELL_CMD("decawave_init", "dvi", decawave_init_command, "DecaWaveInit"),                                    \
    SHELL_CMD("decawave_diag_flow", "ddf", decawave_diag_flow_command, "DecawaveDiagFlow"),                      \
    SHELL_CMD("decawave_protocol_diag", "dpd", decawave_protocol_diag_command, "DecawaveProtocolDiag"),          \
    SHELL_CMD("decawave_diag", "dewd", decawave_diag_command, "DecaWaveDiag"),                                   \

#ifdef __cplusplus
}
#endif

#endif /* DECAWAVE_COMMAND_H */
