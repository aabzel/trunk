#include "rng_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "log.h"
#include "rng_drv.h"

bool trng_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
        uint32_t rand_val = 0;
        res = rng_read(&rand_val);
        if(res) {
            LOG_INFO(RNG, "rand_val %u", rand_val);
        }
    } else {
        LOG_ERROR(RNG, "Usage: rng");
    }
    return res;
}
