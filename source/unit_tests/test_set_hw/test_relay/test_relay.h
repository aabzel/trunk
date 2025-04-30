#ifndef RELAY_TEST_H
#define RELAY_TEST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_HW_TESTS
#error "It is needed HAS_HW_TESTS option for that component"
#endif

#ifndef HAS_RELAY
#error "It is needed to add HAS_RELAY option"
#endif

bool test_relay(void);

#define TEST_SUIT_RELAY   {"relay", test_relay},

#ifdef __cplusplus
}
#endif

#endif /* RELAY_TEST_H */
