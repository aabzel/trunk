
#ifndef AES256_COMPONENT_H
#define AES256_COMPONENT_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "aes256_types.h"

/// @function aes256_init
/// @brief Initialize a context structure.
/// @param[in,out] ctx Pointer to a pre-allocated context structure.
/// @param[in] key Pointer to a key initialized buffer.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256_init(
    aes256_context_t *ctx,
    aes256_key_t *key
);

/// @brief Clear the context structure.
/// @param[in,out] ctx Pointer to a context structure.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256_done(
    aes256_context_t *ctx
);

/// @brief Encrypt a single data block in place.
/// @param[in] ctx Pointer to an initialized context structure.
/// @param[in,out] buf Plaintext in, ciphertext out.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256_encrypt_ecb(
    aes256_context_t *ctx,
    aes256_blk_t *buf
);

/// @brief Decrypt a single data block in place.
/// @param[in] ctx Pointer to an initialized context structure.
/// @param[in,out] buf Ciphertext in, plaintext out.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256_decrypt_ecb(
    aes256_context_t *ctx,
    aes256_blk_t *buf
);



#ifdef __cplusplus
}
#endif

#endif // AES256_COMPONENT_H

