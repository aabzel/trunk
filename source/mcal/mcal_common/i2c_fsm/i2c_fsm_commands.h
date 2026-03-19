#ifndef I2C_FSM_COMMANDS_H
#define I2C_FSM_COMMANDS_H

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

bool i2c_fsm_read_command(int32_t argc, char* argv[]);
bool i2c_fsm_read_byte_command(int32_t argc, char* argv[]);
bool i2c_fsm_read_word_command(int32_t argc, char* argv[]);
bool i2c_fsm_read_memory_command(int32_t argc, char* argv[]);
bool i2c_fsm_scan_base_command(int32_t argc, char* argv[]);
bool i2c_fsm_check_addr_command(int32_t argc, char* argv[]);

#define I2C_FSM_READ_COMMANDS                      \
        SHELL_CMD("i2c_fsm_check", "i2cfc", i2c_fsm_check_addr_command, "I2cCheckAddr"),            \
        SHELL_CMD("i2c_fsm_scan_base", "i2cfsb", i2c_fsm_scan_base_command, "I2cScanBase"),                        \
        SHELL_CMD("i2c_fsm_read", "i2cfr", i2c_fsm_read_command, "I2cRead"),                        \
        SHELL_CMD("i2c_fsm_read_word", "i2cfrd", i2c_fsm_read_word_command, "I2cReadWord"),         \
        SHELL_CMD("i2c_fsm_read_byte", "i2cfrr", i2c_fsm_read_byte_command, "I2cRegRead"),            \
        SHELL_CMD("i2c_fsm_read_memory", "i2cfrm", i2c_fsm_read_memory_command, "I2cReadMemory"),

bool i2c_fsm_write_command(int32_t argc, char* argv[]);
bool i2c_fsm_write_reg_verify_command(int32_t argc, char* argv[]);
bool i2c_fsm_write_reg_command(int32_t argc, char* argv[]);

#define I2C_FSM_WRITE_COMMANDS                                                                       \
        SHELL_CMD("i2c_start_stop", "i2cfsp", i2c_start_stop_command, "I2cWriteStartStop"),       \
        SHELL_CMD("i2c_fsm_write", "i2cfw", i2c_fsm_write_command, "I2cWriteHexStr"),                     \
        SHELL_CMD("i2c_fsm_write_reg_verify", "i2cfrwv", i2c_fsm_write_reg_verify_command, "I2cRegWriteVerify"), \
        SHELL_CMD("i2c_fsm_write_reg", "i2cfrw", i2c_fsm_write_reg_command, "I2cRegWrite"),

bool i2c_fsm_init_command(int32_t argc, char* argv[]);
bool i2c_fsm_diag_command(int32_t argc, char* argv[]);
bool i2c_fsm_empty_command(int32_t argc, char* argv[]);

#define I2C_FSM_COMMANDS                                                                       \
    I2C_FSM_READ_COMMANDS                                                                      \
    I2C_FSM_WRITE_COMMANDS                                                                     \
    SHELL_CMD("i2c_fsm_empty", "i2cfe", i2c_fsm_empty_command, "I2cFsmEmpty"),                 \
    SHELL_CMD("i2c_fsm_diag", "i2cfd", i2c_fsm_diag_command, "I2cFsmDiag"),                    \
    SHELL_CMD("i2c_fsm_init", "i2cfi", i2c_fsm_init_command, "I2cFsmInit"),

#ifdef __cplusplus
}
#endif

#endif /* I2C_FSM_COMMANDS_H */
