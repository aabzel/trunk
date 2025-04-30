#ifndef TEST_MATH_H
#define TEST_MATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_MATH
#error "It is needed HAS_MATH option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_math_powi(void);
bool test_math_vectors_angle_same_abs(void);
bool test_math_vectors_angle_same_angle(void);
bool test_math_vectors_angle(void);
bool test_math_sin(void);
bool test_math_period(void);
bool test_math_double(void);
bool test_math_double2(void);

#define TEST_SUIT_MATH                  \
    {"math_double2", test_math_double2},      \
    {"math_vectors_angle_same_angle", test_math_vectors_angle_same_angle},      \
    {"math_double", test_math_double},      \
    {"math_vectors_angle", test_math_vectors_angle},      \
    {"math_vectors_angle_same_abs", test_math_vectors_angle_same_abs},      \
    {"math_powi", test_math_powi},      \
    {"math_sin", test_math_sin},        \
    {"math_period", test_math_period},

#ifdef __cplusplus
}
#endif

#endif /* TEST_MATH_H */
