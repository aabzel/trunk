#ifndef I2S_FULL_DUPLEX_GENERAL_COMMANDS_H
#define I2S_FULL_DUPLEX_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool i2s_full_duplex_ctrl_command(int32_t argc, char* argv[]);
bool i2s_full_duplex_diag_command(int32_t argc, char* argv[]);

#define I2S_FULL_DUPLEX_COMMANDS                                                                                                   \
    SHELL_CMD("i2s_full_duplex_diag", "i2sfdd", i2s_full_duplex_diag_command, "I2sFullDuplexDiag"),                                  \
    SHELL_CMD("i2s_full_duplex_ctrl", "i2sfdc", i2s_full_duplex_ctrl_command, "I2sFullDuplexCtrl"),

#ifdef __cplusplus
}
#endif

#endif /* I2S_FULL_DUPLEX_GENERAL_COMMANDS_H */
