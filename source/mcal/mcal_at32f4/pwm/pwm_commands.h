#ifndef PWM_COMMANDS_H
#define PWM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_PWM
#error "+HAS_PWM"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_PWM_COMMANDS
#error "+HAS_PWM_COMMANDS"
#endif

bool oc_enable_command(int32_t argc, char* argv[]);
bool pwm_enable_command(int32_t argc, char* argv[]);
bool pwm_diag_ll_command(int32_t argc, char* argv[]);
bool pwm_diag_command(int32_t argc, char* argv[]);
bool pwm_set_phase_command(int32_t argc, char* argv[]);
bool pwm_set_duty_command(int32_t argc, char* argv[]);
bool pwm_set_period_command(int32_t argc, char* argv[]);

#define PWM_COMMANDS                                                                                                   \
    SHELL_CMD("pwm_enable", "pe", pwm_enable_command, "PwmEnable"),                                                    \
        SHELL_CMD("out_enable", "oe", oc_enable_command, "PwmOutEnable"),                                              \
        SHELL_CMD("pwm_set_duty", "psd", pwm_set_duty_command, "PwmSetDuty"),                                          \
        SHELL_CMD("pwm_diag_ll", "pdl", pwm_diag_ll_command, "PwmDiagLowLevel"),                                       \
        SHELL_CMD("pwm_diag", "pwd", pwm_diag_command, "PwmDiag"),                                                     \
        SHELL_CMD("pwm_set_phase", "psp", pwm_set_phase_command, "PwmSetPhase"),                                       \
        SHELL_CMD("pwm_set_per", "pse", pwm_set_period_command, "PwmPeriod"),

#ifdef __cplusplus
}
#endif

#endif /* PWM_COMMANDS_H */
