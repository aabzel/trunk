#ifndef SOCKET_COMMAND_H
#define SOCKET_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_SOCKET
#error "+HAS_SOCKET"
#endif

#ifndef HAS_SOCKET_COMMANDS
#error "+HAS_SOCKET_COMMANDS"
#endif

bool socket_diag_command(int32_t argc, char* argv[]);
bool socket_init_command(int32_t argc, char* argv[]);
bool socket_client_send_command(int32_t argc, char* argv[]);
bool socket_server_send_command(int32_t argc, char* argv[]);
bool socket_server_start_command(int32_t argc, char* argv[]);
bool socket_client_start_command(int32_t argc, char* argv[]);

#define SOCKET_COMMANDS                                                                                    \
    SHELL_CMD("socket_diag", "sod", socket_diag_command, "SocketDiag"),                                    \
    SHELL_CMD("socket_server_send", "sss", socket_server_send_command, "SocketServerSend"),                \
    SHELL_CMD("socket_server_start", "ssl", socket_server_start_command, "SocketServerStart"),             \
    SHELL_CMD("socket_client_start", "scl", socket_client_start_command, "SocketClientStart"),             \
    SHELL_CMD("socket_init", "soi", socket_init_command, "SocketInit"),                                    \
    SHELL_CMD("socket_client_send", "scs", socket_client_send_command, "SocketClientSend"),

#ifdef __cplusplus
}
#endif

#endif /* SOCKET_COMMAND_H */
