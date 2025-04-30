#ifndef TEST_KEYBOARD_UTILS_H
#define TEST_KEYBOARD_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

bool test_keyboard_types(void);
bool test_keyboard_codes(void);
bool test_keyboard_upper_codes(void);
bool test_keyboard_special_codes(void);
bool test_keyboard_lower_codes(void);
bool test_keyboard_codes2(void);

#define TEST_SUIT_KEYBOARD                              \
    {"keyboardTypes", test_keyboard_types},              \
    {"keyboard_special_codes", test_keyboard_special_codes},              \
    {"keyboard_upper_codes", test_keyboard_upper_codes},              \
    {"keyboard_lower_codes", test_keyboard_lower_codes},              \
    {"keyboard_codes", test_keyboard_codes},            \
    {"keyboard_codes2", test_keyboard_codes2},

#ifdef __cplusplus
}
#endif

#endif /* TEST_KEYBOARD_UTILS_H */
