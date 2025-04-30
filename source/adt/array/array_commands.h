#ifndef ARRAY_COMMANDS_H
#define ARRAY_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

bool array_print_command(int32_t argc, char* argv[]);

#define ARRAY_COMMANDS                                                     \
    SHELL_CMD("array_print", "ap", array_print_command, "ArrayPrint"),    \

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_COMMANDS_H */
