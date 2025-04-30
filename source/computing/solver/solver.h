#ifndef SOLVER_H
#define SOLVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "solver_types.h"

#ifndef HAS_SOLVER
#error "+HAS_SOLVER"
#endif

/* Solver for ax+b=0; equations */

bool solver_init(Solver_t* Solver);
bool solver_equation_order1(Solver_t* Solver, const char* const equation);

#ifdef __cplusplus
}
#endif

#endif /* SOLVER_H */
