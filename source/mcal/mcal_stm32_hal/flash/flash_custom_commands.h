#ifndef FLASH_CUSTOM_COMMANDS_H
#define FLASH_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool flash_diag_reg_command(int32_t argc, char* argv[]);

#define FLASH_CUSTOM_COMMANDS                                                                                          \
        SHELL_CMD("flash_diag_reg", "fdr", flash_diag_reg_command, "FlashCustomDiagReg"),


#ifdef __cplusplus
}
#endif

#endif /* FLASH_CUSTOM_COMMANDS_H */
