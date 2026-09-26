#include "clock_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

//#include "clock_diag.h"
#include "clock_custom_diag.h"
#include "convert.h"
#include "ctype.h"
#include "data_utils.h"
#include "log.h"
#include "str_utils.h"
#include "timer_utils.h"

bool clock_custom_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = clock1_diag();
    res = clock2_diag();
    return res;
}

bool clock_peripheral_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool clock_raw_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

/*
 */
bool clock_frequency_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool clock_diag_frequency_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}
