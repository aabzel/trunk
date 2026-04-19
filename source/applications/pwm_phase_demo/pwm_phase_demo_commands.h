#ifndef PWM_PHASE_DEMO_COMMANDS_H
#define PWM_PHASE_DEMO_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_PWM_PHASE_DEMO
#error "+ HAS_PWM_PHASE_DEMO"
#endif

#ifndef HAS_PWM_PHASE_DEMO_COMMANDS
#error "+ HAS_PWM_PHASE_DEMO_COMMANDS"
#endif

bool pwm_phase_demo_diag_command(int32_t argc, char* argv[]);
bool pwm_phase_demo_init_command(int32_t argc, char* argv[]);

#define PWM_PHASE_DEMO_COMMANDS                                                                                          \
        SHELL_CMD("pwm_phase_demo_diag", "ppdd", pwm_phase_demo_diag_command, "PwmPhaseDemoDiag"),                           \
        SHELL_CMD("pwm_phase_demo_init", "ppdi", pwm_phase_demo_init_command, "PwmPhaseDemoInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* PWM_PHASE_DEMO_COMMANDS_H */
