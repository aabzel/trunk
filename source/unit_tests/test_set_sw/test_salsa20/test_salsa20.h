
#ifndef TEST_SALSA20_H
#define TEST_SALSA20_H

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

#ifndef HAS_SALSA20
#error "It is needed HAS_SALSA20 option for that component"
#endif

bool test_salsa20(void);

#define TEST_SUIT_SALSA20             \
    {"salsa20", test_salsa20},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SALSA20_H */
