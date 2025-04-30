#include "cross_detect_commands.h"

#include <stdio.h>

#include "convert.h"
#include "gpio_drv.h"
#include "gpio_diag.h"
#include "cross_detect_diag.h"
#include "cross_detect_drv.h"
#include "log.h"
#include "time_mcal.h"

bool cross_detect_diag_command(int32_t argc, char* argv[]) {
    bool res = true;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }


    if(res) {
        res = cross_detect_diag();
    }

    return res;
}

bool cross_detect_pin_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(res) {
        res = cross_detect_pin_diag(keyWord1,keyWord2);
    }

    return res;
}


bool cross_detect_init_command(int32_t argc, char* argv[]) {
    bool res = true;
    uint8_t num = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = cross_detect_init_one(num);
        if(res) {
            LOG_INFO(CROSS_DETECT, "InitOk");
        } else {
            LOG_ERROR(CROSS_DETECT, "InitErr");
        }
    }
    return res;
}

bool cross_detect_period_command(int32_t argc, char* argv[]){
    bool res = true;
    uint32_t period_ms = 0;
    if( 0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &period_ms);
    }

    if(res) {
        switch(argc) {
            case 0:
                LOG_INFO(CROSS_DETECT, "GetPeriod %f ms", USEC_2_MSEC(cross_detect_period_us));
                break;
            case 1:
                LOG_INFO(CROSS_DETECT, "SetPeriod %u ms",period_ms);
                cross_detect_period_us = MSEC_2_USEC(period_ms);
                break;
        }
    } else {
    	LOG_ERROR(CROSS_DETECT,"Usage: cpe period");
    }
    return res;
}

bool cross_detect_enable_command(int32_t argc, char* argv[]){
    bool res = true;
    uint8_t num = 0;
    bool on_off = true;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }
    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
    }

    if(res){
        res= cross_detect_enable(  num,   on_off);
    }
    return res;
}

bool cross_detect_diag_lut_command(int32_t argc, char* argv[]){
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(res){
        res= cross_detect_diag_lut(  keyWord1,keyWord2);
    }
    return res;
}
