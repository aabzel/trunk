
#ifndef TEST_CALCULATOR_H
#define TEST_CALCULATOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>


#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_CALCULATOR
#error "It is needed HAS_CALCULATOR option for that component"
#endif

bool test_calculator_float(void);
bool test_calculator_pow(void);
bool test_calculator_logic(void);
bool test_calculator_integer(void);

#define TEST_SUIT_CALCULATOR                 \
    {"calculator_integer", test_calculator_integer}, \
    {"calculator_pow", test_calculator_pow}, \
    {"calculator_logic", test_calculator_logic}, \
    {"calculator_float", test_calculator_float},

#ifdef __cplusplus
}
#endif

#endif /* TEST_CALCULATOR_H */
