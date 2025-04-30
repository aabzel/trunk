#ifndef TEST_DATA_UTILS_H
#define TEST_DATA_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_interval_overlap(void);
bool test_interval_shared(void);
bool test_interval_merge(void);

bool test_int_arround(void);
bool test_int_shift_left(void);
bool test_int_shift_right(void);
bool test_data_sizes(void);
bool test_data_utils(void);
bool test_bin2sacii(void);
bool test_extract_digit(void);
bool test_bit2bytes(void);

#define TEST_SUIT_INTERVAL                       \
    {"interval_merge", test_interval_merge},     \
    {"intervals_shared", test_interval_shared},  \
    {"intervals", test_interval_overlap},

#define TEST_SUIT_UTILS_DATA     TEST_SUIT_INTERVAL                                                                                      \
    {"data_utils", test_data_utils},   \
     {"int_arround", test_int_arround}, \
        {"int_shift_right", test_int_shift_right}, {"int_shift_left", test_int_shift_left},                            \
        {"ExtractDigit", test_extract_digit}, {"data_sizes", test_data_sizes}, {"data_utils", test_data_utils},        \
        {"bit2bytes", test_bit2bytes}, {"bin2sacii", test_bin2sacii},

#ifdef __cplusplus
}
#endif

#endif /* TEST_DATA_UTILS_H */
