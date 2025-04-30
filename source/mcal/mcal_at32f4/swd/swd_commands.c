#include "swd_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <stddef.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "swd_drv.h"
#include "at32f435_437.h"
#include "table_utils.h"
#include "writer_config.h"

bool swd_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    LOG_INFO(SWD, "ITM_RxBuffer: %d", ITM_RxBuffer);
    return res;
}


bool swd_write_command(int32_t argc, char* argv[]) {
    bool res = false;
    static uint8_t tx_array[256];
    size_t array_len = 0;
    if(1 == argc) {
            res = try_str2array(argv[0], tx_array, sizeof(tx_array), ( size_t* )&array_len);
            if(false == res) {
            	strcpy((char *)tx_array,argv[0]);
            	array_len = strlen(argv[0]);
                LOG_WARNING(SWD, "Unable to extract bin TxArray [%s]=[%s]Len%u", argv[0],tx_array,array_len);
                res = true;
            }

    }

        if(res) {
            res = swd_write( tx_array, array_len);
            if(res) {
                LOG_INFO(SWD, "OK");
                cli_printf(CRLF);
            } else {
                LOG_ERROR(SWD, "Unable to send SWD");
            }

    } else {
        LOG_ERROR(SWD, "Usage: sw  hex_string");
        LOG_INFO(SWD, "instance");
        LOG_INFO(SWD, "hex_string 0x[0...F]+");
    }
    return res;
}

bool swd_read_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
        uint8_t array[256];
        memset(array, 0x0, sizeof(array));
        uint16_t array_len = 0;


        if(res) {
            res = try_str2uint16(argv[1], &array_len);
            if(false == res) {
                LOG_ERROR(SWD, "Unable to extract array %s", argv[1]);
            }
        }

        if(res) {
            res = swd_read( array, array_len);
            if(false == res) {
                LOG_ERROR(SWD, "Unable to read SWD");
            } else {
                print_mem(array, array_len, true, false, false, true);
                cli_printf(CRLF);
            }
        }
    } else {
        LOG_ERROR(SWD, "Usage: sr byte");
        LOG_INFO(SWD, "swd_num");
        LOG_INFO(SWD, "byte");
    }
    return res;
}

bool swd_init_command(int32_t argc, char* argv[]){
    bool res=swd_init();
    if(res){
        LOG_INFO(SWD, "Ok");
    }else{
        LOG_ERROR(SWD, "InitErr");
    }
    return res;
}
