#include "rs2058_commands.h"

#include "convert.h"
#include "log.h"
#include "rs2058_diag.h"
#include "rs2058_drv.h"
#include "rs2058_types.h"

bool rs2058_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = rs2058_diag();
    return res;
}

bool rs2058_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = rs2058_init();
    return res;
}

bool rs2058_ctrl_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t chip_num=0;
    uint8_t mux_num=0;
    uint8_t state=0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &chip_num);
        if(false == res) {
            LOG_ERROR(RS2058, "ParseErr chip_num %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &mux_num);
        if(false == res) {
            LOG_ERROR(RS2058, "ParseErr mux_num %s", argv[1]);
        }
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &state);
        if(false == res) {
            LOG_ERROR(RS2058, "ParseErr state %s", argv[2]);
        }
    }

    if(res){
        res = rs2058_ctrl(chip_num,mux_num,state);
        if(res){
        	 LOG_INFO(RS2058, "Ok");
        }else{
        	 LOG_ERROR(RS2058, "Error");
        }
    }
    return res;
}
