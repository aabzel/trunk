#include "ext_int_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "ext_int_mcal.h"
#include "log.h"

bool ext_int_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = ext_int_diag();

    return res;
}

bool ext_int_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(EXT_INT, "ParseErr EXT_INTNum [0~%u]", EXT_INT_COUNT);
        }
    }
    if(res) {
        res = ext_int_init_one(num);
    }
    return res;
}
