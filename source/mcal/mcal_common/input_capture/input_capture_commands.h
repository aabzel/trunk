#ifndef INPUT_CAPTURE_COMMANDS_H
#define INPUT_CAPTURE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifdef HAS_INPUT_CAPTURE_CUSTOM_COMMANDS
#include "input_capture_custom_commands.h"
#else
#define INPUT_CAPTURE_CUSTOM_COMMANDS
#endif

#ifndef HAS_INPUT_CAPTURE
#error "+HAS_INPUT_CAPTURE"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_INPUT_CAPTURE_COMMANDS
#error "+HAS_INPUT_CAPTURE_COMMANDS"
#endif

bool input_capture_enable_command(int32_t argc, char* argv[]);
bool input_capture_reset_command(int32_t argc, char* argv[]);
bool input_capture_init_command(int32_t argc, char* argv[]);
bool input_capture_diag_command(int32_t argc, char* argv[]);

#define INPUT_CAPTURE_COMMANDS                                                                                                   \
    INPUT_CAPTURE_CUSTOM_COMMANDS                                                                                                \
    SHELL_CMD("input_capture_reset", "icr", input_capture_reset_command, "InputCaptureReset"),                                   \
    SHELL_CMD("input_capture_enable", "ince", input_capture_enable_command, "InputCaptureEnable"),                               \
    SHELL_CMD("input_capture_diag", "incd", input_capture_diag_command, "InputCaptureDiag"),                                     \
    SHELL_CMD("input_capture_init", "inci", input_capture_init_command, "InputCaptureInit"),

#ifdef __cplusplus
}
#endif

#endif /* INPUT_CAPTURE_CUSTOM_COMMANDS_H */
