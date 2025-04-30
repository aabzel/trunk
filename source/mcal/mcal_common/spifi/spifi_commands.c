#include "spifi_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "spifi_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

bool spifi_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = spifi_diag();
    return res;
}


bool spifi_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }
    if(res) {
        res = spifi_init_one(num);
    }
    return res;
}
