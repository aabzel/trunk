#ifndef PWM_CUSTOM_COMMANDS_H
#define PWM_CUSTOM_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_PWM
#error "+HAS_PWM"
#endif

#ifndef HAS_CLI
#error "only for CLI"
#endif

#ifndef HAS_PWM_CUSTOM_COMMANDS
#error "+HAS_PWM_CUSTOM_COMMANDS"
#endif

#include "std_includes.h"

bool pwm_phase_sw_command(int32_t argc, char* argv[]) ;
bool pwm_phase_deg_command(int32_t argc, char* argv[]) ;
bool pwm_phase_hw_command(int32_t argc, char* argv[]) ;

#define PWM_CUSTOM_COMMANDS                                                             \
        SHELL_CMD("pwm_phase_hw", "pphah", pwm_phase_hw_command, "PwmPhaseHw"),         \
        SHELL_CMD("pwm_phase_deg", "ppasd", pwm_phase_deg_command, "PwmPhaseDeg"),      \
        SHELL_CMD("pwm_phase_sw", "ppas", pwm_phase_sw_command, "PwmPhaseSw"),


#ifdef __cplusplus
}
#endif

#endif /* PWM_CUSTOM_COMMANDS_H */
