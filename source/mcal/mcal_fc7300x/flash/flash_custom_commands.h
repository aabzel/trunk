#ifndef FLASH_CUSTOM_COMMANDS_H
#define FLASH_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool flash_raw_reg_read_command(int32_t argc, char* argv[]);

#define FLASH_CUSTOM_COMMANDS  \
    SHELL_CMD("flash_raw_reg", "frrr", flash_raw_reg_read_command, "FlashReadRawReg"), 

#ifdef __cplusplus
}
#endif

#endif /* FLASH_CUSTOM_COMMANDS_H */
