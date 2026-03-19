#ifndef SDIO_COMMANDS_H
#define SDIO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_SDIO_CUSTOM_COMMANDS
#include "sdio_custom_commands.h"
#else
#define SDIO_CUSTOM_COMMANDS
#endif

#ifndef HAS_SDIO
#error "+ HAS_SDIO"
#endif

#ifndef HAS_SDIO_COMMANDS
#error "+ HAS_SDIO_COMMANDS"
#endif

bool sdio_diag_command(int32_t argc, char* argv[]);
bool sdio_init_command(int32_t argc, char* argv[]);
bool sdio_reg_map_command(int32_t argc, char* argv[]);

#define SDIO_COMMANDS                                                                           \
        SDIO_CUSTOM_COMMANDS                                                                    \
        SHELL_CMD("sdio_diag", "sdd", sdio_diag_command, "SdioDiag"),                           \
        SHELL_CMD("sdio_init", "sdi", sdio_init_command, "SdioInit"),                           \
        SHELL_CMD("sdio_reg_map", "sdrm", sdio_reg_map_command, "SdioRawRegs"),

#ifdef __cplusplus
}
#endif

#endif /* SDIO_COMMANDS_H */
