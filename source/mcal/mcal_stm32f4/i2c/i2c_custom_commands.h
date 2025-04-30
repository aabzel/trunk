#ifndef I2C_CUSTOM_COMMANDS_H
#define I2C_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#define I2C_CUSTOM_COMMANDS

#if 0
bool i2c_init_command(int32_t argc, char* argv[]);
bool i2c_start_stop_command(int32_t argc, char* argv[]);
bool i2c_diag_command(int32_t argc, char* argv[]);
bool i2c_diag_low_level_command(int32_t argc, char* argv[]);
bool i2c_scan_command(int32_t argc, char* argv[]);

    SHELL_CMD("i2c_diag", "i2cd", i2c_diag_command, "I2c diag"),                                                       \
        SHELL_CMD("i2c_diag_ll", "i2cdl", i2c_diag_low_level_command, "I2cDiagLowLevel"),                              \
        SHELL_CMD("i2c_start_stop", "i2css", i2c_start_stop_command, "I2cStartStop"),                                  \
        SHELL_CMD("i2c_check", "i2cc", i2c_check_addr_command, "I2c check addr"),                                      \
        SHELL_CMD("i2c_scan", "i2cs", i2c_scan_command, "I2cScan"),                                                    \
        SHELL_CMD("i2c_write", "i2cw", i2c_write_command, "I2c write hex str"),                                        \
        SHELL_CMD("i2c_init", "i2ci", i2c_init_command, "I2c init"),                                                   \
        SHELL_CMD("i2c_read", "i2cr", i2c_read_command, "I2c read "),
#endif

#ifdef __cplusplus
}
#endif

#endif /* I2C_CUSTOM_COMMANDS_H */
