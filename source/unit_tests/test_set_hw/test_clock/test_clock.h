#ifndef TEST_CLOCK_H
#define TEST_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"


bool test_clock_us(void);
bool test_clock_ms(void);

#define TEST_SUIT_CLOCK                \
    {"clock_us", test_clock_us},        \
    {"clock_ms", test_clock_ms},     

#ifdef __cplusplus
}
#endif

#endif /* TEST_CLOCK_H */
