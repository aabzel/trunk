#ifndef LED_MONO_PWM_COMMANDS_H
#define LED_MONO_PWM_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_LED_MONO_PWM
#error "+ HAS_LED_MONO_PWM"
#endif

#ifndef HAS_LED_MONO_PWM_COMMANDS
#error "+ HAS_LED_MONO_PWM_COMMANDS"
#endif

bool led_mono_pwm_diag_command(int32_t argc, char* argv[]);
bool led_mono_pwm_init_command(int32_t argc, char* argv[]);

#define LED_MONO_PWM_COMMANDS                                                                                          \
        SHELL_CMD("led_mono_pwm_diag", "lmpd", led_mono_pwm_diag_command, "LedMonoPwmDiag"),                           \
        SHELL_CMD("led_mono_pwm_init", "lmpi", led_mono_pwm_init_command, "LedMonoPwmInit"),                           \

#ifdef __cplusplus
}
#endif

#endif /* LED_MONO_PWM_COMMANDS_H */
