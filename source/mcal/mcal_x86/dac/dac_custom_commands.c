#include "dac_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "debug_info.h"
#include "dac_mcal.h"
#include "dac_custom_diag.h"
#include "dac_custom_types.h"
#include "dac_custom_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

bool dac_diag_custom_command(int32_t argc, char *argv[]) {
    bool res = false;
    res = dac_diag_custom();
    return res;
}

bool dac_data_send_command(int32_t argc, char *argv[]) {
    bool res = false;
    uint8_t data = 0;
    uint8_t num = 0;

    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if (false == res) {
            LOG_ERROR(DAC, "ParseErr DAC Number [1-%d]", DAC_COUNT);
        }
    }

    if (2 <= argc) {
        res = try_str2uint8(argv[1], &data);
        if (false == res) {
            LOG_ERROR(DAC, "ParseErr data");
        }
    }

    if (res) {
        DacHandle_t *Node = DacGetNode(num);
        if (Node) {
            dac_data_send(Node->DACx, data);
            res = true;
        }
    }
    return res;
}

bool dac_raw_reg_command(int32_t argc, char* argv[]){
    uint8_t num = 0;
    bool res = false;
    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if (false == res) {
            LOG_ERROR(DAC, "ParseErr DAC Number [1-%d]", DAC_COUNT);
        }
    }

    if(res) {
    	res = dac_raw_reg_diag(num);
    }else{
    	LOG_ERROR(DAC, "Usage dacrr Num");
    }


    return res;
}


bool dac_all_int_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if (false == res) {
            LOG_ERROR(DAC, "ParseErr DAC Number [1-%d]", DAC_COUNT);
        }
    }

    const DacInfo_t* Info = DacGetInfo(num);
    if(Info) {
    	 dac_interrupt_enable(Info->DACx, DAC_ALL_INT, TRUE);
    	 res = true;
    } else {
    	LOG_ERROR(DAC, "Usage dacai Num");
    }

    return res;
}

bool dac_div_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    uint8_t div = 0;
    if (1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if (false == res) {
            LOG_ERROR(DAC, "ParseErr DAC Number [1-%d]", DAC_COUNT);
        }
    }

    if (2 <= argc) {
        res = try_str2uint8(argv[1], &div);
        if (false == res) {
            LOG_ERROR(DAC, "ParseErr DAC Div");
        }
    }

    if(res) {
    	 switch(argc){
    	 case 1: {
    		 res = dac_div_get(num, &div);
    		 LOG_INFO(DAC, "Get,DAC%u,Div:%u",num, div);
    	 } break;
    	 case 2: {
    		 LOG_INFO(DAC, "Set,DAC%u,Div:%u",num, div);
        	 res = dac_div_set(num, div);

    	 } break;
    	 }

    } else {
    	LOG_ERROR(DAC, "Usage dacdi Num Div");
    }

    return res;
}
