#include "tpa2013d1_commands.h"

#include "convert.h"
#include "log.h"
#include "tpa2013d1_diag.h"
#include "tpa2013d1_drv.h"
#include "tpa2013d1_types.h"

bool tpa2013d1_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = tpa2013d1_diag();
    return res;
}


bool tpa2013d1_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = tpa2013d1_init();
    return res;
}


