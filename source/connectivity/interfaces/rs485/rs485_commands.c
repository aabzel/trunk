#include "rs485_commands.h"

#include <stdio.h>
#include <string.h>

#include "rs485_mcal.h"
#include "convert.h"
#include "log.h"

bool rs485_scan_command(int32_t argc, char* argv[]){
	bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RS485, "ParseErr Num [1....8]");
        }
    }
#ifdef HAS_RS485_SCAN
	res=rs485_scan_one(num);
#endif
	return res;
}

bool rs485_init_command(int32_t argc, char* argv[]){
	bool res = false;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RS485, "ParseErr Num [1....8]");
        }
    }

	res = rs485_init_one(num);
	return res;
}

bool rs485_diag_command(int32_t argc, char* argv[]){
	bool res = false;
	res = rs485_diag();
	return res;
}

bool rs485_send_command(int32_t argc, char* argv[]){
	bool res = false;
    uint8_t array[256]={0};
    size_t array_len = 0;

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(RS485, "ParseErr Num [1....8]");
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], array, sizeof(array), &array_len);
        if(false == res) {
            LOG_WARNING(RS485, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)array, sizeof(array), "%s", argv[1]);
            array_len = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = rs485_send(  num,  array,   array_len);
        if(false == res) {
            LOG_ERROR(RS485, "%u SendErr", num);
        } else {
            cli_printf(CRLF);
        }
    } else {
        LOG_ERROR(RS485, "Usage: rss instance hex_string");
        LOG_INFO(RS485, "hex_string 0x[0...F]+");
    }
	return res;
}
