#ifndef PC_COMMANDS_H
#define PC_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool exit_command(int32_t argc, char* argv[]);

#define PC_COMMANDS                                               \
    SHELL_CMD("exit", "exit", exit_command, "Exit"),

#ifdef __cplusplus
}
#endif

#endif /* PC_COMMANDS_H */
