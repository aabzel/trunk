#include "calculator_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "convert.h"
#include "calculator_diag.h"
#include "calculator.h"
#include "log.h"

bool calculator_calc_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
    }

    if(res) {
        double  result = 0.0;
        res = calculator_calc(argv[0], &result);
        if (res) {
            LOG_INFO(CALC, "CalcResult: %f", result);
        }
    } else {
        LOG_ERROR(CALC, "Usage: calc formula");
    }
    return res;
}

