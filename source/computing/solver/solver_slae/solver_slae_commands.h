#ifndef SOLVER_SLAE_COMMANDS_H
#define SOLVER_SLAE_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_SOLVER_SLAE_COMMANDS
#error "+HAS_SOLVER_SLAE_COMMANDS"
#endif

bool solver_slae_calc_y_command(int32_t argc, char* argv[]);
bool solver_slae_calc_x_command(int32_t argc, char* argv[]);
bool solver_slae_calc_ab_command(int32_t argc, char* argv[]);

#define SOLVER_SLAE_COMMANDS                                                    \
    SHELL_CMD("solver_slae_calc_y", "sy", solver_slae_calc_y_command, "SolverSlaeCalcY"),     \
    SHELL_CMD("solver_slae_calc_x", "sx", solver_slae_calc_x_command, "SolverSlaeCalcX"),     \
    SHELL_CMD("solver_slae_calc_ab", "sab", solver_slae_calc_ab_command, "SolverSlaeCalcAb"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*SOLVER_SLAE_COMMANDS_H*/
