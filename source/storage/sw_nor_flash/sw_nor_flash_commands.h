#ifndef SW_NOR_FLASH_COMMANDS_H
#define SW_NOR_FLASH_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_SW_NOR_FLASH
#error "+ HAS_SW_NOR_FLASH"
#endif

#ifndef HAS_SW_NOR_FLASH_COMMANDS
#error "+ HAS_SW_NOR_FLASH_COMMANDS"
#endif

bool sw_nor_flash_diag_command(int32_t argc, char* argv[]);
bool sw_nor_flash_init_command(int32_t argc, char* argv[]);

#define SW_NOR_FLASH_COMMANDS                                                                                         \
        SHELL_CMD("sw_nor_flash_diag", "swfd", sw_nor_flash_diag_command, "SwNorFlashDiag"),                           \
        SHELL_CMD("sw_nor_flash_init", "swfi", sw_nor_flash_init_command, "SwNorFlashInit"),

#ifdef __cplusplus
}
#endif

#endif /* SW_NOR_FLASH_COMMANDS_H */
