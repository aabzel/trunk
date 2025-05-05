#include "auto_version_commands.h"

#include "auto_version.h"
#include "auto_version_diag.h"
#include "convert.h"
#include "log.h"

bool cmd_auto_version_diag(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res){
        res = auto_version_diag();
    } else {
        LOG_ERROR(AUTO_VERSION, "Usage: avd");
    }
    return res;
}

bool cmd_auto_version_proc(int32_t argc, char* argv[]) {
    bool res = false;

    if(1 <= argc) {
        res = true;
    }

    if(res){
        res = auto_version_proc_headr(argv[0]);
    }else {
        LOG_ERROR(AUTO_VERSION, "Usage: avp");
    }
    return res;
}


