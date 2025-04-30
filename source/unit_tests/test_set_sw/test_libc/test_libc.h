#ifndef TEST_LIBC_H
#define TEST_LIBC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_UNIT_TEST
#error "It is needed HAS_UNIT_TEST option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_libc_stdio(void);
bool test_libc_sprintf_long(void);
bool test_libc_stdio_uint64(void);
bool test_libc_stdio_small_double(void);
bool test_libc_sprintf_minus(void);

#define TEST_SUIT_LIBC                                                \
    {"libc_stdio", test_libc_stdio},                                  \
    {"libc_stdio_uint64", test_libc_stdio_uint64},                    \
    {"libc_stdio_small_double", test_libc_stdio_small_double},        \
    {"libc_sprintf_long", test_libc_sprintf_long},                    \
    {"libc_sprintf_minus", test_libc_sprintf_minus},

#ifdef __cplusplus
}
#endif

#endif /* TEST_LIBC_H */
