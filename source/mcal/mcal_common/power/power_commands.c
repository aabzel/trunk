#include "power_commands.h"

#include "power_mcal.h"
#include "convert.h"
#include "debug_info.h"
#include "log.h"


bool power_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = power_mcal_init();
          log_res(POWER,  res, "Init");
    } else {
        LOG_ERROR(POWER, "Usage: pdi");
    }
    return res;
}

bool power_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = power_diag();
        log_res(POWER,  res, "Diag");
    } else {
        LOG_ERROR(POWER, "Usage: pdd");
    }
    return res;
}


