#ifndef TEST_BUTTON_H
#define TEST_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_BUTTON
#error "+HAS_BUTTON"
#endif

#ifndef HAS_TEST_BUTTON
#error "+HAS_TEST_BUTTON"
#endif

bool test_button_types(void);
bool test_button_get(void);

#define TEST_SUIT_BUTTON                     \
    {"button_types", test_button_types},     \
    {"button_get", test_button_get},

#ifdef __cplusplus
}
#endif

#endif /* TEST_BUTTON_H */
