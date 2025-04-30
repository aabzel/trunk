#include "axp192_commands.h"

#include <stdio.h>
#include <string.h>

#include "log.h"
#include "convert.h"
#include "axp192_diag.h"
#include "axp192_drv.h"
#include "axp192_types.h"

bool axp192_diag_command(int32_t argc, char* argv[]){
    bool res = false;
    ChargeControl_t reg;
    reg.byte=0;
    res = axp192_i2c_read(0x33, &reg.byte);
    res = axp192_parse_reg33(reg.byte);
    return res;
}

bool axp192_reg_write_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t reg_addr=0;
    uint8_t reg_val=0;
    if(1<=argc){
       res = try_str2uint8(argv[0], &reg_addr);
    }
    if(2<=argc){
       res = try_str2uint8(argv[1], &reg_val);
    }
    if(res && (2==argc)){
        res= axp192_i2c_write(  reg_addr,   reg_val);
        if(res){
              LOG_INFO(PMIC,"WrOk");
        }
    }
    return res;
}

bool axp192_reg_read_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t reg_addr=0;
    uint8_t reg_val=0;
    if(1<=argc){
       res = try_str2uint8(argv[0], &reg_addr);
    }
    if(res){
        res = axp192_i2c_read(reg_addr, &reg_val);
        if(res){
            LOG_INFO(PMIC,"Reg[0x%02x]=0x%02x",reg_addr,reg_val);
        }
    }
    return res;
}

bool axp192_reg_map_command(int32_t argc, char* argv[]){
    bool res = false;
    uint16_t reg_addr=0;
    uint8_t reg_val=0;
    for(reg_addr=0;reg_addr<=0xFF;reg_addr++){
        reg_val=0;
        res = axp192_i2c_read(reg_addr, &reg_val);
        if(res){
            LOG_INFO(PMIC,"Reg[0x%02x]=0x%02x",reg_addr,reg_val);
        }else{
            LOG_ERROR(PMIC, "RegRrErr");
        }
    }
    return res;
}

