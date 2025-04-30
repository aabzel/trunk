#include "dac_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "log.h"
#include "dac_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

bool dac_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = dac_diag();

    return res;
}

bool dac_code_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint16_t code = 0;
    if(2 == argc) {

        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_DAC, "ParseErr DACNum [0~%u]", DAC_COUNT);
        }

            res = try_str2uint16(argv[1], &code);
            if(false == res) {
                LOG_ERROR(LG_DAC, "ParseErr code %s", argv[1]);
            }

    }

        if(res) {
        	res= dac_code_u16_set(num, code) ;
            if(res) {
                LOG_INFO(LG_DAC, "OK");
            } else {
                LOG_ERROR(LG_DAC, "ParseErr send DAC");
            }
        }else {
            LOG_ERROR(LG_DAC, "Usage: dacc Num Code"); /*sw 4 0x55aa*/
        }
    return res;
}

bool dac_voltage_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double voltage = 0.0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_DAC, "ParseErr DACNum [0~%u]", DAC_COUNT);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &voltage);
        if(false == res) {
            LOG_ERROR(LG_DAC, "ParseErr voltage %s", argv[1]);
        }
    }

    if(res) {
    	switch(argc) {
    	case 1: {
            res = dac_voltage_get(num, &voltage);
    	}break;
    	case 2: {
            res = dac_voltage_set(num, voltage);
    	}break;
    	}
    } else {
        LOG_ERROR(LG_DAC, "Usage: dacv num voltage");
    }
    return res;
}

bool dac_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LG_DAC, "ParseErr DACNum [0~%u]", DAC_COUNT);
        }
    }
    if(res) {
        res = dac_init_one(num);
    }
    return res;
}
