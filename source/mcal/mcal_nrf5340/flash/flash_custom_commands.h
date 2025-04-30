#ifndef FLASH_CUSTOM_COMMANDS_H
#define FLASH_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

bool flash_custom_diag_cmd(int32_t argc, char* argv[]);

#define FLASH_CUSTOM_COMMANDS                                                                 \
    SHELL_CMD("flash_custom_diag", "fcd", flash_custom_diag_cmd, "FlashCustomDiag"),

#ifdef __cplusplus
}
#endif

#endif /* FLASH_CUSTOM_COMMANDS_H */

