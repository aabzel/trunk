#ifndef TEST_TIME_UTILS_H
#define TEST_TIME_UTILS_H

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

bool test_time_types(void);
bool test_time_mcal(void);
bool test_time_cmp(void);
bool test_time_parse(void);
bool test_time_stamp(void);
bool test_time_stamp2(void);

#define TEST_SUIT_UTILS_TIME                                                                                           \
    {"time_types", test_time_types}, \
    {"time_parse", test_time_parse}, \
	{"time_mcal", test_time_mcal}, {"time_stamp", test_time_stamp},                 \
        {"time_stamp2", test_time_stamp2}, {"time_cmp", test_time_cmp},

#ifdef __cplusplus
}
#endif

#endif /* TEST_TIME_UTILS_H */
