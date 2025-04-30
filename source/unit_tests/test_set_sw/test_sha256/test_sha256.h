
#ifndef TEST_SHA256_H
#define TEST_SHA256_H

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

#ifndef HAS_SHA256
#error "It is needed HAS_SHA256 option for that component"
#endif

bool test_sha256(void);

#define TEST_SUIT_SHA256             \
    {"sha256", test_sha256},

#ifdef __cplusplus
}
#endif

#endif /* TEST_SHA256_H */
