#ifndef GPIO_COMMANDS_H
#define GPIO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

bool gpio_set_dir_command(int32_t argc, char* argv[]);
bool gpio_get_command(int32_t argc, char* argv[]);
bool gpio_get_dir_command(int32_t argc, char* argv[]);
bool gpio_list_command(int32_t argc, char* argv[]);
bool gpio_set_command(int32_t argc, char* argv[]);
bool gpio_set_in_mode_command(int32_t argc, char* argv[]);
bool gpio_set_pull_command(int32_t argc, char* argv[]);
bool gpio_toggle_command(int32_t argc, char* argv[]);

#define GPIO_SPECIFIC_COMMANDS                                                                                                  \
    SHELL_CMD("gpio_list", "gl", gpio_list_command, "GPIO list"),                                                      \
        SHELL_CMD("gpio_toggle", "gt", gpio_toggle_command, "GPIO toggle"),                                            \
        SHELL_CMD("gpio_pull", "gp", gpio_set_pull_command, "GPIO set pull"),                                          \
        SHELL_CMD("gpio_in", "gis", gpio_set_in_mode_command, "GPIO set in mode"),                                     \
        SHELL_CMD("gpio_get", "gg", gpio_get_command, "GPIO get"),                                                     \
        SHELL_CMD("gpio_dirr", "ggd", gpio_get_dir_command, "GPIO dir"),                                               \
        SHELL_CMD("gpio_set_dirr", "gsd", gpio_set_dir_command, "GPIO set dir"),                                       \
        SHELL_CMD("gpio_set", "gs", gpio_set_command, "GPIO set"),

#ifdef __cplusplus
}
#endif

#endif /* GPIO_COMMANDS_H */
