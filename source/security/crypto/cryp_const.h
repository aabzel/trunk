#ifndef CRYPTO_CONST_H
#define CRYPTO_CONST_H


#include "cryp_dep.h"

/* ECB- Electronic Code Book
 * CBC- Cipher Block Chaining
 * DES - Data Encryption Standard
 * AES - Advanced Encryption Standard
 * CTR - Counter mode
 * counter with cipher block chaining message authentication code
 */

typedef enum{
	CRYP_ALGO_AES=0,/**/
	CRYP_ALGO_AES_ECB=1,/*Electronic Code Book*/
	CRYP_ALGO_AES_CBC=2,/*Cipher Block Chaining*/
	CRYP_ALGO_DES_ECB=3,/*Electronic Code Book*/
	CRYP_ALGO_DES_CBC=4,/*Cipher Block Chaining*/
	CRYP_ALGO_AES_CTR=5,/*Cipher Block Chaining*/
	CRYP_ALGO_AES_CCM=6,/**/
	CRYP_ALGO_AES_GCM=7,/**/
	CRYP_ALGO_AES_GCM_GMAC=8,/**/
	CRYP_ALGO_TDES_ECB=9,/**/
	CRYP_ALGO_DES=10,/**/
	CRYP_ALGO_UNDEF=11,/**/
}CrypAlgorithm_t;

typedef enum{
	CRYP_KEY_128_BIT=128,
	CRYP_KEY_192_BIT=192,
	CRYP_KEY_256_BIT=256,
	CRYP_KEY_UNDEF=0,
}CrypKeySize_t;

typedef enum{
	ALG_IMPL_SW=0,
	ALG_IMPL_HW=1,
	ALG_IMPL_UNDEF=2,
}AlgImpl_t;

typedef enum {
	IV_SKIP_CFG_ONCE=0,
	IV_SKIP_CFG_ALWAYS=1,
	IV_SKIP_CFG_UNDEF=2,
}IvSkipCfg_t;

#endif /* CRYPTO_CONST_H */
