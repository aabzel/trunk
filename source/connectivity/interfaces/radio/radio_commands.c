#include "radio_commands.h"

#include <stdio.h>
#include <string.h>

#include "convert.h"
#include "cli_utils.h"
#include "log.h"
#include "radio_drv.h"

#ifdef HAS_SX1262
#include "sx1262_drv.h"
#endif

bool radio_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0==argc){
        cli_printf("overflow err cnt: %u"CRLF, LoRaInterface.ovfl_err_cnt);
        cli_printf("err cnt: %u"CRLF, LoRaInterface.err_cnt);
        cli_printf("tx ok cnt: %u"CRLF, LoRaInterface.tx_ok_cnt);
        cli_printf("tx done cnt: %u"CRLF, LoRaInterface.tx_done_cnt);
        cli_printf("max_distance: %f m"CRLF, LoRaInterface.max_distance);
        res = true;
    } else {
        LOG_INFO(LORA,"ld");
    }
    return res;
}

#ifdef HAS_DEBUG
#define EARTH_RADIUS_M 6371000.0
bool radio_horizon_command(int32_t argc, char* argv[]){
    bool res = false;
    double height = 0.0;
    double horizon = 0.0;
    uint8_t key='h';
    if(0<=argc) {
        res = try_str2double(argv[0], &height);
        res = try_str2double(argv[0], &horizon);
    }
    if(1<=argc){
        key = argv[1][0];
    }
    if(res){
        if('h'==key){
            horizon=sqrt(((EARTH_RADIUS_M+height)*(EARTH_RADIUS_M+height))-(EARTH_RADIUS_M*EARTH_RADIUS_M));
            cli_printf("horizon: %6.1f m"CRLF, horizon);
        }else if('l'==key){
            height = sqrt((horizon*horizon)+(EARTH_RADIUS_M*EARTH_RADIUS_M))-EARTH_RADIUS_M;
            cli_printf("height: %7.2f m"CRLF, height);
        }else{
            res = false;
        }
    }
    return res;
}
#endif
