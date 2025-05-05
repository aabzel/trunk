#ifndef SERIAL_PORT_COMMAND_H
#define SERIAL_PORT_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_SERIAL_PORT
#error "+HAS_SERIAL_PORT"
#endif

#ifndef HAS_SERIAL_PORT_COMMANDS
#error "+HAS_SERIAL_PORT_COMMANDS"
#endif

bool serial_port_diag_command(int32_t argc, char* argv[]);
bool serial_port_init_command(int32_t argc, char* argv[]);
bool serial_port_send_command(int32_t argc, char* argv[]);

#define SERIAL_PORT_COMMANDS                                                                                    \
    SHELL_CMD("serial_port_init", "spi", serial_port_init_command, "SerialPortInit"),                                    \
    SHELL_CMD("serial_port_diag", "spd", serial_port_diag_command, "SerialPortDiag"),                                    \
    SHELL_CMD("serial_port_send", "sps", serial_port_send_command, "SerialPortSend"),

#ifdef __cplusplus
}
#endif

#endif /* SERIAL_PORT_COMMAND_H */
