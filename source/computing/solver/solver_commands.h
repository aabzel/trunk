
#ifndef SOLVER_COMMANDS_H
#define SOLVER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#include "solver_slae_commands.h"


#define SOLVER_COMMANDS     SOLVER_SLAE_COMMANDS                                               

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*SOLVER_COMMANDS_H*/
