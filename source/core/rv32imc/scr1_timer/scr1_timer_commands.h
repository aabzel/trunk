#ifndef SCR1_TIMER_COMMANDS_H
#define SCR1_TIMER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_LOG_UTILS
#include "ostream.h"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

#ifndef HAS_SCR1_TIMER
#error "+HAS_SCR1_TIMER"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_CORE_COMMANDS
#error "+HAS_CORE_COMMANDS"
#endif

#ifdef HAS_SCR1_TIMER_CUSTOM_COMMANDS
#include "scr1_timer_custom_commands.h"
#else
#define SCR1_TIMER_CUSTOM_COMMANDS
#endif

bool scr1_timer_start_command(int32_t argc, char* argv[]);
bool scr1_timer_stop_command(int32_t argc, char* argv[]);
bool scr1_timer_reset_command(int32_t argc, char* argv[]);
bool scr1_timer_diag_command(int32_t argc, char* argv[]);
bool scr1_timer_init_command(int32_t argc, char* argv[]);
bool scr1_timer_set_cnt_command(int32_t argc, char* argv[]);

#define SCR1_TIMER_COMMANDS                                                                        \
    SCR1_TIMER_CUSTOM_COMMANDS                                                                     \
    SHELL_CMD("scr1_timer_set_cnt", "sctc", scr1_timer_set_cnt_command, "Scr1TimerSetCnt"),        \
    SHELL_CMD("scr1_timer_init", "scti", scr1_timer_init_command, "Scr1TimerInit"),                \
    SHELL_CMD("scr1_timer_diag", "sctd", scr1_timer_diag_command, "Scr1TimerDiag"),                \
    SHELL_CMD("scr1_timer_start", "scts", scr1_timer_start_command, "SysTicStart"),                \
    SHELL_CMD("scr1_timer_reset", "sctr", scr1_timer_reset_command, "SysTicReset"),                \
    SHELL_CMD("scr1_timer_stop", "sctp", scr1_timer_stop_command, "SysTicStop"),

#ifdef __cplusplus
}
#endif

#endif /* SCR1_TIMER_COMMANDS_H */
