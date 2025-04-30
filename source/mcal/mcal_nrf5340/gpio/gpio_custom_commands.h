#ifndef GPIO_NRF_COMMANDS_H
#define GPIO_NRF_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_GPIO_COMMANDS
#error "+HAS_GPIO_COMMANDS"
#endif

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool nrf_gpio_set_command(int32_t argc, char* argv[]);
bool nrf_gpio_set_core_command(int32_t argc, char* argv[]);
bool nrf_gpio_cfg_command(int32_t argc, char* argv[]);

#define GPIO_CUSTOM_COMMANDS                                                                                     \
    SHELL_CMD("nrf_gpio_cfg", "ngc", nrf_gpio_cfg_command, "NrfGpioCfg"),                                        \
    SHELL_CMD("nrf_gpio_set", "ngs", nrf_gpio_set_command, "NrfGpioSet"),                                        \
        SHELL_CMD("nrf_gpio_set_core", "ngsm", nrf_gpio_set_core_command, "NrfGpioSetCore"),

#ifdef __cplusplus
}
#endif

#endif /* GPIO_NRF_COMMANDS_H */
