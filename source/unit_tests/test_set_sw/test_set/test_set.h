#ifndef TEST_SET_H
#define TEST_SET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SET
#error "It is needed HAS_SET option for that component"
#endif

bool test_set_push(void);

#define TEST_SUIT_SET                                         \
	{"set_push", test_set_push},


#ifdef __cplusplus
}
#endif

#endif /* TEST_SET_H */
