#ifndef MIN_HEAP_COMMANDS_H
#define MIN_HEAP_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MIN_HEAP
#error "+ HAS_MIN_HEAP"
#endif

#ifndef HAS_MIN_HEAP_COMMANDS
#error "+ HAS_MIN_HEAP_COMMANDS"
#endif

bool min_heap_diag_command(int32_t argc, char* argv[]);
bool min_heap_init_command(int32_t argc, char* argv[]);
bool min_heap_push_command(int32_t argc, char* argv[]);
bool min_heap_pull_command(int32_t argc, char* argv[]);
bool min_heap_peek_command(int32_t argc, char* argv[]);

#define MIN_HEAP_COMMANDS                                                                                  \
        SHELL_CMD("min_heap_diag", "hid", min_heap_diag_command, "MinHeapDiag"),                           \
        SHELL_CMD("min_heap_init", "hii", min_heap_init_command, "MinHeapInit"),                           \
        SHELL_CMD("min_heap_peek", "hik", min_heap_peek_command, "MinHeapPeek"),                           \
        SHELL_CMD("min_heap_pull", "hil", min_heap_pull_command, "MinHeapPull"),                           \
        SHELL_CMD("min_heap_push", "hip", min_heap_push_command, "MinHeapPush"),

#ifdef __cplusplus
}
#endif

#endif /* MIN_HEAP_COMMANDS_H */
