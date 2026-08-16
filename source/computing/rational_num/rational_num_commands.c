#include "rational_num_commands.h"

#include <stdio.h>
#include <string.h>

#include "convert.h"
#include "log.h"
#include "rational_num.h"

bool float_to_rational_number_command(int32_t argc, char* argv[]) {
    bool res = false;
    float real = 0.0f;

    int32_t numerator = 0;
    int32_t denominator = 0;

    if(1 <= argc) {
        res = try_str2float(argv[0], &real);
        log_info_res(RATIONAL_NUM, res, "Float");
    }

    if(res) {
        res = float_to_rational_number(real, &numerator, &denominator);
        LOG_INFO(RATIONAL_NUM, "Real:%f=%u/%u", real, numerator, denominator);
    } else {
        LOG_ERROR(RATIONAL_NUM, "Usage: frn RealVal");
    }

    return res;
}
