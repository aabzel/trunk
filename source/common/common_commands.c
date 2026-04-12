#include "common_commands.h"

#include "common_diag.h"
#include "common_functions.h"
#include "convert.h"
#include "log.h"

bool common_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = common_diag();
    } else {
        LOG_ERROR(SYS, "Usage: comd");
    }

    return res;
}
