#ifndef TEST_CRYP_HW_H
#define TEST_CRYP_HW_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "aes_test_types.h"
#include "test_hw_dep_check.h"

#ifndef HAS_CRYP
#error "+HAS_CRYP"
#endif

#ifndef HAS_TEST_CRYP_HW
#error "It is needed HAS_TEST_CRYP_HW option for that component"
#endif

bool test_hw_aes256_ecb_encrypt(void);
bool test_hw_aes256_ecb_encrypt_decrypt(void);
bool test_hw_aes256_cbc_encrypt(void);
bool test_hw_aes256_cbc_encrypt_decrypt(void);

#define TEST_SUIT_CRYP_HW                                                                                              \
    {"hwAes256EcbEncrypt", test_hw_aes256_ecb_encrypt}, {"hwAes256CbcEncrypt", test_hw_aes256_cbc_encrypt},            \
        {"HwAes256EcbEncryptDecrypt", test_hw_aes256_ecb_encrypt_decrypt},                                             \
        {"HwAes256CbcEncryptDecrypt", test_hw_aes256_cbc_encrypt_decrypt},

#ifdef __cplusplus
}
#endif

#endif /* TEST_CRYP_HW_H */
