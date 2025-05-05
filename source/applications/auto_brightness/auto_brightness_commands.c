#include "auto_brightness_commands.h"

#include "log.h"
#include "auto_brightness_diag.h"
#include "auto_brightness.h"

bool auto_brightness_diag_command(int32_t argc, char *argv[]) {
    bool res = false;
    if (0 == argc) {
        res = true;
    }

    if (res) {
        res = auto_brightness_diag();
        if(res){
            LOG_INFO(DISTANCE,"Ok");
        }else{
            LOG_ERROR(DISTANCE,"err");
        }
    }else{
    	LOG_ERROR(SYS,"Usage: abd");
    }
    return res;
}



