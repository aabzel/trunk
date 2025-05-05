#include "dashboard_commands.h"

#include "log.h"
#include "dashboard_diag.h"

bool dashboard_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = dashboard_diag();
    }
    return res;
}


