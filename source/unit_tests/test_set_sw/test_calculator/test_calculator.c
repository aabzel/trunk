#include "test_calculator.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "calculator.h"
#include "float_utils.h"
#include "log.h"
#include "unit_test_assert.h"

bool test_calculator_logic(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(CALC, LOG_LEVEL_DEBUG);
    double result = 0.0;
    ASSERT_TRUE(calculator_calc("2^5", &result)); // 2 xor 5    010 xor 101 =
    ASSERT_EQ_DOUBLE(7.0, result);

    set_log_level(CALC, LOG_LEVEL_INFO);
    return true;
}

bool test_calculator_pow(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(CALC, LOG_LEVEL_DEBUG);
    double result = 0.0;
    ASSERT_TRUE(calculator_calc("2**16", &result));
    ASSERT_EQ_DOUBLE(65536.0, result);
    set_log_level(CALC, LOG_LEVEL_INFO);
    return true;
}

bool test_calculator_integer(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(CALC, LOG_LEVEL_DEBUG);
    double result = 0.0;

    ASSERT_TRUE(calculator_calc("(1+2)*5", &result));
    ASSERT_EQ_DOUBLE(15.0, result);

    ASSERT_TRUE(calculator_calc("1/2", &result));
    ASSERT_EQ_DOUBLE(0.5, result);

    ASSERT_TRUE(calculator_calc("1+2*2", &result));
    ASSERT_EQ_DOUBLE(5.0, result);

    ASSERT_TRUE(calculator_calc("22+2", &result)); /*ok*/
    ASSERT_EQ_DOUBLE(24.0, result);

    set_log_level(CALC, LOG_LEVEL_INFO);

    return true;
}

bool test_calculator_float(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(CALC, LOG_LEVEL_DEBUG);
    double result = 0.0;

    ASSERT_TRUE(calculator_calc("2.4+2.6", &result));
    ASSERT_EQ_DOUBLE(5.0, result);

    set_log_level(CALC, LOG_LEVEL_INFO);

    return true;
}
