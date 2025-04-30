#include "axp192_drv.h"

#include <stdbool.h>
#include <stdint.h>

#include "log.h"

#ifdef HAS_I2C
#include "i2c_drv.h"
#endif

#include "sys_config.h"

//https://github.com/bitengineers/esp32_axp192/blob/main/include/axp192.h
//https://github.com/bitengineers/esp32_axp192/blob/main/axp192.c

#ifndef HAS_AXP192
#error "That component needs option HAS_AXP192"
#endif

#ifndef HAS_I2C
#error "That component needs option HAS_I2C"
#endif

bool axp192_init(void) {
    bool res = true;
    return res;
}

bool axp192_process(void) {
    bool res = false;
    return res;
}

bool axp192_i2c_write(uint8_t reg, uint8_t value){
    bool res = false;
    uint8_t data[2]={0};
    data[0]=reg;
    data[1]=value;
    res=i2c_write(AXP192_I2C,  AXP192_I2C_ADDR, data, 2);

    return res;
}

bool axp192_i2c_read(uint8_t reg, uint8_t *value){
    bool res = false;
    /*CLI eqvivalent:*/
    /* i2w 0 0x34 0x23*/
    /* i2r 0 0x34 1*/
    res=i2c_write(AXP192_I2C,  AXP192_I2C_ADDR, &reg, 1);
    if(res){
        res=i2c_read(AXP192_I2C, AXP192_I2C_ADDR, value, 1);
    }

    return res;
}
