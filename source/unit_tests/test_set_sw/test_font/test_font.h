#ifndef TEST_FONT_H
#define TEST_FONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_FONT
#error "It is needed HAS_FONT option for that component"
#endif

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_font_types(void);
bool test_font_hash(void);

#ifdef HAS_FONT_12_X_6
bool test_font_12(void);
bool test_font_raw_12(void);

#define TEST_FONT_RAW_12 {"font_12", test_font_12}, {"font_raw_12", test_font_raw_12},
#else
#define TEST_FONT_RAW_12
#endif

#ifdef HAS_FONT_16_X_8
bool test_font_16(void);
bool test_font_raw_16(void);

#define TEST_FONT_RAW_16 {"font_16", test_font_16}, {"font_raw_16", test_font_raw_16},
#else
#define TEST_FONT_RAW_16
#endif

#ifdef HAS_FONT_24_X_12
bool test_font_24(void);
bool test_font_raw_24(void);

#define TEST_FONT_RAW_24{"font_24", test_font_24}, {"font_raw_24", test_font_raw_24},
#else
#define TEST_FONT_RAW_24
#endif

#define TEST_SUIT_FONT                \
    {"font_types", test_font_types},        \
    {"font_hash", test_font_hash},        \
	TEST_FONT_RAW_12   \
	TEST_FONT_RAW_16   \
	TEST_FONT_RAW_24

#ifdef __cplusplus
}
#endif

#endif /* TEST_FONT_H */
