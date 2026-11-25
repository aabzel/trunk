#include "flash_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "flash_mcal.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

bool flash_raw_reg_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = flash_raw_reg_diag();
    } else {
        LOG_ERROR(LG_FLASH, "Usage frrr");
    }

    return res;
}
