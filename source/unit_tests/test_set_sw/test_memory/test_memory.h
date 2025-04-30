#ifndef TEST_MEMORY_H
#define TEST_MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_TEST_SUIT_MEMORY
#error "It is needed HAS_TEST_SUIT_MEMORY option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_malloc_zero(void);
bool test_heap(void);

#define TEST_SUIT_MEMORY {"heap", test_heap}, {"malloc_zero", test_malloc_zero},

#ifdef __cplusplus
}
#endif

#endif /* TEST_MEMORY_H */
