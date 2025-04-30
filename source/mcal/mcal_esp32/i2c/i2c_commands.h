#ifndef I2C_COMMANDS_H
#define I2C_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_manager.h"

bool i2c_init_command(int32_t argc, char* argv[]);
bool i2c_start_stop_command(int32_t argc, char* argv[]);
bool i2c_write_command(int32_t argc, char* argv[]);
bool i2c_read_command(int32_t argc, char* argv[]);
bool i2c_diag_command(int32_t argc, char* argv[]);
bool i2c_scan_command(int32_t argc, char* argv[]);
bool i2c_check_addr_command(int32_t argc, char* argv[]);

#define I2C_COMMANDS                                                                                                   \
    SHELL_CMD("i2c_diag", "i2d", i2c_diag_command, "I2C diag"),                                                        \
        SHELL_CMD("i2c_start_stop", "i2ss", i2c_start_stop_command, "I2C start stop"),                                 \
        SHELL_CMD("i2c_check", "i2cc", i2c_check_addr_command, "I2C check addr"),                                      \
        SHELL_CMD("i2c_scan", "i2s", i2c_scan_command, "I2C scan"),                                                    \
        SHELL_CMD("i2c_write", "i2w", i2c_write_command, "I2C write hex str"),                                         \
        SHELL_CMD("i2c_init", "i2i", i2c_init_command, "I2C init"),                                                    \
        SHELL_CMD("i2c_read", "i2r", i2c_read_command, "I2C write "),

#ifdef __cplusplus
}
#endif

#endif /* I2C_COMMANDS_H */
