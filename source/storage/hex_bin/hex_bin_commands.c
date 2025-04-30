#include "hex_bin_commands.h"

#include "convert.h"
#include "hex_bin.h"
#include "log.h"



bool hex_to_bin_command(int32_t argc, char* argv[]) {
    bool res = false;
    char file_name[100] = "";
    if(0 == argc) {
    	res = false;
    }

    if(1 <= argc) {
        LOG_INFO(HEX_BIN, "argv0 [%s]", argv[0]);
        strcpy(file_name, argv[0]);
        LOG_INFO(HEX_BIN, "FileName [%s]", file_name);
        res = true;
    }

    if(res) {
    	res= hex_to_bin( file_name);
        if( res) {
            LOG_INFO(HEX_BIN, "hex>binOk");
        } else {
            LOG_ERROR(HEX_BIN, "hex>binErr");
        }
    }
    return res;
}

bool bin_to_hex_command(int32_t argc, char* argv[]) {
    bool res = false;
    char file_name[100] = "";
    if(0 == argc) {
    	res = false;
    }

    if(1 <= argc) {
        LOG_INFO(HEX_BIN, "argv0 [%s]", argv[0]);
        strcpy(file_name, argv[0]);
        LOG_INFO(HEX_BIN, "FileName [%s]", file_name);
        res = true;
    }

    if(res) {
        res = bin_to_hex(file_name);
        if( res) {
            LOG_INFO(HEX_BIN, "bin>hexOk");
        } else {
            LOG_ERROR(HEX_BIN, "bin>hexErr");
        }
    }
    return res;
}

