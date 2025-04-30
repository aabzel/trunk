#ifndef SWD_COMMANDS_H
#define SWD_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "debug_info.h"
#include "ostream.h"

#ifndef HAS_SWD
#error "+HAS_SWD"
#endif

#ifndef HAS_MICROCONTROLLER
#error "+HAS_MICROCONTROLLER"
#endif

#ifdef HAS_SWD_CUSTOM
#include "swd_custom_commands.h"
#else /*HAS_SWD_CUSTOM*/
#define SWD_CUSTOM_COMMANDS
#endif /*HAS_SWD_CUSTOM*/

bool swd_set_baudrate_command(int32_t argc, char* argv[]);
bool swd_send_command(int32_t argc, char* argv[]);
bool swd_wait_send_command(int32_t argc, char* argv[]);
bool swd_send_wait_command(int32_t argc, char* argv[]);
bool swd_init_command(int32_t argc, char* argv[]);
bool swd_diag_command(int32_t argc, char* argv[]);
bool swd_dma_send_command(int32_t argc, char* argv[]);

#define SWD_COMMANDS    \
        SWD_CUSTOM_COMMANDS                                                                  \
        SHELL_CMD("swd_baud", "ub", swd_set_baudrate_command, "SwdSetBaud"),            \
        SHELL_CMD("swd_send", "us", swd_send_command, "SwdSend"),              \
        SHELL_CMD("swd_dma_send", "udms", swd_dma_send_command, "SwdDmaSend"),              \
        SHELL_CMD("swd_wait_send", "uws", swd_wait_send_command, "SwdWaitSend"),              \
        SHELL_CMD("swd_send_wait", "usw", swd_send_wait_command, "SwdSendWait"),              \
        SHELL_CMD("swd_init", "ui", swd_init_command, "SwdInit"),                       \
        SHELL_CMD("swd_diag", "ud", swd_diag_command, "SwdDiag"),

#ifdef __cplusplus
}
#endif

#endif /* SWD_COMMANDS_H */
