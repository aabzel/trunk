#ifndef RNG_DRV_H
#define RNG_DRV_H

#include <stdbool.h>
#include <stdint.h>


typedef enum BOARD_TRNGName {
    BOARD_TRNG0 = 0,
    BOARD_TRNG1 = 1,

    BOARD_TRNGCOUNT
} BOARD_TRNGName;

bool rng_init(void);
bool rng_read(uint32_t* out_val);
uint32_t generate_rand_uint32(void);

#endif /* RNG_DRV_H  */
