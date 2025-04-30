
#ifndef TEST_BASE64_H
#define TEST_BASE64_H

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

#ifndef HAS_BASE64
#error "It is needed HAS_BASE64 option for that component"
#endif

#ifndef HAS_TEST_SUIT_BASE64
#error "It is needed HAS_TEST_SUIT_BASE64 option for that component"
#endif

bool test_base64_code(void);
bool test_base64_decode(void);

#define TEST_SUIT_BASE64                  \
   {"base64_decode", test_base64_decode}, \
   {"base64_code", test_base64_code},

#ifdef __cplusplus
}
#endif

#endif /* TEST_BASE64_H */
