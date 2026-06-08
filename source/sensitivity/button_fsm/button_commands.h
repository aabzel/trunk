#ifndef BUTTON_COMMANDS_H
#define BUTTON_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_BUTTON
#error "+HAS_BUTTON"
#endif

#ifndef HAS_BUTTON_COMMANDS
#error "+HAS_BUTTON_COMMANDS"
#endif

bool button_get_command(int32_t argc, char* argv[]);
bool button_set_command(int32_t argc, char* argv[]);
bool button_diag_command(int32_t argc, char* argv[]);
bool button_press_command(int32_t argc, char* argv[]);
bool button_init_command(int32_t argc, char* argv[]);

#define BUTTON_COMMANDS                                                                        \
    SHELL_CMD("button_init", "bti", button_init_command, "ButtonInit"),                        \
    SHELL_CMD("button_get", "btg", button_get_command, "ButtonGet"),                           \
    SHELL_CMD("button_diag", "btd", button_diag_command, "ButtonDiag"),                        \
    SHELL_CMD("button_set", "bts", button_set_command, "ButtonSet"),                           \
    SHELL_CMD("button_press", "btp", button_press_command, "ButtonPress"),

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_COMMANDS_H */
