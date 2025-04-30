#ifndef TEST_DWM3000_H
#define TEST_DWM3000_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_DWM3000
#error "+HAS_DWM3000"
#endif

#ifndef HAS_TEST_DWM3000
#error "+HAS_TEST_DWM3000"
#endif

bool test_dwm3000_connected(void);
bool test_dwm3000_types(void);
bool test_dwm3000_gpio_set(void);
bool test_dwm3000_read(void);
bool test_dwm3000_read_offset(void);

#define TEST_SUIT_DWM3000                              \
    {"dwm3000_types", test_dwm3000_types},             \
    {"dwm3000_gpio_set", test_dwm3000_gpio_set},             \
    {"dwm3000_read", test_dwm3000_read},               \
    {"dwm3000_read_offset", test_dwm3000_read_offset},               \
    {"dwm3000_connect", test_dwm3000_connected},

#ifdef __cplusplus
}
#endif

#endif /* TEST_DWM3000_H */
