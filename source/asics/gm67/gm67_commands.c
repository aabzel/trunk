#include "gm67_commands.h"

#include <limits.h>
#include <stdio.h>

#include "gm67_drv.h"
#include "convert.h"
#include "debug_info.h"
#include "log.h"

bool gm67_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = gm67_diag();
    }
    return res;
}

bool gm67_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(GM67, "ParseErr num  %s", argv[0]);
        }
    }

    if(res) {
        res = gm67_init_one(num);
    }
    return res;
}

