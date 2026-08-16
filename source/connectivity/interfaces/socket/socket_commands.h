#ifndef SOCKET_COMMAND_H
#define SOCKET_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
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

#ifdef HAS_SOCKET_CLIENT
bool socket_client_send_command(int32_t argc, char* argv[]);
bool socket_client_start_command(int32_t argc, char* argv[]);

#define SOCKET_CLIENT_COMMANDS                                                                             \
    SHELL_CMD("socket_client_start", "scl", socket_client_start_command, "SocketClientStart"),             \
    SHELL_CMD("socket_client_send", "scs", socket_client_send_command, "SocketClientSend"),
#else
#define SOCKET_CLIENT_COMMANDS
#endif


#ifdef HAS_SOCKET_SERVER
bool socket_server_send_command(int32_t argc, char* argv[]);
bool socket_server_start_command(int32_t argc, char* argv[]);

#define SOCKET_SERVER_COMMANDS                                                                     \
    SHELL_CMD("socket_server_send", "sss", socket_server_send_command, "SocketServerSend"),        \
    SHELL_CMD("socket_server_start", "ssl", socket_server_start_command, "SocketServerStart"),
#else
#define SOCKET_SERVER_COMMANDS
#endif

bool socket_diag_command(int32_t argc, char* argv[]);
bool socket_init_command(int32_t argc, char* argv[]);

#define SOCKET_COMMANDS                                                          \
    SOCKET_CLIENT_COMMANDS                                                       \
    SOCKET_SERVER_COMMANDS                                                       \
    SHELL_CMD("socket_diag", "sod", socket_diag_command, "SocketDiag"),          \
    SHELL_CMD("socket_init", "soi", socket_init_command, "SocketInit"),

#ifdef __cplusplus
}
#endif

#endif /* SOCKET_COMMAND_H */
