
#ifndef TEST_AES256_H
#define TEST_AES256_H

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

#ifndef HAS_AES256
#error "It is needed HAS_AES256 option for that component"
#endif

bool test_encrypt_aes256_ecb(void);
bool test_decrypt_aes256_ecb(void);

#define TEST_SUIT_AES256                                                                                               \
    {"decrypt_aes256_ecb", test_decrypt_aes256_ecb}, {"encrypt_aes256_ecb", test_encrypt_aes256_ecb},

#ifdef __cplusplus
}
#endif

#endif /* TEST_AES256_H */
