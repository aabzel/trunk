#ifndef TEST_BIT_UTILS_H
#define TEST_BIT_UTILS_H

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

bool test_bit8_swap(void);
bool test_bit16_swap(void);
bool test_bit32_fields(void);
bool test_bit32_swap(void);
bool test_bit64_swap(void);
bool test_bit_mask(void);
bool test_bit_utils(void);
bool test_nimble_set(void);
bool test_bit_type_size(void);
bool test_parse_n_bit_signed(void);
bool test_bit_macro(void);
bool test_bit_adjust_mask(void);
/*
tsr bit_utils+
*/
#define TEST_SUIT_UTILS_BIT                                                                                            \
    {"nimble_set", test_nimble_set}, \
    {"bit32_fields", test_bit32_fields}, \
    {"bit_macro", test_bit_macro}, \
	{"bit_adjust_mask", test_bit_adjust_mask},                                          \
        {"parse_n_bit_signed", test_parse_n_bit_signed}, {"bit8_swap", test_bit8_swap},                                \
        {"bit16_swap", test_bit16_swap}, {"bit32_swap", test_bit32_swap}, {"bit64_swap", test_bit64_swap},             \
        {"bit_utils", test_bit_utils}, {"bit_type_size", test_bit_type_size}, {"bit_mask", test_bit_mask},

#ifdef __cplusplus
}
#endif

#endif /* TEST_BIT_UTILS_H */
