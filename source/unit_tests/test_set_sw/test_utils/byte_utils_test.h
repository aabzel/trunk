#ifndef TEST_BYTE_UTILS_H
#define TEST_BYTE_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_byte_copy_rev(void);
bool test_byte_reverse(void);
bool test_reverse_byte_order64(void);
bool test_array_reverse(void);
bool test_byte_type_sizes(void);

#define TEST_SUIT_UTILS_BYTE                                                                                           \
    {"byte_reverse", test_byte_reverse}, \
    {"reverse_byte_order64", test_reverse_byte_order64}, \
{"array_reverse", test_array_reverse},                                        \
        {"byte_type_sizes", test_byte_type_sizes}, {"byte_copy_rev", test_byte_copy_rev},

#ifdef __cplusplus
}
#endif

#endif /* TEST_BYTE_UTILS_H */
