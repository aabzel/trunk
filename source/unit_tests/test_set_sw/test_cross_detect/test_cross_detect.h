
#ifndef TEST_CROSS_DETECT_H
#define TEST_CROSS_DETECT_H

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

#ifndef HAS_CROSS_DETECT
#error "It is needed HAS_CROSS_DETECT option for that component"
#endif

#ifndef HAS_TEST_SUIT_CROSS_DETECT
#error "It is needed HAS_TEST_SUIT_CROSS_DETECT option for that component"
#endif

bool test_cross_detect_types(void);
bool test_cross_detect_functions(void);

#define TEST_SUIT_CROSS_DETECT                               \
    {"cross_detect_parse_double", test_cross_detect_types},   \
    {"cross_detect_functions", test_cross_detect_functions},

#ifdef __cplusplus
}
#endif

#endif /* TEST_CROSS_DETECT_H */
