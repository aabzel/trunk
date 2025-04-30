#ifndef I2S_CUSTOM_CUSTOM_COMMANDS_H
#define I2S_CUSTOM_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"


bool i2s_diag_low_level_command(int32_t argc, char* argv[]);
bool i2s_raw_reg_command(int32_t argc, char* argv[]);


#define I2S_CUSTOM_COMMANDS                                                                       \
    SHELL_CMD("i2s_raw_reg", "i2sra", i2s_raw_reg_command, "I2sRawReg"),                          \
    SHELL_CMD("i2s_diag_low_level", "i2sdl", i2s_diag_low_level_command, "I2sDiagLowLevel"),




#ifdef __cplusplus
}
#endif

#endif /* I2S_CUSTOM_CUSTOM_COMMANDS_H */
