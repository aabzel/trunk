#ifndef SOFTWARE_TIMER_COMMANDS_H
#define SOFTWARE_TIMER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_SOFTWARE_TIMER_COMMANDS
#error "only for HAS_SOFTWARE_TIMER_COMMANDS"
#endif

#ifndef HAS_SOFTWARE_TIMER
#error "only for HAS_SOFTWARE_TIMER"
#endif

bool sw_timer_set_handler_command(int32_t argc, char* argv[]);
bool sw_timer_diag_command(int32_t argc, char* argv[]);
bool sw_timer_set_command(int32_t argc, char* argv[]);
bool sw_timer_timer_command(int32_t argc, char* argv[]);

#define SOFTWARE_TIMER_COMMANDS                                                                                     \
    SHELL_CMD("sw_timer_timer", "timer", sw_timer_timer_command, "SwTimer"),                   \
    SHELL_CMD("sw_timer_set_handler", "stdc", sw_timer_set_handler_command, "SwTimerSetHandler"),                   \
        SHELL_CMD("sw_timer_diag", "std", sw_timer_diag_command, "SwTimerDiag"),                                    \
        SHELL_CMD("sw_timer_set", "sts", sw_timer_set_command, "SwTimerSet"),



#ifdef __cplusplus
}
#endif

#endif /* SOFTWARE_TIMER_COMMANDS_H */
