#ifndef TEST_DECAWAVE_NATIVE_H
#define TEST_DECAWAVE_NATIVE_H

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

bool test_decawave_native_types(void);
bool test_decawave_native_nodes(void);

#define TEST_SUIT_DECAWAVE_NATIVE                           \
    {"decawave_nativetypes", test_decawave_native_types},    \
    {"decawave_nativenodes", test_decawave_native_nodes},


#ifdef __cplusplus
}
#endif

#endif /* TEST_DECAWAVE_NATIVE_H */
