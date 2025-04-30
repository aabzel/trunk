#ifndef TEST_HASHSET_H
#define TEST_HASHSET_H

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

#ifndef HAS_HASHSET
#error "It is needed HAS_HASHSET option for that component"
#endif

bool test_hashset_pull(void);
bool test_hashset_push(void);

#define TEST_SUIT_HASHSET                                         \
    {"hashset_pull", test_hashset_pull},            \
	{"hashset_push", test_hashset_push},


#ifdef __cplusplus
}
#endif

#endif /* TEST_HASHSET_H */
