#include "math_commands.h"

#include <stdio.h>
#include <string.h>

#include "convert.h"
#include "log.h"
#include "utils_math.h"
#include "vector_diag.h"

bool math_vector_angle_command(int32_t argc, char* argv[]) {
    bool res = false;

    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(MATH, "Usage: mva keyWord");
    }

    if(res) {
#ifdef HAS_MATH_VECTOR
        res = math_vector_angle_diag(keyWord1, keyWord2);
#endif
    }
    return res;
}

bool math_sum4_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t sum = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &sum);
        log_res(MATH, res, "sum");
    }

    if(res) {
        res = math_sum4(sum);
    }
    return res;
}

bool math_sum3_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t sum = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &sum);
        log_res(MATH, res, "sum");
    }

    if(res) {
        res = math_sum3(sum);
    }
    return res;
}

bool math_sum4_d_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t sum = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &sum);
        log_res(MATH, res, "sum");
    }

    if(res) {
        res = math_sum4_dynamic(sum);
    }
    return res;
}
