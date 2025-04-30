#ifndef RELAY_COMMANDS_H
#define RELAY_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool relay_blink_command(int32_t argc, char* argv[]);
bool relay_diag_command(int32_t argc, char* argv[]);
bool relay_get_command(int32_t argc, char* argv[]);
bool relay_init_command(int32_t argc, char* argv[]);
bool relay_set_command(int32_t argc, char* argv[]);

#define RELAY_COMMANDS                                                    \
      SHELL_CMD("relay_blink", "rb", relay_blink_command, "RelayBlink"),  \
      SHELL_CMD("relay_diag", "rd", relay_diag_command, "RelayDiag"),     \
      SHELL_CMD("relay_init", "ri", relay_init_command, "RelayInit"),     \
      SHELL_CMD("relay_get", "rg", relay_get_command, "RelayGet"),        \
      SHELL_CMD("relay_set", "rs", relay_set_command, "RelaySet"),

#ifdef __cplusplus
}
#endif

#endif /* RELAY_COMMANDS_H  */
