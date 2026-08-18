#ifndef RS2058_COMMANDS_H
#define RS2058_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_RS2058
#error "+ HAS_RS2058"
#endif

#ifndef HAS_RS2058_COMMANDS
#error "+ HAS_RS2058_COMMANDS"
#endif

bool rs2058_init_command(int32_t argc, char* argv[]);
bool rs2058_diag_command(int32_t argc, char* argv[]);
bool rs2058_ctrl_command(int32_t argc, char* argv[]);

#define RS2058_COMMANDS                                                                       \
        SHELL_CMD("rs2058_diag", "rsd", rs2058_diag_command, "Rs2058Diag"),                   \
        SHELL_CMD("rs2058_ctrl", "rct", rs2058_ctrl_command, "Rs2058Ctrl"),                   \
        SHELL_CMD("rs2058_init", "rsi", rs2058_init_command, "Rs2058Init"),                   \

#ifdef __cplusplus
}
#endif

#endif /* RS2058_COMMANDS_H */
