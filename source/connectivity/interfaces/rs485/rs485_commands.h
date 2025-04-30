#ifndef RS485_COMMANDS_H
#define RS485_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_RS485
#error "+ HAS_RS485"
#endif

#ifndef HAS_RS485_COMMANDS
#error "+ HAS_RS485_COMMANDS"
#endif

bool rs485_scan_command(int32_t argc, char* argv[]);
bool rs485_send_command(int32_t argc, char* argv[]);
bool rs485_init_command(int32_t argc, char* argv[]);
bool rs485_diag_command(int32_t argc, char* argv[]);

#define RS485_COMMANDS                                                       \
    SHELL_CMD("rs485_send", "r4s", rs485_send_command, "Rs485Send"),         \
    SHELL_CMD("rs485_scan", "r4c", rs485_scan_command, "Rs485Scan"),         \
    SHELL_CMD("rs485_diag", "r4d", rs485_diag_command, "Rs485Diag"),         \
    SHELL_CMD("rs485_init", "r4i", rs485_init_command, "Rs485Init"),

#ifdef __cplusplus
}
#endif

#endif /* RS485_COMMANDS_H */
