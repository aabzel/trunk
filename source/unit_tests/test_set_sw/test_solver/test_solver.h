#ifndef TEST_SOLVER_H
#define TEST_SOLVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SOLVER
#error "It is needed HAS_SOLVER option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_solver(void);

#define TEST_SUIT_SOLVER        \
     {"solver", test_solver},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SOLVER_H */
