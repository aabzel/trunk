#ifndef SALSA20_TYPES_H
#define SALSA20_TYPES_H

typedef enum   { 
KEYLEN_128, 
KEYLEN_256 
}key_len_t;

/**
 * Return codes for s20_crypt
 */
typedef enum {
  S20_SUCCESS,
  S20_FAILURE
}s20_status_t;

/**
 * Key size
 * Salsa20 only permits a 128-bit key or a 256-bit key, so these are
 * the only two options made available by this library.
 */
enum s20_keylen_t
{
  S20_KEYLEN_256,
  S20_KEYLEN_128
};

#endif /*SALSA20_TYPES_H*/
