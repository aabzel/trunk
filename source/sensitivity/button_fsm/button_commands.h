#ifndef BUTTON_COMMANDS_H
#define BUTTON_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_BUTTON
#error "+HAS_BUTTON"
#endif  /*HAS_BUTTON*/

#ifndef HAS_BUTTON_COMMANDS
#error "+HAS_BUTTON_COMMANDS"
#endif  /*HAS_BUTTON_COMMANDS*/

bool button_get_command(int32_t argc, char* argv[]);
bool button_set_command(int32_t argc, char* argv[]);
bool button_diag_command(int32_t argc, char* argv[]);
bool button_press_command(int32_t argc, char* argv[]);

#define BUTTON_COMMANDS                                                                        \
    SHELL_CMD("button_get", "bg", button_get_command, "ButtonGet"),                            \
    SHELL_CMD("button_diag", "bd", button_diag_command, "ButtonDiag"),                         \
    SHELL_CMD("button_set", "bs", button_set_command, "ButtonSet"),                            \
    SHELL_CMD("button_press", "bp", button_press_command, "ButtonPress"),

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_COMMANDS_H */
