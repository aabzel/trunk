#ifndef I2C_COMMANDS_H
#define I2C_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool i2c_diag_low_level_command(int32_t argc, char* argv[]);

#define I2C_PLATFORM_COMMANDS                                                                                                   \
        SHELL_CMD("i2c_diag_ll", "i2cdl", i2c_diag_low_level_command, "I2cDiagLowLevel"),

#ifdef __cplusplus
}
#endif

#endif /* I2C_COMMANDS_H */
