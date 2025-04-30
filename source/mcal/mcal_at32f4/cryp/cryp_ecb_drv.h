#ifndef CRYP_ECB_DRV_H
#define CRYP_ECB_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "artery_at32f4xx.h"

#ifndef HAS_CRYP
#error "+HAS_CRYP"
#endif

#ifndef HAS_CUSTOM
#error "+HAS_CUSTOM"
#endif

bool hw_aes256_ecb_init(const uint8_t* const key32byte);

bool hw_aes256_ecb_encrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out);

bool hw_aes256_ecb_decrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out);

#ifdef __cplusplus
}
#endif

#endif /* CRYP_ECB_DRV_H */
