#include "distance_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "convert.h"
#include "distance_diag.h"
#include "distance_drv.h"
#include "log.h"

bool distance_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;

    if(0<=argc) {
    	num = 1;
        res = true;
    }

    if(1<=argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = distance_diag( num);
        if(res){
            LOG_INFO(DISTANCE,"Ok");
        }else{
            LOG_ERROR(DISTANCE,"err");
        }
    } else {
        LOG_ERROR(DISTANCE,"Usage: dd num");
    }
    return res;
}

bool distance_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0<=argc) {
    	num = 1;
        res = true;
    }

    if(1<=argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = distance_init_one(num);
        if(res){
            LOG_INFO(DISTANCE,"Ok");
        }else{
            LOG_ERROR(DISTANCE,"err");
        }
    }else {
        LOG_ERROR(DISTANCE,"Usage: di num");
    }
    return res;
}
