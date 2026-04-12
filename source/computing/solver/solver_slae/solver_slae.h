#ifndef SOLVER_SLAE_H
#define SOLVER_SLAE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "solver_slae_types.h"

#ifndef HAS_SOLVER_SLAE
#error "+HAS_SOLVER_SLAE"
#endif

extern SolverSlae_t SolverSlae;
/* Solver for y=ax+b equations */

const char* SlaeToStr(const  SolverSlae_t* const  Solver);

bool solver_slae_init(SolverSlae_t* const Solver , float x1, float y1, float x2, float y2);
bool solver_slae_calc_ab(SolverSlae_t* const Solver);
float solver_slae_calc_y(SolverSlae_t* const Solver, float x);
float solver_slae_calc_x(SolverSlae_t* const Solver, float y);

#ifdef __cplusplus
}
#endif

#endif /* SOLVER_SLAE_H */
