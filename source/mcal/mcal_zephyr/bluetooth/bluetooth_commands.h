#ifndef BLUETOOTH_COMMANDS_H
#define BLUETOOTH_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_drv.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_BLUETOOTH
#error "+HAS_BLUETOOTH"
#endif

bool bluetooth_init_command(int32_t argc, char* argv[]);
bool bluetooth_load_settings_command(int32_t argc, char* argv[]);
bool bluetooth_unpair_command(int32_t argc, char* argv[]);
bool bluetooth_write_command(int32_t argc, char* argv[]);
bool bluetooth_read_command(int32_t argc, char* argv[]);
bool bluetooth_diag_command(int32_t argc, char* argv[]);
bool bluetooth_scan_command(int32_t argc, char* argv[]);

#define BLUETOOTH_COMMANDS                                                                                    \
    SHELL_CMD("bluetooth_load_settings", "blels", bluetooth_load_settings_command, "BlueToothLoadSettings"),  \
    SHELL_CMD("bluetooth_diag", "bled", bluetooth_diag_command, "BlueToothDiag"),                             \
    SHELL_CMD("bluetooth_unpair", "bleu", bluetooth_unpair_command, "BlueToothUnPair"),                       \
    SHELL_CMD("bluetooth_scan", "bles", bluetooth_scan_command, "BlueToothScan"),                             \
    SHELL_CMD("bluetooth_write", "blew", bluetooth_write_command, "BlueToothWriteHexStr"),                    \
    SHELL_CMD("bluetooth_init", "blei", bluetooth_init_command, "BlueToothInit"),                             \
	SHELL_CMD("bluetooth_read", "bler", bluetooth_read_command, "BlueToothRead"),

#ifdef __cplusplus
}
#endif

#endif /* BLUETOOTH_COMMANDS_H */
