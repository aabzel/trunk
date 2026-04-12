#ifndef MEMORY_MANAGER_CLI_H
#define MEMORY_MANAGER_CLI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_MEMORY_MANAGER
#error "+HAS_MEMORY_MANAGER"
#endif

#ifndef HAS_FLASH
#error "+HAS_FLASH"
#endif

bool memory_manager_init_cli(int32_t argc, char* argv[]);
bool memory_manager_diag_cli(int32_t argc, char* argv[]);
bool memory_manager_bank_diag_cli(int32_t argc, char* argv[]);
bool memory_manager_dump_cli(int32_t argc, char* argv[]);
bool memory_manager_erase_cli(int32_t argc, char* argv[]);
bool memory_manager_read_cli(int32_t argc, char* argv[]);
bool memory_manager_write_cli(int32_t argc, char* argv[]);

#define MEMORY_MANAGER_CLI                                                                        \
    SHELL_CMD("memory_manager_init", "mmi", memory_manager_init_cli, "MemoryManagerInit"),        \
    SHELL_CMD("memory_manager_dump", "mmdu", memory_manager_dump_cli, "MemoryManagerDump"),       \
    SHELL_CMD("memory_manager_diag", "mmdi", memory_manager_diag_cli, "MemoryManagerDiag"),       \
    SHELL_CMD("memory_manager_bank_diag", "mmbd", memory_manager_bank_diag_cli, "MemoryManagerBankDiag"),       \
    SHELL_CMD("memory_manager_erase", "mme", memory_manager_erase_cli, "MemoryManagerErase"),     \
    SHELL_CMD("memory_manager_read", "mmr", memory_manager_read_cli, "MemoryManagerRead"),        \
    SHELL_CMD("memory_manager_write", "mmw", memory_manager_write_cli, "MemoryManagerWrite"),

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_MANAGER_CLI_H */
