#ifndef TIM_CUSTOM_COMMANDS_H
#define TIM_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "only for CLI"
#endif

bool timer_info_command(int32_t argc, char* argv[]);
bool timer_diag_reg_fields_command(int32_t argc, char* argv[]);

#define TIMER_CUSTOM_COMMANDS \
           SHELL_CMD("timer_info", "timi", timer_info_command, "TimerInfoDiag"),   \
           SHELL_CMD("timer_diag_reg_fields", "tdrf", timer_diag_reg_fields_command, "TimerDiagRegFields"),

#ifdef __cplusplus
}
#endif

#endif /* TIM_CUSTOM_COMMANDS_H */
