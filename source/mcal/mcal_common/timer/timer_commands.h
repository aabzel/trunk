#ifndef TIMER_GENERAL_COMMANDS_H
#define TIMER_GENERAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "timer_custom_commands.h"

#ifndef HAS_CLI
#error "only for CLI"
#endif

bool timer_compare_command(int32_t argc, char* argv[]);
bool timer_diag_compare_complimentary_command(int32_t argc, char* argv[]);
bool timer_ctrl_command(int32_t argc, char* argv[]);
bool timer_diag_compare_command(int32_t argc, char* argv[]);
bool timer_diag_ll_command(int32_t argc, char* argv[]);
bool timer_diag_command(int32_t argc, char* argv[]);
bool timer_prescaler_command(int32_t argc, char* argv[]);
bool timer_overflow_command(int32_t argc, char* argv[]);
bool timer_channel_diag_command(int32_t argc, char* argv[]);
bool timer_set_laod_command(int32_t argc, char* argv[]);
bool timer_period_command(int32_t argc, char* argv[]);
bool timer_frequency_command(int32_t argc, char* argv[]);

#define TIMER_COMMANDS                                                                           \
        TIMER_CUSTOM_COMMANDS                                                                    \
        SHELL_CMD("timer_overflow", "to", timer_overflow_command, "TimerOvefflow"),              \
        SHELL_CMD("timer_ctrl", "tct", timer_ctrl_command, "TimerCtrl"),                         \
        SHELL_CMD("timer_compare", "tsc", timer_compare_command, "TimerCompare"),                \
        SHELL_CMD("timer_diag_compare", "tdc", timer_diag_compare_command, "TimerDiagCompare"),   \
        SHELL_CMD("timer_diag_compare_com", "tdcc", timer_diag_compare_complimentary_command, "TimerDiagCompareComplimentary"),  \
        SHELL_CMD("timer_diag_ll", "tdl", timer_diag_ll_command, "TimerDiagLowLevel"),            \
        SHELL_CMD("timer_diag", "trd", timer_diag_command, "TimerDiag"),                          \
        SHELL_CMD("timer_channel_diag", "tcd", timer_channel_diag_command, "TimerChannelDiag"),   \
        SHELL_CMD("timer_psc", "tsp", timer_prescaler_command, "TimerPrescaler"),                 \
        SHELL_CMD("timer_set_load", "tsl", timer_set_laod_command, "TimerLoad"),                  \
        SHELL_CMD("timer_period", "tp", timer_period_command, "TimerPeriod"),                    \
        SHELL_CMD("timer_frequency", "tf", timer_frequency_command, "TimerFrequency"),

#ifdef __cplusplus
}
#endif

#endif /* TIMER_GENERAL_COMMANDS_H */
