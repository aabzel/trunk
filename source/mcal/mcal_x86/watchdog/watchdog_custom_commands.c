#include "watchdog_custom_commands.h"

#include "convert.h"
#include "log.h"
#include "watchdog_diag.h"

bool wdt_diag_reg_command(int32_t argc, char* argv[]) {
    bool res = false;

    res = wdt_diag_reg();
    return res;
}
