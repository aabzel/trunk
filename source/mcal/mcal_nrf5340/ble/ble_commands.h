#ifndef BLE_COMMANDS_H
#define BLE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool ble_init_command(int32_t argc, char* argv[]);
bool ble_diag_command(int32_t argc, char* argv[]);

#define BLE_COMMANDS                                                                                                 \
        SHELL_CMD("ble_init", "ui", ble_init_command, "UartInit"),                                                  \
        SHELL_CMD("ble_diag", "ud", ble_diag_command, "UartDiag"),                                                  

#ifdef __cplusplus
}
#endif

#endif /* BLE_COMMANDS_H */
