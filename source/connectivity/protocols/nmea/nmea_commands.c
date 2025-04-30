#include "nmea_commands.h"

#include <stdio.h>

#include "std_includes.h"
#include "convert.h"
#include "log.h"
#include "nmea_diag.h"


bool nmea_stat_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc){
        res = true;
        num = 1;
    }

    if(1 <= argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(NMEA, "UnableToParseNum");
        }
    }

    if(0 == argc) {
        res = nmea_diag(num);
        res=log_res(NMEA, res, "Diag");
    } else {
        LOG_ERROR(NMEA, "Usage: nmd Num");
    }
    return res;
}

bool nmea_data_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc){
        res = true;
        num = 1;
    }

    if(1 <= argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(NMEA, "UnableToParseNum");
        }
    }

    if(res) {
        res = nmea_data(num);
        res = log_res(NMEA, res, "Data");
    } else {
        LOG_ERROR(NMEA, "Usage: nmd Num");
    }
    return res;
}

bool nmea_messages_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc){
        res = true;
        num = 1;
    }

    if(1 <= argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(NMEA, "UnableToParseNum");
        }
    }

    if(0 == argc) {
        res = nmea_messages(num);
        res =log_res(NMEA, res, "Messages");
    } else {
        LOG_ERROR(NMEA, "Usage: nmm Num");
    }
    return res;
}


bool nmea_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc){
        res = true;
        num = 1;
    }

    if(1 <= argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(NMEA, "UnableToParseNum");
        }
    }

    if(res) {
        res = nmea_diag(num);
        res = log_res(NMEA, res, "Diag");
    }else {
        LOG_ERROR(NMEA, "Usage: nmg Num");
    }
    return res;
}
