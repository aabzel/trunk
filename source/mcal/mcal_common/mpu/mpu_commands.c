#include "mpu_commands.h"

#include "convert.h"
#include "log.h"
#include "mpu_mcal.h"

bool mpu_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool mpu_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = mpu_diag();
    } else {
        LOG_ERROR(LG_MPU, "Usage: fdat");
    }

    return res;
}

bool mpu_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = mpu_mcal_init();
        if(false == res) {
            LOG_ERROR(LG_MPU, "Init" LOG_ER);
        } else {
            LOG_INFO(LG_MPU, "Init" LOG_OK);
        }
    }
    return res;
}
