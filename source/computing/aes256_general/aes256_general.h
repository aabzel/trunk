
#ifndef AES256_GEN_H
#define AES256_GEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "aes256_cbc_types.h"
#include "aes256_general_types.h"

bool aes256_ecb_decrypt(const uint8_t* key,
		uint8_t* data_in, uint32_t datalen,
		uint8_t* data_out,uint32_t* returnlen);

bool aes256_ecb_encrypt(const uint8_t* key,
		uint8_t* data_in, uint32_t datalen,
		uint8_t* data_out,uint32_t* returnlen);

bool aes256_cbc_encrypt(uint8_t* key, uint8_t* iv,
		uint8_t* data, uint32_t datalen,
		uint8_t* returndata, uint32_t* returnlen );

bool aes256_cbc_decrypt(uint8_t* key, uint8_t* iv,
		uint8_t* data, uint32_t datalen,
		uint8_t* returndata, uint32_t* returnlen);

bool aes256_cbc_decrypt_stream(AES_ctx* ctx, uint8_t* key,
        uint8_t* in_data, uint32_t datalen, uint8_t* out_data,
        uint32_t* returnlen);

#ifdef __cplusplus
}
#endif

#endif // AES256_GEN_H

