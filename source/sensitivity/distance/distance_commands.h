#ifndef DISTANCE_COMMANDS_H
#define DISTANCE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

bool distance_diag_command(int32_t argc, char* argv[]);
bool distance_init_command(int32_t argc, char* argv[]);

#define DISTANCE_COMMANDS                                                      \
    SHELL_CMD("distance_diag", "dd", distance_diag_command, "DistanceDiag"),   \
    SHELL_CMD("distance_init", "di", distance_init_command, "DistanceInit"),

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /*DISTANCE_COMMANDS_H*/
