#include "relay_commands.h"

#include <stdio.h>

#include "data_utils.h"
#include "relay.h"
#include "log.h"
#include "common_diag.h"
#include "convert.h"
#include "str_utils.h"
#include "relay_diag.h"


bool relay_blink_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    uint32_t time_out_ms = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RELAY, "ParseErr num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &time_out_ms);
        if(false == res) {
            LOG_ERROR(RELAY, "ParseErr Duration %s", argv[1]);
        }
    }

    if(res) {
        LOG_INFO(RELAY, "TrySetBlink Index:%u Time:%u",num,time_out_ms);
        res = relay_blink_set(num, time_out_ms);
        if(res) {
            LOG_INFO(RELAY, "Ok!");
        }
    }else {
        LOG_ERROR(RELAY, "Usage: rb Num DurationMs");
    }
    return res;
}

bool relay_get_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RELAY, "ParseErr num %s", argv[0]);
        }
    }

    if(res){
        bool on_off = false;
        on_off = relay_state_get(  num);
        LOG_INFO(RELAY, "Index:%u State:%s", num, OnOffToStr( on_off));
    }else {
        LOG_ERROR(RELAY, "Usage: rg Num");
    }
    return res;
}

bool relay_set_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    bool on_off = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RELAY, "ParseErr Num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(RELAY, "ParseErr OnOff %s", argv[1]);
        }
    }

    if(res) {
        res = relay_state_set(num, on_off);
        LOG_INFO(RELAY, "Ok!");
    } else {
        LOG_ERROR(RELAY, "Usage: rs Num OnOff");
    }
    return res;
}

bool relay_diag_command(int32_t argc, char* argv[]) {
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

    if(2 < argc) {
        LOG_ERROR(RELAY, "Usage: rd keyWord");
    }
    if(res) {
        res = relay_diag(keyWord1, keyWord2);
    }
    return res;
}

bool relay_init_command(int32_t argc, char* argv[]){
	bool res=false;
	res=relay_mcal_init( );
    return res;
}
