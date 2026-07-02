#include "rng_drv.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


#include "debug_info.h"

bool rng_init(void) {
    bool res = false;
    return res;
}

bool rng_read(uint32_t* out_val) {
    bool res = false;
    return res;
}

uint32_t generate_rand_uint32(void) {
    uint32_t val = 0;
    rng_read(&val);
    return val;
}
