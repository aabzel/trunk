#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

#ifndef HAS_TEST_SUIT_ARRAY
#error "+HAS_TEST_SUIT_ARRAY"
#endif

bool test_array_i8_mult_sum(void);
bool test_array_i8_mult(void);
bool test_array_bit_to_hex(void);
bool test_array_con_pat(void);
bool test_array_index(void);
bool test_array_shift_right(void);
bool test_array_add_front(void);
bool test_array_insert_first(void);

#define TEST_SUIT_ARRAY                                \
    {"array_i8_mult", test_array_i8_mult},             \
    {"array_i8_mult_sum", test_array_i8_mult_sum},     \
    {"array_bit_to_hex", test_array_bit_to_hex},       \
    {"array_con_pat", test_array_con_pat} ,            \
    {"array_index", test_array_index},                 \
    {"array_insert_first", test_array_insert_first},   \
    {"array_shift_right", test_array_shift_right},     \
    {"array_add_front", test_array_add_front},

#ifdef __cplusplus
}
#endif

#endif /* TEST_ARRAY_H */
