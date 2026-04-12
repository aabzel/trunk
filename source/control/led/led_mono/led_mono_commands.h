#ifndef LED_MONO_COMMANDS_H
#define LED_MONO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "ostream.h"

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif

#ifndef HAS_LED
#error "+HAS_LED"
#endif

#ifndef HAS_LED_MONO
#error "+HAS_LED_MONO"
#endif

#ifndef HAS_LED_MONO_COMMANDS
#error "+HAS_LED_MONO_COMMANDS"
#endif


#ifdef HAS_PWM
bool led_mono_set_on_duty_command(int32_t argc, char* argv[]);
bool led_mono_set_off_duty_command(int32_t argc, char* argv[]);

#define LED_MONO_PWM_COMMANDS                                            \
    SHELL_CMD("led_mono_set_on_duty", "lmsod", led_mono_set_on_duty_command, "LedMonoSetOnDuty"),           \
    SHELL_CMD("led_mono_set_off_duty", "lmsofd", led_mono_set_off_duty_command, "LedMonoSetOffDuty"),

#else
#define LED_MONO_PWM_COMMANDS
#endif

bool led_mono_diag_command(int32_t argc, char* argv[]);
bool led_mono_set_command(int32_t argc, char* argv[]);
bool led_mono_init_command(int32_t argc, char* argv[]);
bool led_mono_blink_command(int32_t argc, char* argv[]);
bool led_mono_mode_command(int32_t argc, char* argv[]);

#define LED_MONO_COMMANDS     LED_MONO_PWM_COMMANDS                                       \
    SHELL_CMD("led_mono_init", "lmi", led_mono_init_command, "LedMonoInit"),           \
    SHELL_CMD("led_mono_mode", "lmm", led_mono_mode_command, "LedMonoMode"),           \
    SHELL_CMD("led_mono_diag", "lmd", led_mono_diag_command, "LedMonoDiag"),           \
    SHELL_CMD("led_mono_blink", "lmb", led_mono_blink_command, "LedMonoBlink"),     \
    SHELL_CMD("led_mono_set", "lms", led_mono_set_command, "LedMonoSet"),

#ifdef __cplusplus
}
#endif

#endif /* LED_MONO_COMMANDS_H */
