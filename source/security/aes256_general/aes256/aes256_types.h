
#ifndef AES256_V2_TYPES_H
#define AES256_V2_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "aes256_const.h"
typedef struct  {
	uint8_t raw[32];
} aes256_key_t;

typedef struct  {
	uint8_t raw[16];
} aes256_blk_t;

typedef struct {
    aes256_key_t key;
    aes256_key_t enckey;
    aes256_key_t deckey;
} aes256_context_t;

#define AES_CORE_FN_ static void __attribute__((nonnull))
#define GFC_FN_ static uint8_t __attribute__((const))

#ifdef __cplusplus
}
#endif

#endif /* AES256_V2_TYPES_H */

