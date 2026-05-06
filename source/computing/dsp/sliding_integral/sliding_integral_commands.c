#include "sliding_integral_commands.h"

#include "convert.h"
#include "sliding_integral.h"
#include "log.h"

//sliding_integral_proc_file

/*
 sliding_integral_proc_file 8 directionNorm.csv 3 9
 * */



bool sliding_integral_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    int32_t value = 0.0;

    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        res = try_str2int32(argv[1], &value);
    }

    if(res) {
        int32_t out = 0.0;
        LOG_INFO(SLIDING_INTEGRAL, "Proc,In:%f", value);
        res = sliding_integral_proc_in_out(num, (int32_t)value, &out);
        log_res(SLIDING_INTEGRAL, res, "proc_in_out");
        if(res) {
            LOG_INFO(SLIDING_INTEGRAL, "Out:%f", out);
        } else {
            LOG_ERROR(SLIDING_INTEGRAL, "Out:%f", out);
        }
    } else {
        LOG_ERROR(SLIDING_INTEGRAL, "Usage: fis Num M FcHz");
    }

    return res;
}

bool sliding_integral_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);

    if(res) {
        res = sliding_integral_init_one(num);
        log_res(SLIDING_INTEGRAL, res, "init_one");
    } else {
        LOG_ERROR(SLIDING_INTEGRAL, "Usage: fis Num M FcHz");
    }

    return res;
}

bool sliding_integral_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {

        res = sliding_integral_reset_one(num);
        log_res(SLIDING_INTEGRAL, res, "reset_one");
    }

    return res;
}


bool sliding_integral_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
#ifdef HAS_SLIDING_INTEGRAL_DIAG
        res = sliding_integral_diag(num);
        res = sliding_integral_diag_mem(num);
#endif
        log_res(SLIDING_INTEGRAL, res, "diag");
    } else {
        LOG_ERROR(SLIDING_INTEGRAL, "Usage: fis Num M FcHz");
    }
    return res;
}

