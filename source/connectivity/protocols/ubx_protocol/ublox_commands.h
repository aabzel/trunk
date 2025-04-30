#ifndef U_BLOX_COMMAND_H
#define U_BLOX_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cli_manager.h"

bool ubx_nav_command(int32_t argc, char* argv[]);
// bool ubx_print_key_val_command(int32_t argc, char* argv[]);
bool ubx_diag_command(int32_t argc, char* argv[]);
bool ubx_diag_base_command(int32_t argc, char* argv[]);

#define UBLOX_BASE_COMMANDS                                                                                                 \
    SHELL_CMD("ubx_diag_base", "ubb", ubx_diag_base_command, "U-Blox DiagBase"),                                                     \
    SHELL_CMD("ubx_diag", "ubd", ubx_diag_command, "U-Blox diag"),                                                     \
        SHELL_CMD("ubx_nav", "ubn", ubx_nav_command, "U-Blox navigation result"),                                      \


#ifdef HAS_UBX_EXT
// bool ubx_print_key_val_command(int32_t argc, char* argv[]);
bool ubx_send_command(int32_t argc, char* argv[]);
bool ubx_get_key_command(int32_t argc, char* argv[]);
bool ubx_set_val_command(int32_t argc, char* argv[]);

#define UBLOX_EXT_COMMANDS                                                                                                 \
    SHELL_CMD("ubx_diag", "ubd", ubx_diag_command, "U-Blox diag"),                                                     \
        SHELL_CMD("ubx_set_val", "ubsv", ubx_set_val_command, "U-Blox set Val"),                                       \
        SHELL_CMD("ubx_send", "ubs", ubx_send_command, "U-Blox Send packet"),                                          \
        SHELL_CMD("ubx_getey", "ubg", ubx_get_key_command, "U-Blox get key"),
#else
#define UBLOX_EXT_COMMAND
#endif

#define UBLOX_COMMANDS          \
        UBLOX_EXT_COMMAND       \
        UBLOX_BASE_COMMANDS

#ifdef __cplusplus
}
#endif

#endif /* U_BLOX_COMMAND_H */
