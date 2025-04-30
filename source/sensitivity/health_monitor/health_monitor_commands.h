#ifndef HEALTH_MONITOR_COMMAND_H
#define HEALTH_MONITOR_COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_HEALTH_MONITOR_COMMANDS
#error "+HAS_HEALTH_MONITOR_COMMANDS"
#endif

bool pwr_set_save_mode_command(int32_t argc, char* argv[]);
bool health_monitor_command(int32_t argc, char* argv[]);
bool health_monitor_reset_command(int32_t argc, char* argv[]);

#define HEALTH_MONITOR_COMMANDS                                                       \
    SHELL_CMD("health_monitor", "hmd", health_monitor_command, "HealthMonitor"),      \
    SHELL_CMD("health_monitor_reset", "hmr", health_monitor_reset_command, "HealthMonitorReset"),
#ifdef __cplusplus
}
#endif

#endif /* HEALTH_MONITOR_COMMAND_H */
