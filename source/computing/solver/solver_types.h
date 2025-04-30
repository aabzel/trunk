#ifndef SOLVER_TYPES_H
#define SOLVER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "solver_const.h"

#ifndef HAS_SOLVER
#error "+HAS_SOLVER"
#endif

#include "lifo_array.h"

/* Solver for ax+b=0; equations   ax=-b x = -b/a*/

typedef struct{
	char prev_letter;
	EquationPart_t equation_part;
	SolverState_t cur_state;
	bool solution_found;
	bool inf_solution;
	bool no_solution;
	char value_str[MAX_VALUE_LEN];
	uint32_t value_idx;
    int8_t cur_val_sign;
	double a[100];
	uint32_t a_cnt;
	double b[100];
	uint32_t b_cnt;
	Array_t ArrayHeap[SOLVER_LIFO_SIZE];
	LifoArray_t LifoArray;
	ConstType_t const_type;
	bool init;
	double x;
}Solver_t;

#ifdef __cplusplus
}
#endif

#endif /* SOLVER_TYPES_H */
