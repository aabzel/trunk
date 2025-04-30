#ifndef I2C_GENERAL_COMMANDS_H
#define I2C_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_I2C
#error "+HAS_I2C"
#endif

#ifdef HAS_I2C_CUSTOM_COMMANDS
#include "i2c_custom_commands.h"
#else
#define I2C_CUSTOM_COMMANDS
#endif

bool i2c_read_command(int32_t argc, char* argv[]);
bool i2c_read_reg_command(int32_t argc, char* argv[]);
bool i2c_read_word_command(int32_t argc, char* argv[]);
bool i2c_read_memory_command(int32_t argc, char* argv[]);
bool i2c_scan_command(int32_t argc, char* argv[]);
bool i2c_check_addr_command(int32_t argc, char* argv[]);

#define I2C_READ_COMMANDS                      \
        SHELL_CMD("i2c_check", "i2cc", i2c_check_addr_command, "I2cCheckAddr"),            \
        SHELL_CMD("i2c_scan", "i2cs", i2c_scan_command, "I2cScan"),                        \
        SHELL_CMD("i2c_read", "i2cr", i2c_read_command, "I2cRead"),                        \
        SHELL_CMD("i2c_read_word", "i2crd", i2c_read_word_command, "I2cReadWord"),         \
        SHELL_CMD("i2c_read_reg", "i2crr", i2c_read_reg_command, "I2cRegRead"),            \
        SHELL_CMD("i2c_read_memory", "i2crm", i2c_read_memory_command, "I2cReadMemory"),

bool i2c_write_command(int32_t argc, char* argv[]);
bool i2c_reg_write_verify_command(int32_t argc, char* argv[]);
bool i2c_reg_write_command(int32_t argc, char* argv[]);
bool i2c_start_stop_command(int32_t argc, char* argv[]);

#define I2C_WRITE_COMMANDS                                                                       \
        SHELL_CMD("i2c_start_stop", "i2csp", i2c_start_stop_command, "I2cWriteStartStop"),       \
        SHELL_CMD("i2c_write", "i2cw", i2c_write_command, "I2cWriteHexStr"),                     \
        SHELL_CMD("i2c_reg_write_verify", "i2crwv", i2c_reg_write_verify_command, "I2cRegWriteVerify"), \
        SHELL_CMD("i2c_reg_write", "i2crw", i2c_reg_write_command, "I2cRegWrite"),

bool i2c_init_command(int32_t argc, char* argv[]);
bool i2c_diag_command(int32_t argc, char* argv[]);

#define I2C_COMMANDS                                                                       \
    I2C_CUSTOM_COMMANDS                                                                    \
    I2C_READ_COMMANDS                                                                      \
    I2C_WRITE_COMMANDS                                                                     \
    SHELL_CMD("i2c_diag", "i2cd", i2c_diag_command, "I2cDiag"),                            \
    SHELL_CMD("i2c_init", "i2ci", i2c_init_command, "I2cInit"),

#ifdef __cplusplus
}
#endif

#endif /* I2C_GENERAL_COMMANDS_H */
