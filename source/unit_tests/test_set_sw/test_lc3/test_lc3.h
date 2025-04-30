#ifndef TEST_LC3_H
#define TEST_LC3_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifndef HAS_LC3
#error "It is needed HAS_LC3 option for that component"
#endif

#ifndef HAS_SW_TESTS
#error "It is needed HAS_SW_TESTS option for that component"
#endif

bool test_lc3(void);

#ifdef HAS_LC3_ENCODE
bool test_lc3_encode(void);
#define TEST_SUIT_LC3_ENCODE {"lc3_encode", test_lc3_encode},
#else
#define TEST_SUIT_LC3_ENCODE
#endif

#ifdef HAS_LC3_DECODE
bool test_lc3_decode(void);
#define TEST_SUIT_LC3_DECODE   {"lc3_decode", test_lc3_decode},
#else
#define TEST_SUIT_LC3_DECODE
#endif

#define TEST_SUIT_LC3            \
  TEST_SUIT_LC3_ENCODE \
  TEST_SUIT_LC3_DECODE  {"lc3", test_lc3},

#ifdef __cplusplus
}
#endif

#endif /* TEST_LC3_H */
