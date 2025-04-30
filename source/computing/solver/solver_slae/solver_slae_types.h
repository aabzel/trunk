#ifndef SOLVER_SLAE_TYPES_H
#define SOLVER_SLAE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "solver_slae_const.h"

#ifndef HAS_SOLVER_SLAE
#error "+HAS_SOLVER_SLAE"
#endif

typedef struct {
    double x;
    double y;
}Mapping_t;

typedef struct{
    double a;
    double b;
    Mapping_t M[2];
}SolverSlae_t;

#ifdef __cplusplus
}
#endif

#endif /* SOLVER_SLAE_TYPES_H */
