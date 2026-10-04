#include "light_navigator_commands.h"

#include "convert.h"
#include "light_navigator.h"
#include "light_navigator_diag.h"
#include "log.h"

bool cmd_light_navigator_diag(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;

    } else {
        LOG_ERROR(LIGHT_NAVIGATOR, "Usage: lnd");
    }

    res = light_navigator_diag();
    return res;
}

bool light_navigator_coordinate_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    } else {
        LOG_ERROR(LIGHT_NAVIGATOR, "Usage: lnc");
    }

    res = light_navigator_coordinate();
    return res;
}
