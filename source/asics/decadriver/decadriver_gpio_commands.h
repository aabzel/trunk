#ifndef DECADRIVER_GPIO_COMMANDS_H
#define DECADRIVER_GPIO_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_DIAG
#error "+ HAS_DIAG"
#endif

#ifndef HAS_DECADRIVER
#error "+ HAS_DECADRIVER"
#endif

#ifndef HAS_DECADRIVER_COMMANDS
#error "+HAS_DECADRIVER_COMMANDS"
#endif

bool decadriver_gpio_diag_command(int32_t argc, char* argv[]);
bool decadriver_gpio_init_command(int32_t argc, char* argv[]);
bool decadriver_gpio_set_dir_command(int32_t argc, char* argv[]);
bool decadriver_gpio_set_val_command(int32_t argc, char* argv[]);
bool decadriver_gpio_get_val_command(int32_t argc, char* argv[]);

#define DECADRIVER_GPIO_COMMANDS                                                                           \
        SHELL_CMD("deca_gpio_diag", "dgd", decadriver_gpio_diag_command, "DecaGpioDiag"),                   \
        SHELL_CMD("deca_gpio_init", "dgi", decadriver_gpio_init_command, "DecaGpioInit"),                   \
        SHELL_CMD("deca_gpio_set_val", "dgsv", decadriver_gpio_set_dir_command, "DecaGpioSetVal"),          \
        SHELL_CMD("deca_gpio_set_dir", "dgsd", decadriver_gpio_set_val_command, "DecaGpioSetDir"),          \
        SHELL_CMD("deca_gpio_get_val", "dgv", decadriver_gpio_get_val_command, "DecaGpioGetVal"),

#ifdef __cplusplus
}
#endif

#endif /* DECADRIVER_GPIO_COMMANDS_H */
