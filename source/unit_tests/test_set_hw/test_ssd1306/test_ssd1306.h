#ifndef TEST_SSD1306_H
#define TEST_SSD1306_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "test_hw_dep_check.h"

#ifndef HAS_SSD1306
#error "+HAS_SSD1306"
#endif

#ifndef HAS_TEST_SSD1306
#error "+HAS_TEST_SSD1306"
#endif

bool test_ssd1306_connected(void);
bool test_ssd1306_types(void);
bool test_ssd1306_dot(void);
bool test_ssd1306_hash_tables(void);
bool test_ssd1306_screen(void);
bool test_ssd1306_char(void);
bool test_ssd1306_text(void);

#define TEST_SUIT_SSD1306                               \
    {"ssd1306_types", test_ssd1306_types},              \
    {"ssd1306_connect", test_ssd1306_connected},        \
    {"ssd1306_dot", test_ssd1306_dot},              \
    {"ssd1306_hash_tables", test_ssd1306_hash_tables},  \
    {"ssd1306_screen", test_ssd1306_screen},       \
    {"ssd1306_char", test_ssd1306_char},    \
    {"ssd1306_text", test_ssd1306_text},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SSD1306_H */
