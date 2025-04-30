
#ifndef __CRYPTO_SHA256_H
#define __CRYPTO_SHA256_H

#include <stdint.h>
#include <stdlib.h>

#ifndef HAS_SHA256
#error "+HAS_SHA256"
#endif


typedef struct  {
  uint32_t state[8];
  uint64_t count;
  unsigned char buffer[64];
} sha256_t;

void sha256_hash(unsigned char *buf, const unsigned char *data, size_t size);

#endif
