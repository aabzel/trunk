#ifndef TIMER_CUSTOM_COMMANDS_H
#define TIMER_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ostream.h"

#ifndef HAS_CLI
#error "only for CLI"
#endif

bool timer_raw_reg_command(int32_t argc, char* argv[]);
bool timer_reg_parse_command(int32_t argc, char* argv[]);


#define TIMER_CUSTOM_COMMANDS                                         \
    SHELL_CMD("timer_reg_ll", "timrrl", timer_reg_parse_command, "TimerRegParse"), \
    SHELL_CMD("timer_raw_reg", "timra", timer_raw_reg_command, "TimerRawReg"),


#ifdef __cplusplus
}
#endif

#endif /* TIMER_CUSTOM_COMMANDS_H */
