#include "mam_commands.h"

#include "convert.h"
#include "log.h"
#include "mam_mcal.h"

bool mam_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = mam_diag();
    } else {
        LOG_ERROR(MAM, "Usage: fdat");
    }

    return res;
}

bool mam_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = mam_mcal_init();
        if(false == res) {
            LOG_ERROR(MAM, "Init" LOG_ER);
        } else {
            LOG_INFO(MAM, "Init" LOG_OK);
        }
    }
    return res;
}
