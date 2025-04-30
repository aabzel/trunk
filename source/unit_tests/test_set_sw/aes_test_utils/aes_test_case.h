
#ifndef AES_TEST_CASE_H
#define AES_TEST_CASE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_AES
#error "+HAS_AES"
#endif

#include "aes_test_types.h"

extern const AES256TestCase_t Case1;
extern const AES256CbcTestCase_t Case2;
extern const AES256CbcTestCase64_t Case3;

#ifdef __cplusplus
}
#endif

#endif /* AES_TEST_CASE_H */
