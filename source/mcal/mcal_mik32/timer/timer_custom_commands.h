#ifndef TIM_COMMANDS_H
#define TIM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_CLI
#error "only for CLI"
#endif

#if 0
bool tim_diag_compare_command(int32_t argc, char* argv[]);
bool tim_diag_ll_command(int32_t argc, char* argv[]);
bool tim_diag_command(int32_t argc, char* argv[]);
bool tim_set_prescaler_command(int32_t argc, char* argv[]);
bool tim_set_laod_command(int32_t argc, char* argv[]);
bool tim_set_period_command(int32_t argc, char* argv[]);
#endif

#define TIMER_CUSTOM_COMMANDS
#if 0
SHELL_CMD("tim_diag_compare", "tdc", tim_diag_compare_command, "TimDiagComparator"),                               \
        SHELL_CMD("tim_diag_ll", "tdl", tim_diag_ll_command, "TimDiagLowLevel"),                                       \
        SHELL_CMD("tim_diag", "td", tim_diag_command, "TimDiag"),                                                      \
        SHELL_CMD("tim_set_psc", "tsp", tim_set_prescaler_command, "TimPrescaler"),                                    \
        SHELL_CMD("tim_set_load", "tsl", tim_set_laod_command, "TimLoad"),                                             \
        SHELL_CMD("tim_set_per", "tspr", tim_set_period_command, "TimPeriod"),
#endif

#ifdef __cplusplus
}
#endif

#endif /* TIM_COMMANDS_H */
