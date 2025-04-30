#ifndef SOLVER_CONST_H
#define SOLVER_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_SOLVER
#error "+HAS_SOLVER"
#endif

#define MAX_VALUE_LEN 256
#define SOLVER_LIFO_SIZE 10

typedef enum {
    SOL_ST_INIT,
    SOL_ST_EQUAL,
    SOL_ST_PLUS,
    SOL_ST_MINUS,
    SOL_ST_INTEGER,
    SOL_ST_DOT,
    SOL_ST_FRACTION,
    SOL_ST_DIVIDOR,
    SOL_ST_MULT,
    SOL_ST_EX,
} SolverState_t;

typedef enum {
    CONST_TYPE_B = 0,
    CONST_TYPE_A = 1,
    CONST_TYPE_UNDEF,
} ConstType_t;

typedef enum {
    EQUATION_PART_LEFT,
    EQUATION_PART_RIGHT,
    EQUATION_PART_UNDEF,
} EquationPart_t;

#ifdef __cplusplus
}
#endif

#endif /* SOLVER_CONST_H */
