#ifndef ALLOCATOR_COMMANDS_H
#define ALLOCATOR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_HEAP_COMMANDS
#error "+HAS_HEAP_COMMANDS"
#endif

#ifndef HAS_DEBUGGER
//#error "+HAS_DEBUGGER"
#endif

bool heap_diag_command(int32_t argc, char* argv[]);
bool heap_malloc_command(int32_t argc, char* argv[]);
bool heap_free_command(int32_t argc, char* argv[]);
bool heap_scan_command(int32_t argc, char* argv[]);

#define HEAP_COMMANDS                                                                                                  \
    SHELL_CMD("heap_diag", "hd", heap_diag_command, "HeapDiag"),                                                       \
        SHELL_CMD("heap_free", "hf", heap_free_command, "HeapFree"),                                                   \
        SHELL_CMD("heap_malloc", "hpm", heap_malloc_command, "HeapMalloc"),                                            \
        SHELL_CMD("heap_scan", "hs", heap_scan_command, "HeapScan"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*ALLOCATOR_COMMANDS_H*/
