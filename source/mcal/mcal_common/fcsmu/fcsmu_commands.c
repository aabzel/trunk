#include "fcsmu_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "fcsmu_mcal.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

bool fcsmu_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = fcsmu_diag();
    log_res(LG_FCSMU, res, "Diag");
    return res;
}

bool fcsmu_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t snum = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &snum);
        log_res(LG_FCSMU, res, "Num");
    }
    if(res) {
        res = fcsmu_init_one(snum);
    } else {
        LOG_ERROR(LG_FCSMU, "Usage: mci Num");
    }
    return res;
}
