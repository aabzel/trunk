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

bool pwm_enable_command(int32_t argc, char* argv[]);
bool pwm_init_command(int32_t argc, char* argv[]);
bool pwm_diag_command(int32_t argc, char* argv[]);
bool pwm_phase_set_command(int32_t argc, char* argv[]);
bool pwm_duty_set_command(int32_t argc, char* argv[]);
bool pwm_period_set_command(int32_t argc, char* argv[]);

#define PWM_COMMANDS                                                                                                   \
    SHELL_CMD("pwm_enable", "pe", pwm_enable_command, "PwmEnable"),                                                    \
        SHELL_CMD("pwm_init", "pwi", pwm_init_command, "PwmInit"),                                                     \
        SHELL_CMD("pwm_duty_set", "pds", pwm_duty_set_command, "PwmDutySet"),                                          \
        SHELL_CMD("pwm_diag", "pwd", pwm_diag_command, "PwmDiag"),                                                     \
        SHELL_CMD("pwm_phase_set", "pps", pwm_phase_set_command, "PwmPhaseSet"),                                       \
        SHELL_CMD("pwm_set_per", "pes", pwm_period_set_command, "PwmPeriodSet"),

#ifdef __cplusplus
}
#endif

#endif /* PWM_CUSTOM_COMMANDS_H */
