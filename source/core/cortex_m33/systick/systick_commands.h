#ifndef SYSTICK_COMMANDS_H
#define SYSTICK_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "ostream.h"

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_SYSTICK
#error "+HAS_SYSTICK"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_CORE_COMMANDS
#error "+HAS_CORE_COMMANDS"
#endif

#ifdef HAS_SYSTICK_CUSTOM_COMMANDS
#include "systick_custom_commands.h"
#else
#define SYSTICK_CUSTOM_COMMANDS
#endif

bool systick_start_command(int32_t argc, char* argv[]);
bool systick_stop_command(int32_t argc, char* argv[]);
bool systick_set_load_command(int32_t argc, char* argv[]);
bool systick_clksrc_command(int32_t argc, char* argv[]);
bool systick_diag_command(int32_t argc, char* argv[]);
bool systick_init_command(int32_t argc, char* argv[]);
bool systick_set_cnt_command(int32_t argc, char* argv[]);

#define SYSTICK_COMMANDS                                                                                       \
    SYSTICK_CUSTOM_COMMANDS                                                                                    \
    SHELL_CMD("systick_set_cnt",    "stkt",  systick_set_cnt_command, "SysTickSetCnt"),                        \
    SHELL_CMD("systick_clk",    "stkc",  systick_clksrc_command, "SysTickClkSrc"),                             \
    SHELL_CMD("systick_init",    "stki",  systick_init_command, "SysTickInit"),                                \
    SHELL_CMD("systick_diag",    "stkd",  systick_diag_command, "SysTickDiag"),                                \
    SHELL_CMD("systick_start",   "stks",  systick_start_command, "SysTicStart"),                               \
    SHELL_CMD("systick_stop",    "stkp",  systick_stop_command, "SysTicStop"),                                 \
    SHELL_CMD("systic_set_load", "stkl", systick_set_load_command, "SysTicSetLoad"),

#ifdef __cplusplus
}
#endif

#endif /* SYSTICK_COMMANDS_H */
