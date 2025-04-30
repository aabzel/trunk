#ifndef GPIO_MIK32_COMMANDS_H
#define GPIO_MIK32_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
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

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool ext_int_mask_reset_command(int32_t argc, char* argv[]);
bool ext_int_mask_set_command(int32_t argc, char* argv[]);
bool gpio_interrupt_command(int32_t argc, char* argv[]);

#define GPIO_MIK32_COMMANDS                                                                                                  \
        SHELL_CMD("ext_int_set", "eis", ext_int_mask_set_command, "ExtIntSet"),                                        \
        SHELL_CMD("ext_int_reset", "eir", ext_int_mask_reset_command, "ExtIntReset"),                                  \
        SHELL_CMD("gpio_int", "gi", gpio_interrupt_command, "GpioInt"),                                                \

#ifdef __cplusplus
}
#endif

#endif /* GPIO_MIK32_COMMANDS_H */
