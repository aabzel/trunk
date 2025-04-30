#include "iec16022_commands.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

#include "debug_info.h"
#include "iec16022_drv.h"
#include "iec16022ecc200.h"
#include "convert.h"
#include "win_utils.h"
#include "log.h"

bool iec16022_encode_command(int32_t argc, char* argv[]){
	bool res = false;
    uint8_t array[256];
    char file_name[256];
    size_t size = 0;

    if(1 <= argc) {
        res = try_str2array(argv[0], array, sizeof(array), &size);
        if(false == res) {
            LOG_WARNING(IEC16022, "ExtractHexArrayErr  [%s]", argv[0]);
            snprintf((char*)array, sizeof(array), "%s", argv[0]);
            size = strlen(argv[0]);
            res = true;
        }else{
        }
    }

    if(2 <= argc) {
            snprintf((char*)file_name, sizeof(file_name), "%s", argv[1]);
            res = true;
    }else{
    	strcpy(file_name,"DataMatrix.gv");
    }

    if(res) {
    	res= iec16022_encode(   array,   size,file_name);
    }

	return res;
}

bool iec16022_init_command(int32_t argc, char* argv[]){
	bool res = false;
	return res;
}
