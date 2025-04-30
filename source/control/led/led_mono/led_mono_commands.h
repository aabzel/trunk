#ifndef LED_MONO_COMMANDS_H
#define LED_MONO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif  /*HAS_GPIO*/

#ifndef HAS_LED
#error "+HAS_LED"
#endif  /*HAS_LED*/

#ifndef HAS_LED_MONO
#error "+HAS_LED_MONO"
#endif  /*HAS_LED_MONO*/

#ifndef HAS_LED_MONO_COMMANDS
#error "+HAS_LED_MONO_COMMANDS"
#endif  /*HAS_LED_MONO_COMMANDS*/

bool led_mono_get_command(int32_t argc, char* argv[]);
bool led_mono_set_command(int32_t argc, char* argv[]);
bool led_mono_init_command(int32_t argc, char* argv[]);
bool led_mono_blink_command(int32_t argc, char* argv[]);
bool led_mono_mode_command(int32_t argc, char* argv[]);

#define LED_MONO_COMMANDS                                            \
    SHELL_CMD("led_mono_init", "lmi", led_mono_init_command, "LedMonoInit"),           \
    SHELL_CMD("led_mono_mode", "lmm", led_mono_mode_command, "LedMonoMode"),           \
    SHELL_CMD("led_mono_get", "lmg", led_mono_get_command, "LedMonoGet"),           \
    SHELL_CMD("led_mono_blink", "lmb", led_mono_blink_command, "LedMonoBlink"),     \
    SHELL_CMD("led_mono_set", "lms", led_mono_set_command, "LedMonoSet"),

#ifdef __cplusplus
}
#endif

#endif /* LED_MONO_COMMANDS_H */
