#include "echo_effect_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "convert.h"
#include "echo_effect.h"
#include "log.h"

bool echo_effect_factor_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;
    double factor = 0.01;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(ECHO_EFFECT, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &factor);
        if(false == res) {
            LOG_ERROR(ECHO_EFFECT, "Arg1 factor %s", argv[1]);
        }
    }

    if(res) {
        switch(argc) {
            case 1: {
                res = echo_effect_factor_get(num,&factor);
                LOG_INFO(ECHO_EFFECT, "Get,Factor:%f",factor);
            }break;
            case 2: {
                LOG_INFO(ECHO_EFFECT, "Set,Factor:%f",factor);
                res = echo_effect_factor_set(num,factor);
            } break;
            default: break;
        } //switch

        if(res) {
            LOG_INFO(ECHO_EFFECT, "Ok");
        } else {
            LOG_ERROR(ECHO_EFFECT, "Err");
        }
    } else {
        LOG_ERROR(ECHO_EFFECT, "Usage: eef Num Factor");
    }
    return res;
}

//psd 1
bool echo_effect_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(ECHO_EFFECT, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(res) {
        res = echo_effect_diag(num);
        if(res) {
        } else {
            LOG_ERROR(ECHO_EFFECT, "GenerateErr");
        }
    } else {
        LOG_ERROR(ECHO_EFFECT, "Usage: eed Num");
    }
    return res;
}

