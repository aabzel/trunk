#include "rv32imc_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "array.h"
#include "convert.h"
#include "core_diag.h"
#include "data_utils.h"
#include "debug_info.h"
#include "flash_config.h"
#include "rv32imc_driver.h"
#ifdef HAS_CMSIS
#include "cmsis_gcc.h"
#endif
#include "log.h"
#include "microcontroller_const.h"
#include "str_utils.h"
#include "table_utils.h"

/*
 * rv32b 0x80000000
 * */
bool rv32imc_boot_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t app_start_address = 0;
    if(0 <= argc) {
        app_start_address = EXT_ROM_START;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &app_start_address);
        log_res(CORE, res, "StartAddr");
    }

    if(res) {
        res = rv32imc_boot_addr(app_start_address);
        log_res(CORE, res, "Boot");
    } else {
        LOG_ERROR(SYS, "Usage: rv32b");
    }
    return res;
}

bool rv32imc_reboot_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = rv32imc_reboot();
#ifdef HAS_RV32IMC_DIAG
#endif
    } else {
        LOG_ERROR(SYS, "Usage: rv32r");
    }
    return res;
}

bool rv32imc_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = rv32imc_diag();
    } else {
        LOG_ERROR(SYS, "Usage: rv32d");
    }
    return res;
}
