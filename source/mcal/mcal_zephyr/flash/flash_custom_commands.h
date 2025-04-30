#ifndef FLASH_CUSTOM_COMMANDS_H
#define FLASH_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

bool flash_custom_diag_commands(int32_t argc, char* argv[]);

#define FLASH_CUSTOM_COMMANDS                                                                   \
        SHELL_CMD("flash_custom_diag", "fcd", flash_custom_diag_commands, "FlashCustomDiag"),

#ifdef __cplusplus
}
#endif

#endif /* FLASH_CUSTOM_COMMANDS_H */
