#include "can_registers_commands.h"

#include <stdio.h>

#include "array_diag.h"
#include "can_custom.h"
#include "can_mcal.h"
#include "convert.h"
#include "log.h"

bool can_diag_low_level_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    char keyword[80] = {0};
    if(0 <= argc) {
        res = true;
        num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(2 <= argc) {
        strcpy(keyword, argv[1]);
    }

    if(res) {
        res = can_diag_low_level(num, keyword);
        log_res(CAN, res, "DiagLowLevel");
    } else {
        LOG_ERROR(CAN, "Usage candl Num");
    }

    return res;
}

bool can_raw_reg_command(int32_t argc, char* argv[]) {
    uint8_t num = 1;
    bool res = false;

    if(0 <= argc) {
        res = true;
        num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(CAN, res, "Num");
    }

    if(res) {
        res = can_raw_reg_diag(num);
        log_res(CAN, res, "RawReg");
    } else {
        LOG_ERROR(CAN, "Usage canrr Num");
    }

    return res;
}
