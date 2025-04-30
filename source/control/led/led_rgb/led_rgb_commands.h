#ifndef LED_RGB_COMMANDS_H
#define LED_RGB_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_LED
#error "+HAS_LED"
#endif  /*HAS_LED*/

#ifndef HAS_LED_RGB
#error "+HAS_LED_RGB"
#endif  /*HAS_LED_RGB*/

#ifndef HAS_LED_RGB_COMMANDS
#error "+HAS_LED_RGB_COMMANDS"
#endif  /*HAS_LED_RGB_COMMANDS*/

bool led_rgb_get_command(int32_t argc, char* argv[]);
bool led_rgb_color_command(int32_t argc, char* argv[]);
bool led_rgb_init_command(int32_t argc, char* argv[]);
bool led_rgb_set_command(int32_t argc, char* argv[]);

#define LED_RGB_COMMANDS                                                      \
    SHELL_CMD("led_rgb_color", "lrc", led_rgb_color_command, "LedRgbColor"),   \
    SHELL_CMD("led_rgb_get", "lrg", led_rgb_get_command, "LedRgbGet"),   \
    SHELL_CMD("led_rgb_init", "lri", led_rgb_init_command, "LedRgbInit"),   \
    SHELL_CMD("led_rgb_set", "lrs", led_rgb_set_command, "LedRgbSet"),

#ifdef __cplusplus
}
#endif

#endif /* LED_RGB_COMMANDS_H */
