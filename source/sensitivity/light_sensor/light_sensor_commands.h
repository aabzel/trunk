#ifndef LIGHT_SENSOR_MONO_COMMANDS_H
#define LIGHT_SENSOR_MONO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "ostream.h"

#ifndef HAS_GPIO
#error "+HAS_GPIO"
#endif  /*HAS_GPIO*/

#ifndef HAS_LIGHT_SENSOR
#error "+HAS_LIGHT_SENSOR"
#endif  /*HAS_LIGHT_SENSOR*/

#ifndef HAS_LIGHT_SENSOR_MONO
#error "+HAS_LIGHT_SENSOR_MONO"
#endif  /*HAS_LIGHT_SENSOR_MONO*/

#ifndef HAS_LIGHT_SENSOR_MONO_COMMANDS
#error "+HAS_LIGHT_SENSOR_MONO_COMMANDS"
#endif  /*HAS_LIGHT_SENSOR_MONO_COMMANDS*/

bool light_sensor_get_command(int32_t argc, char* argv[]);
bool light_sensor_set_command(int32_t argc, char* argv[]);
bool light_sensor_init_command(int32_t argc, char* argv[]);
bool light_sensor_blink_command(int32_t argc, char* argv[]);

#define LIGHT_SENSOR_MONO_COMMANDS                                            \
    SHELL_CMD("light_sensor_init", "lmi", light_sensor_init_command, "LedMonoInit"),           \
    SHELL_CMD("light_sensor_get", "lmg", light_sensor_get_command, "LedMonoGet"),           \
    SHELL_CMD("light_sensor_blink", "lmb", light_sensor_blink_command, "LedMonoBlink"),     \
    SHELL_CMD("light_sensor_set", "lms", light_sensor_set_command, "LedMonoSet"),

#ifdef __cplusplus
}
#endif

#endif /* LIGHT_SENSOR_MONO_COMMANDS_H */
