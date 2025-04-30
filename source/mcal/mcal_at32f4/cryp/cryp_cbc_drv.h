#ifndef CRYP_CBC_DRV_H
#define CRYP_CBC_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "artery_at32f4xx.h"
#include "cryp_const.h"

#ifndef HAS_CRYP
#error "+HAS_CRYP"
#endif

#ifndef HAS_CUSTOM
#error "+HAS_CUSTOM"
#endif

bool hw_aes256_cbc_decrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out);
bool hw_aes256_cbc_encrypt(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out);
bool hw_aes256_cbc_init(const uint8_t* key32byte, const uint8_t* init_vector, IvSkipCfg_t iv_skip_cfg) ;
uint32_t hw_aes256_cbc_decrypt_stream(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out);

#ifdef __cplusplus
}
#endif

#endif /* CRYP_CBC_DRV_H */
