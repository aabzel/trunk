#ifndef FLASH_CUSTOM_COMMANDS_H
#define FLASH_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool flash_external_diag_command(int32_t argc, char* argv[]) ;
bool flash_custum_diag_command(int32_t argc, char* argv[]) ;

#define FLASH_CUSTOM_COMMANDS                                                             \
    SHELL_CMD("flash_custum_diag", "fcd", flash_custum_diag_command, "FlashCustomDiag"),  \
    SHELL_CMD("flash_external_diag", "fed", flash_external_diag_command, "FlashExtDiag"),

#ifdef __cplusplus
}
#endif

#endif /* FLASH_CUSTOM_COMMANDS_H */
