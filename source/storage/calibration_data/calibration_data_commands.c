#include "calibration_data_commands.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "convert.h"
#include "crc8_autosar.h"
#include "calibration_data.h"
#ifdef HAS_CALIBRATION_DATA_DIAG
#include "calibration_data_diag.h"
#endif
#include "log.h"


bool cmd_calibration_data_get(int32_t argc, char* argv[]) {
    bool res = false;
    res = calibration_data_diag();
    return res;
}

/*cds 2*/
bool cmd_calibration_data_set(int32_t argc, char* argv[]) {
    bool res = false;

    uint16_t decawave_addr = 0;
    double uwb_offset = 0;
    if(1 <= argc) {
        res = true;
        res = try_str2uint16(argv[0], &decawave_addr);
        if(false == res) {
            LOG_ERROR(CALIBRATION_DATA, "Unable to extract decawave_addr %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = true;
        res = try_str2double(argv[1], &uwb_offset);
        if(false == res) {
            LOG_ERROR(CALIBRATION_DATA, "Unable to extract uwb_offset %s", argv[1]);
        }
    }

    if(res){
    	CalibrationData_t Data = {0};
        memset(Data.buff, 0, sizeof(CalibrationData_t));
    	res= calibration_data_get(Data.buff);
    	switch(argc){
    	case 1:{
    		Data.version = CALIB_DATA_VER1;
    		Data.decawave_address = decawave_addr;
    	} break;
    	case 2:{
    		Data.version = CALIB_DATA_VER1;
    		Data.decawave_address = decawave_addr;
    		Data.uwb_offset = uwb_offset;
    	} break;
    	default: break;
    	}
    	uint8_t calc_crc8=crc8_autosar_calc(Data.buff, 255);
    	Data.crc8 = calc_crc8;
    	res = calibration_data_set(Data.buff);
    	if (res) {
    		LOG_INFO(CALIBRATION_DATA, "SetOk");
    	}else {
    		LOG_ERROR(CALIBRATION_DATA, "SetErr");
    	}
    }else{
    	LOG_ERROR(CALIBRATION_DATA, "Usage: cds decawave_addr uwb_offset");
    }


    return res;
}

bool cmd_calibration_data_erase(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
    	res = true;
    }

    if(res) {
        res = calibration_data_erase();
    }
    return res;
}

bool cmd_calibration_data_init(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
    	res = true;
    }

    if(res) {
        res = calibration_data_init();
        if(false == res) {
            LOG_ERROR(CALIBRATION_DATA, "InitErr");
        } else {
            LOG_INFO(CALIBRATION_DATA, "InitOk");
        }
    }
    return res;
}

