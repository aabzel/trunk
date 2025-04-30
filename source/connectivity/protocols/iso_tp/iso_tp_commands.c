
#include "iso_tp_commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "convert.h"
#include "log.h"
#include "iso_tp_diag.h"
#include "iso_tp.h"
#include "writer_generic.h"

bool iso_tp_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t interface = IF_UNDEF;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &interface);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr if %s", argv[0]);
        }
    }

    if(2 < argc) {
        LOG_ERROR(ISO_TP, "Usage: tbfpd if");
    }
    if(res) {
        res = false;
        res = iso_tp_diag();
    }
    return res;
}

/*
 * iso_tp_send 1 0x1122334455667788991122334455
 */
bool iso_tp_send_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    uint8_t data[256]={0};
    size_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(ISO_TP, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        LOG_INFO(ISO_TP, "TrySend Num:%u,Size:%u",num, size);
        res = iso_tp_send(num, data, size);
        if(res) {
            LOG_INFO(ISO_TP, "SendOk");
        }else {
            LOG_ERROR(ISO_TP, "SendErr");
        }
    }else{
        LOG_ERROR(ISO_TP, "iso_tp Num Data");
    }


    return res;
}

bool iso_tp_buff_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    uint32_t size = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &size);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr size %s", argv[1]);
        }
    }

    if(res) {
    	res=iso_tp_buff_print(  num ,  size,ISO_TP_BUFF_RX);
    	res=iso_tp_buff_print(  num ,  size,ISO_TP_BUFF_TX);
    }
    return res;
}
