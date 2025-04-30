#ifndef BIT_COMMANDS_H
#define BIT_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "only for CLI"
#endif

bool bit_diff_command(int32_t argc, char* argv[]);

#define BIT_COMMANDS                                                                          \
        SHELL_CMD("bit_diff", "bd", bit_diff_command, "BitDiff"),

#ifdef __cplusplus
}
#endif

#endif /* BIT_COMMANDS_H */
