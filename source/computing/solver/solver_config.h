#ifndef SOLVER_CONFIG_H
#define SOLVER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "solver_types.h"

#ifndef HAS_SOLVER
#error "+HAS_SOLVER"
#endif

extern Solver_t Solver;

#ifdef __cplusplus
}
#endif

#endif /* SOLVER_CONFIG_H */
