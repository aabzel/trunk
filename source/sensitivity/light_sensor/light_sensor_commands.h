#ifndef LIGHT_SENSOR_MONO_COMMANDS_H
#define LIGHT_SENSOR_MONO_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_LIGHT_SENSOR
#error "+HAS_LIGHT_SENSOR"
#endif  /*HAS_LIGHT_SENSOR*/

bool light_sensor_get_command(int32_t argc, char* argv[]);
bool light_sensor_init_command(int32_t argc, char* argv[]);

#define LIGHT_SENSOR_MONO_COMMANDS                                            \
    SHELL_CMD("light_sensor_init", "lsi", light_sensor_init_command, "LightSensorInit"),           \
    SHELL_CMD("light_sensor_get", "lsg", light_sensor_get_command, "LightSensorGet"),           \

#ifdef __cplusplus
}
#endif

#endif /* LIGHT_SENSOR_MONO_COMMANDS_H */
