#include "mpu_custom_commands.h"

#include "convert.h"
#include "log.h"
#include "mpu_custom_diag.h"

bool mpu_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 2;
    char keyword[80] = {0};
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(LG_MPU, res, "Num");
    }

    if(2 <= argc) {
        strcpy(keyword, argv[1]);
    }

    if(res) {
        res = mpu_diag_low_level(num, keyword);
        log_res(LG_MPU, res, "DiagLowLevel");
    } else {
        LOG_ERROR(LG_MPU, "Usage mpudl Num");
    }

    return res;
}
