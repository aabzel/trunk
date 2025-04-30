#ifndef TEST_LIFO_ARRAY_H
#define TEST_LIFO_ARRAY_H

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

#ifndef HAS_LIFO
#error "It is needed HAS_LIFO option for that component"
#endif

bool test_lifo_array_types(void);
bool test_lifo_array(void);
bool test_lifo_array_packing(void);

#define TEST_SUIT_LIFO_ARRAY                            \
    {"lifo_array_types", test_lifo_array_types},        \
    {"lifo_array_pack", test_lifo_array_packing},       \
    {"lifo_array", test_lifo_array},

#ifdef __cplusplus
}
#endif

#endif /* TEST_LIFO_ARRAY_H */
