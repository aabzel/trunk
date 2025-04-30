#ifndef CAN_COMMANDS_H
#define CAN_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "debug_info.h"
#include "ostream.h"

#ifndef HAS_CAN
#error "+HAS_CAN"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifdef HAS_CAN_CUSTOM
#include "can_custom_commands.h"
#else /*HAS_CAN_CUSTOM*/
#define CAN_CUSTOM_COMMANDS
#endif /*HAS_CAN_CUSTOM*/

bool can_bit_rate_command(int32_t argc, char* argv[]);
bool can_send_command(int32_t argc, char* argv[]);
bool can_init_command(int32_t argc, char* argv[]);
bool can_diag_command(int32_t argc, char* argv[]);

#define CAN_COMMANDS                                                             \
        CAN_CUSTOM_COMMANDS                                                      \
        SHELL_CMD("can_baud", "cb", can_bit_rate_command, "CanBaud"),            \
        SHELL_CMD("can_send", "cs", can_send_command, "CanSendHexStr"),          \
        SHELL_CMD("can_init", "ci", can_init_command, "CanInit"),                \
        SHELL_CMD("can_diag", "cad", can_diag_command, "CanDiag"),

#ifdef __cplusplus
}
#endif

#endif /* CAN_COMMANDS_H */
