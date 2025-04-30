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

bool solver_slae_init(SolverSlae_t* const Solver , double x1, double y1, double x2, double y2);
bool solver_slae_calc_ab(SolverSlae_t* const Solver);
double solver_slae_calc_y(SolverSlae_t* const Solver, double x);
double solver_slae_calc_x(SolverSlae_t* const Solver, double y);

#ifdef __cplusplus
}
#endif

#endif /* SOLVER_SLAE_H */
