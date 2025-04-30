#ifndef TEST_CLI_H
#define TEST_CLI_H

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

bool test_cli1(void);
bool test_cli2(void);

#define TEST_SUIT_CLI {"cli1", test_cli1}, {"cli2", test_cli2},

#ifdef __cplusplus
}
#endif

#endif /* TEST_CLI_H */
