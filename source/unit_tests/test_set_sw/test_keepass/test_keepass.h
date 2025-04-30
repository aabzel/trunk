#ifndef TEST_KEEPASS_UTILS_H
#define TEST_KEEPASS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#ifdef HAS_CRYP_HW
bool test_keepass_decrypt_hw(void);
#define TEST_SUIT_KEEPASS_HW                          \
    {"KeePassDecryptHw", test_keepass_decrypt_hw},
#else
#define TEST_SUIT_KEEPASS_HW
#endif

bool test_keepass_decrypt_sw(void);
bool test_keepass_test_pass_word(void);
bool test_keepass_idiot_proof(void);
bool test_keepass_types(void);

#define TEST_SUIT_KEEPASS   TEST_SUIT_KEEPASS_HW             \
    {"keepass_test_pass_word", test_keepass_test_pass_word},              \
    {"keepass_idiot_proof", test_keepass_idiot_proof},              \
    {"KeePassTypes", test_keepass_types},              \
    {"KeePassDecryptSw", test_keepass_decrypt_sw},

#ifdef __cplusplus
}
#endif

#endif /* TEST_KEEPASS_UTILS_H */
