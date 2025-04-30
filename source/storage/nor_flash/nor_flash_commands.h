#ifndef NOR_FLASH_COMMANDS_H
#define NOR_FLASH_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_NOR_FLASH
#error "+HAS_NOR_FLASH"
#endif

#ifndef HAS_NOR_FLASH_COMMANDS
#error "+HAS_NOR_FLASH_COMMANDS"
#endif

bool nor_flash_diag_command(int32_t argc, char* argv[]);
bool nor_flash_analyze_command(int32_t argc, char* argv[]);
bool nor_flash_init_command(int32_t argc, char* argv[]);
bool nor_flash_read_command(int32_t argc, char* argv[]);
bool nor_flash_reset_command(int32_t argc, char* argv[]);
bool nor_flash_write_command(int32_t argc, char* argv[]);

#define NOR_FLASH_COMMANDS                                                                      \
        SHELL_CMD("nor_flash_analyze", "nfa", nor_flash_analyze_command, "NorFlashAnalyze"),    \
        SHELL_CMD("nor_flash_read", "nfr", nor_flash_read_command, "NorFlashRead"),             \
        SHELL_CMD("nor_flash_write", "nfw", nor_flash_write_command, "NorFlashWrite"),          \
        SHELL_CMD("nor_flash_diag", "nfd", nor_flash_diag_command, "NorFlashDiag"),             \
        SHELL_CMD("nor_flash_init", "nfi", nor_flash_init_command, "NorFlashInit"),             \
        SHELL_CMD("nor_flash_reset", "nft", nor_flash_reset_command, "NorFlashReset"),

#ifdef __cplusplus
}
#endif

#endif /* NOR_FLASH_COMMANDS_H */
