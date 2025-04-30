#ifndef GPIO_GENERAL_COMMANDS_H
#define GPIO_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_LOG
#include "ostream.h"
#endif

#ifdef HAS_GPIO_CUSTOM_COMMANDS
#include "gpio_custom_commands.h"
#else
#define GPIO_CUSTOM_COMMANDS
#endif

#ifndef HAS_GPIO_COMMANDS
#error "+HAS_GPIO_COMMANDS"
#endif

#ifndef HAS_GPIO_COMMANDS
#error "+HAS_GPIO_COMMANDS"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool gpio_list_command(int32_t argc, char* argv[]);
bool gpio_init_command(int32_t argc, char* argv[]);
bool gpio_test_command(int32_t argc, char* argv[]);
bool gpio_get_command(int32_t argc, char* argv[]);
bool gpio_set_command(int32_t argc, char* argv[]);
bool gpio_mux_command(int32_t argc, char* argv[]);
bool gpio_dir_command(int32_t argc, char* argv[]);
bool gpio_pull_command(int32_t argc, char* argv[]);
bool gpio_toggle_command(int32_t argc, char* argv[]);

#define GPIO_COMMANDS                                                                                                  \
    GPIO_CUSTOM_COMMANDS                                                                                               \
    SHELL_CMD("gpio_list", "gl", gpio_list_command, "GpioList"),                                                       \
        SHELL_CMD("gpio_init", "gi", gpio_init_command, "GpioInit"),                                                   \
        SHELL_CMD("gpio_mux", "gm", gpio_mux_command, "GpioPinMux"),                                                   \
        SHELL_CMD("gpio_dir", "gd", gpio_dir_command, "GpioDir"),                                                      \
        SHELL_CMD("gpio_test", "ge", gpio_test_command, "GpioTest"),                                                   \
        SHELL_CMD("gpio_toggle", "gt", gpio_toggle_command, "GpioToggle"),                                             \
        SHELL_CMD("gpio_get", "gg", gpio_get_command, "GpioGet"),                                                      \
        SHELL_CMD("gpio_pull", "gp", gpio_pull_command, "GpioPull"),                                                   \
        SHELL_CMD("gpio_set", "gs", gpio_set_command, "GpioSet"),

#ifdef __cplusplus
}
#endif

#endif /* GPIO_GENERAL_COMMANDS_H */
