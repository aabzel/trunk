#include "cortex_mpu_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "cortex_mpu_diag.h"
#include "cortex_mpu_mcal.h"
#include "log.h"
#include "time_mcal.h"

bool cortex_mpu_reg_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = mpu_raw_reg_diag();
    log_res(LG_MPU, res, "Regs");
    if(!res) {
        LOG_ERROR(LG_MPU, "Usage: mpug");
    }
    return res;
}

bool cortex_mpu_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = true;
    }

    if(res) {
#ifdef HAS_MPU_DIAG
        res = cortex_mpu_diag();
#endif
        log_res(LG_MPU, res, "Diag");
    } else {
        LOG_ERROR(LG_MPU, "Usage: cmpud");
    }
    return res;
}

bool cortex_mpu_init_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = cortex_mpu_mcal_init();
        log_res(LG_MPU, res, "Init");
    } else {
        LOG_ERROR(LG_MPU, "Usage: cmpui");
    }
    return res;
}

bool cortex_mpu_region_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = cortex_mpu_region();
        log_res(LG_MPU, res, "Regions");
    } else {
        LOG_ERROR(LG_MPU, "Usage: cmpur");
    }
    return res;
}
