#include "dac_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "dac_mcal.h"
#include "writer_config.h"

bool dac_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = dac_diag();
    return res;
}

bool dac_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }
    if (res) {
        res = dac_init_one(num);
    }
    return res;
}
