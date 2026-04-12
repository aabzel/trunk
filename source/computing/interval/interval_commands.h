#ifndef INTERVAL_COMMANDS_H
#define INTERVAL_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

bool interval_merge_command(int32_t argc, char* argv[]);
bool interval_intersect_command(int32_t argc, char* argv[]);
bool interval_dock_command(int32_t argc, char* argv[]);

#define INTERVAL_COMMANDS                                                                 \
    SHELL_CMD("interval_merge", "im", interval_merge_command, "IntervalMerge"),           \
    SHELL_CMD("interval_dock", "id", interval_dock_command, "IntervalDock"),              \
    SHELL_CMD("interval_intersect", "ii", interval_intersect_command, "IntervalIntersect"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*INTERVAL_COMMANDS_H*/
