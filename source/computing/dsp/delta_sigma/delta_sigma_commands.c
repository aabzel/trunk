#include "delta_sigma_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "convert.h"
#include "delta_sigma.h"
#include "log.h"

bool delta_sigma_target_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;
    double target = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DELTA_SIGMA, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &target);
        if(false == res) {
            LOG_ERROR(DELTA_SIGMA, "Arg2 target %s", argv[1]);
        }
    }


    if(res) {
    	DeltaSigmaHandle_t* Node=DeltaSigmaGetNode(num);
    	if(Node) {
    		Node->target =  (ds_value_t) (target*1000.0);
    		LOG_INFO(DELTA_SIGMA, "Target:%f V", target);
    	}

    } else {
        LOG_ERROR(DELTA_SIGMA, "Usage: dst Num Target");
    }
    return res;
}

//psd 1
bool delta_sigma_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(DELTA_SIGMA, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(res) {
        res = delta_sigma_diag(num);
        if(res) {
        } else {
            LOG_ERROR(DELTA_SIGMA, "GenerateErr");
        }
    } else {
        LOG_ERROR(DELTA_SIGMA, "Usage: dsd Num");
    }
    return res;
}

