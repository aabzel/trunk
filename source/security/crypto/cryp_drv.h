#ifndef CRYP_DRV_H
#define CRYP_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "cryp_api.h"
#include "cryp_types.h"
#ifdef HAS_CRYP_HW
#include "cryp_custom_drv.h"
#endif

#ifndef HAS_CRYP
#error "+HAS_CRYP"
#endif

bool cryp_init(void);

bool aes256_cbc_init_api( const uint8_t * key, const uint8_t * init_vector,
		AlgImpl_t alg_impl, IvSkipCfg_t iv_skip_cfg);

bool aes256_ecb_encrypt_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out,
                            AlgImpl_t alg_impl);

bool aes256_ecb_decrypt_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out,
                            AlgImpl_t alg_impl);

bool aes256_cbc_encrypt_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out,
                            AlgImpl_t alg_impl);

uint32_t aes256_cbc_decrypt_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t datalen, uint8_t* data_out,
                                AlgImpl_t alg_impl);

uint32_t aes256_cbc_decrypt_stream_api(const uint8_t* key32byte, uint8_t* data_in, uint32_t data_len, uint8_t* data_out,
                                       AlgImpl_t alg_impl);

#ifdef __cplusplus
}
#endif

#endif /* CRYP_DRV_H */
