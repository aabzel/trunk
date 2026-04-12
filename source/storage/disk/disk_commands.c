#include "disk_commands.h"

#include "convert.h"
#include "disk.h"
#include "log.h"

bool disk_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = disk_diag();
    } else {
        LOG_ERROR(DISK, "Usage: fdat");
    }

    return res;
}

bool disk_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = disk_mcal_init();
        if(false == res) {
            LOG_ERROR(DISK, "Init" LOG_ER);
        } else {
            LOG_INFO(DISK, "Init" LOG_OK);
        }
    }
    return res;
}
