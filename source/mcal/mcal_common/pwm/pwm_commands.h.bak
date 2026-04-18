#ifndef PWM_COMMANDS_H
#define PWM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "pwm_mcal.h"

#ifdef HAS_PWM_CUSTOM_COMMANDS
#include "pwm_custom_commands.h"
#else
#define PWM_CUSTOM_COMMANDS
#endif

#ifndef HAS_PWM
#error "+HAS_PWM"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_PWM_COMMANDS
#error "+HAS_PWM_COMMANDS"
#endif

bool pwm_signal_parse(int32_t argc, char* argv[], uint32_t start , PwmSignalBinary_t * const Node);

bool pwm_frequency_command(int32_t argc, char* argv[]);
bool pwm_enable_command(int32_t argc, char* argv[]);
bool pwm_init_command(int32_t argc, char* argv[]);
bool pwm_diag_command(int32_t argc, char* argv[]);
bool pwm_phase_command(int32_t argc, char* argv[]);
bool pwm_duty_command(int32_t argc, char* argv[]);
bool pwm_period_command(int32_t argc, char* argv[]);

#define PWM_COMMANDS                                                                                    \
    PWM_CUSTOM_COMMANDS                                                                                 \
    SHELL_CMD("pwm_enable", "pe", pwm_enable_command, "PwmEnable"),                                     \
    SHELL_CMD("pwm_init", "pwi", pwm_init_command, "PwmInit"),                                          \
    SHELL_CMD("pwm_duty", "pdu", pwm_duty_command, "PwmDuty"),                                          \
    SHELL_CMD("pwm_diag", "pwd", pwm_diag_command, "PwmDiag"),                                          \
    SHELL_CMD("pwm_frequency", "pf", pwm_frequency_command, "PwmFrequency"),                            \
    SHELL_CMD("pwm_phase", "pps", pwm_phase_command, "PwmPhase"),                                       \
    SHELL_CMD("pwm_period", "pes", pwm_period_command, "PwmPeriod"),

#ifdef __cplusplus
}
#endif

#endif /* PWM_CUSTOM_COMMANDS_H */
