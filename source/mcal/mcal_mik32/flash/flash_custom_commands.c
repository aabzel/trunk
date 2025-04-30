#include "flash_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"

#include "data_utils.h"
#include "debug_info.h"
#include "flash_config.h"
#include "flash_custom_diag.h"
#include "flash_custom_types.h"
#include "flash_diag.h"
#include "flash_mcal.h"
#include "log.h"
#include "str_utils.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

bool flash_external_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = flash_external_diag();
    return res;
}

bool flash_custum_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = flash_custum_diag();
    return res;
}
