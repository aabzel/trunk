#ifndef PIN_GENERAL_COMMANDS_H
#define PIN_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_LOG
#include "ostream.h"
#endif

#ifdef HAS_PIN_CUSTOM_COMMANDS
#include "pin_custom_commands.h"
#else
#define PIN_CUSTOM_COMMANDS
#endif

#ifndef HAS_PIN_COMMANDS
#error "+HAS_PIN_COMMANDS"
#endif

#ifndef HAS_PIN_COMMANDS
#error "+HAS_PIN_COMMANDS"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_PIN
#error "+HAS_PIN"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool pin_list_command(int32_t argc, char* argv[]);
bool pin_init_command(int32_t argc, char* argv[]);
bool pin_test_command(int32_t argc, char* argv[]);
bool pin_get_command(int32_t argc, char* argv[]);
bool pin_set_command(int32_t argc, char* argv[]);
bool pin_mux_command(int32_t argc, char* argv[]);
bool pin_dir_command(int32_t argc, char* argv[]);
bool pin_pull_command(int32_t argc, char* argv[]);
bool pin_toggle_command(int32_t argc, char* argv[]);

#define PIN_COMMANDS                                                                                                  \
    PIN_CUSTOM_COMMANDS                                                                                               \
    SHELL_CMD("pin_list", "gl", pin_list_command, "PinList"),                                                       \
        SHELL_CMD("pin_init", "gi", pin_init_command, "PinInit"),                                                   \
        SHELL_CMD("pin_mux", "gm", pin_mux_command, "PinPinMux"),                                                   \
        SHELL_CMD("pin_dir", "gd", pin_dir_command, "PinDir"),                                                      \
        SHELL_CMD("pin_test", "ge", pin_test_command, "PinTest"),                                                   \
        SHELL_CMD("pin_toggle", "gt", pin_toggle_command, "PinToggle"),                                             \
        SHELL_CMD("pin_get", "gg", pin_get_command, "PinGet"),                                                      \
        SHELL_CMD("pin_pull", "gp", pin_pull_command, "PinPull"),                                                   \
        SHELL_CMD("pin_set", "gs", pin_set_command, "PinSet"),

#ifdef __cplusplus
}
#endif

#endif /* PIN_GENERAL_COMMANDS_H */
