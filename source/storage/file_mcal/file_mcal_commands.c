#include "file_mcal_commands.h"

#include "convert.h"
#include "file_mcal.h"
#include "log.h"

bool file_mcal_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(FILE_MCAL, res, "Num");
    }

    if(res) {
        res = file_mcal_diag_one(num);
        log_info_res(FILE_MCAL, res, "Diag");

        res = file_mcal_diag();
        log_info_res(FILE_MCAL, res, "Diag");
    } else {
        LOG_ERROR(FILE_MCAL, "Usage: fdat");
    }

    return res;
}

bool file_mcal_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(FILE_MCAL, res, "Num");
    }

    if(0 == argc) {
        res = file_mcal_mcal_init();
        log_info_res(FILE_MCAL, res, "Init");
    }
    return res;
}

bool rename_file_command(int32_t argc, char* argv[]) {
    bool res = false;
    // res = file_rename();
    return res;
}
