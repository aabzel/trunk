#include "decawave_commands.h"

#include "log.h"
#include "decawave_diag.h"
#include "decawave.h"
#include "convert.h"


bool decawave_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = decawave_init();
    } else {
        LOG_ERROR(DECAWAVE, "Usage: decawavei");
    }
    return res;
}

bool decawave_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = decawave_diag_distanse(1) ;
    } else {
        LOG_ERROR(DECAWAVE, "Usage: decawaved");
    }
    return res;
}

bool decawave_protocol_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = decawave_protocol_diag(1);
    }else {
        LOG_ERROR(DECAWAVE, "Usage: dpd");
    }
    return res;
}


bool decawave_diag_flow_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = decawave_diag_flow(1);
    }else {
        LOG_ERROR(DECAWAVE, "Usage: dpd");
    }
    return res;
}

