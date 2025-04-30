
#ifndef TEST_BASE16_H
#define TEST_BASE16_H

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

#ifndef HAS_BASE16
#error "It is needed HAS_BASE16 option for that component"
#endif

#ifndef HAS_TEST_SUIT_BASE16
#error "It is needed HAS_TEST_SUIT_BASE16 option for that component"
#endif

bool test_base16_code(void);
bool test_base16_decode(void);
bool test_is_base16_str(void);

#define TEST_SUIT_BASE16                  \
   {"is_base16_str", test_is_base16_str}, \
   {"base16_decode", test_base16_decode}, \
   {"base16_code", test_base16_code},

#ifdef __cplusplus
}
#endif

#endif /* TEST_BASE16_H */
