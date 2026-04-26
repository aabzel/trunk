#ifndef GPIO_DAC_COMMANDS_H
#define GPIO_DAC_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_GPIO_DAC
#error "+ HAS_GPIO_DAC"
#endif

#ifndef HAS_GPIO_DAC_COMMANDS
#error "+ HAS_GPIO_DAC_COMMANDS"
#endif

bool gpio_dac_diag_command(int32_t argc, char* argv[]);
bool gpio_dac_init_command(int32_t argc, char* argv[]);

#define GPIO_DAC_COMMANDS                                                                                  \
        SHELL_CMD("gpio_dac_diag", "gdd", gpio_dac_diag_command, "GpioDacDiag"),                           \
        SHELL_CMD("gpio_dac_init", "gdi", gpio_dac_init_command, "GpioDacInit"),

#ifdef __cplusplus
}
#endif

#endif /* GPIO_DAC_COMMANDS_H */
