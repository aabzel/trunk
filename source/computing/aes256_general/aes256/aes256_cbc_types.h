#ifndef AES256_CBC_TYPES_H
#define AES256_CBC_TYPES_H

#include "aes256_cbc_const.h"

#ifndef HAS_AES256
#error "+HAS_AES256"
#endif

typedef struct {
	unsigned char RoundKey[AES_KEY_EXP_SIZE];
	unsigned char Iv[AES_BLOCKLEN];
}AES_ctx;


#endif /**/
