#include "can_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "ostream.h"
#include "table_utils.h"
#include "can_mcal.h"
#include "can_types.h"
#include "writer_config.h"
#include "string_reader.h"

// us 8 byte
// us 8 hex_string
bool can_send_command(int32_t argc, char* argv[]) {
    bool res = false;
   	CanMessage_t Message = {0};
    uint8_t num = 0;
    size_t array_len = 0;

    if(1<=argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CAN, "ParseErr CanNum [1....8]");
        }
    }

    if(2<=argc) {
        res = try_str2uint32(argv[1], &Message.identifier.extended);
        if(false == res) {
            LOG_ERROR(CAN, "ParseErr ID [1....8]");
        }else{

        }
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], Message.data, sizeof(Message.data), &array_len);
        if(false == res) {
            LOG_WARNING(CAN, "ExtractHexArrayErr  [%s]", argv[2]);
            snprintf((char*)Message.data, sizeof(Message.data), "%s", argv[2]);
            array_len = strlen(argv[2]);
            res = true;
        }else{
        	LOG_WARNING(CAN, "SpotSize:%u Byte", array_len);
        }
    }

    if(res) {
    	Message.id_type = CAN_FRAME_ID_STANDARD;
    	Message.dlc = array_len;
    	res = can_api_transmit_data(  num, &Message);
        if(res) {
          	print_hex( Message.data,array_len);
        	LOG_INFO(CAN, "%u SendOk %u byte",num, array_len);
            cli_printf(CRLF);
        } else {
            LOG_ERROR(CAN, "%u SendErr",num);
        }
    }else {
        LOG_ERROR(CAN, "Usage: cs instance Id hex_string");
        LOG_INFO(CAN, "instance [1...%u]", CAN_COUNT);
        LOG_INFO(CAN, "hex_string 0x[0...F]+");
    }
    return res;
}

bool can_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1<= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CAN, "ParseErr CanNum [1....8]");
        }
    }
    if(res) {
    	res = can_init_one(num);
        if(res) {
        	LOG_INFO(CAN, "InitOk");
        }else{
            LOG_ERROR(CAN, "InitErr");
        }
    }else {
        LOG_ERROR(CAN, "Usage: ci instance ");
        LOG_INFO(CAN, "instance [1...%u]", CAN_COUNT);
        LOG_INFO(CAN, "bit_rate ");
    }
    return res;
}


bool can_bit_rate_command(int32_t argc, char* argv[]){
    bool res=false;
    uint32_t bit_rate=0;
    uint8_t num = 1;
    if(1<=argc){
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CAN, "ParseErr CanNum [1....N]");
        }
    }

    if(2<=argc){
        res = try_str2uint32(argv[1], &bit_rate);
        if(false == res) {
            LOG_ERROR(CAN, "Err extract bit_rate %s", argv[1]);
        }
    }

    if(res){
    	switch(argc){
    	case 1:{
    		res = can_api_baudrate_get(num, &bit_rate);
            if(res) {
                LOG_INFO(CAN,"BitRate:%u bit/s",bit_rate);
            }else {
            	 LOG_ERROR(CAN,"BitRateGetErr");
            }

    	} break;

    	case 2: {
        res = can_api_baudrate_set(num, bit_rate);
        if(res){
            LOG_INFO(CAN,"SetBaudRate:%u bit/s Ok",bit_rate);
        }

    	}break;
    	}
    }
    return res;
}

/*TODO: calculate */
bool can_diag_command(int32_t argc, char* argv[]) {
    bool res=false;

    res=can_diag();
    return res;
}





