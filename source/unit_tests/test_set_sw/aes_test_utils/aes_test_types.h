
#ifndef AES_TEST_CASE_TYPES_H
#define AES_TEST_CASE_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "aes_test_const.h"

#ifndef HAS_AES
#error "+HAS_AES"
#endif

typedef struct {
    uint8_t PlainText[16];
    uint8_t Key256bit[BLOCK_SIZE];
    uint8_t CipherText[16];
} AES256TestCase_t;

typedef struct {
    uint8_t PlainText[16];
    uint8_t Key256bit[BLOCK_SIZE];
    uint8_t InitVector[16];
    uint8_t CipherText[16];
} AES256CbcTestCase_t;

typedef struct {
    uint8_t PlainText[64];
    uint8_t Key256bit[32];
    uint8_t InitVector[16];
    uint8_t CipherText[64];
} AES256CbcTestCase64_t;

#ifdef __cplusplus
}
#endif

#endif /* AES_TEST_CASE_TYPES_H */
