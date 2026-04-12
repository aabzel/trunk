#ifndef MAX_HEAP_COMMANDS_H
#define MAX_HEAP_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_MAX_HEAP
#error "+ HAS_MAX_HEAP"
#endif

#ifndef HAS_MAX_HEAP_COMMANDS
#error "+ HAS_MAX_HEAP_COMMANDS"
#endif

bool max_heap_diag_command(int32_t argc, char* argv[]);
bool max_heap_init_command(int32_t argc, char* argv[]);
bool max_heap_push_command(int32_t argc, char* argv[]);
bool max_heap_pull_command(int32_t argc, char* argv[]);
bool max_heap_peek_command(int32_t argc, char* argv[]);

#define MAX_HEAP_COMMANDS                                                                                  \
        SHELL_CMD("max_heap_diag", "hxd", max_heap_diag_command, "MaxHeapDiag"),                           \
        SHELL_CMD("max_heap_init", "hxi", max_heap_init_command, "MaxHeapInit"),                           \
        SHELL_CMD("max_heap_peek", "hxk", max_heap_peek_command, "MaxHeapPeek"),                           \
        SHELL_CMD("max_heap_pull", "hxl", max_heap_pull_command, "MaxHeapPull"),                           \
        SHELL_CMD("max_heap_push", "hxp", max_heap_push_command, "MaxHeapPush"),

#ifdef __cplusplus
}
#endif

#endif /* MAX_HEAP_COMMANDS_H */
