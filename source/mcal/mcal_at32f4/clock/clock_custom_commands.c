#include "clock_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

//#include "clock_diag.h"
#include "clock.h"
#include "clock_custom_diag.h"
#include "convert.h"
#include "ctype.h"
#include "data_utils.h"
#include "log.h"
#include "str_utils.h"
#include "timer_utils.h"

bool clock_custom_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = clock_custom_diag();
    } else {
        LOG_ERROR(SYS, "Usage: clsd keyWord");
    }
    return res;
}
