#ifndef I2C_CUSTOM_COMMANDS_H
#define I2C_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


bool i2c_diag_custom_command(int32_t argc, char* argv[]);
bool i2c_all_int_command(int32_t argc, char* argv[]);
bool i2c_data_send_command(int32_t argc, char* argv[]);
bool i2c_raw_reg_command(int32_t argc, char* argv[]);
bool i2c_div_command(int32_t argc, char* argv[]);
bool i2c_clkctrl_diag_command(int32_t argc, char* argv[]);


#define I2C_CUSTOM_COMMANDS                                                                       \
    SHELL_CMD("i2c_clkctrl_diag", "i2ccd", i2c_clkctrl_diag_command, "I2cClkCtrlDiag"),           \
    SHELL_CMD("i2c_div", "i2cdi", i2c_div_command, "I2cDiv"),                                     \
    SHELL_CMD("i2c_all_int", "i2cai", i2c_all_int_command, "I2cAllInt"),                          \
    SHELL_CMD("i2c_raw_reg", "i2cra", i2c_raw_reg_command, "I2cRawReg"),                          \
    SHELL_CMD("i2c_diag_custom", "i2cdc", i2c_diag_custom_command, "I2cDiagCustom"),              \
    SHELL_CMD("i2c_data_send", "i2cds", i2c_data_send_command, "I2cDataSend"),

#ifdef __cplusplus
}
#endif

#endif /* I2C_CUSTOM_COMMANDS_H */
