#include "i2c_custom_diag.h"

#include <stdint.h>

#include "i2c_custom_const.h"
#include "mik32_hal.h"

char* I2cHalState2Str(uint8_t code){
   char* name="?";
   switch(code){
   case HAL_I2C_STATE_RESET: name="Reset";break;
   case HAL_I2C_STATE_READY:name="Ready"; break;
   case HAL_I2C_STATE_BUSY:name="Busy"; break;
   case HAL_I2C_STATE_BUSY_TX:name="BusyTx"; break;
   case HAL_I2C_STATE_BUSY_RX: name="BusyRx";break;
   case HAL_I2C_STATE_LISTEN: name="Listen";break;
   case HAL_I2C_STATE_BUSY_TX_LISTEN:name="BusyTxListen"; break;
   case HAL_I2C_STATE_BUSY_RX_LISTEN:name="BusyRxListen"; break;
   case HAL_I2C_STATE_ABORT:name="Abort"; break;
   case HAL_I2C_STATE_TIMEOUT:name="Timeout"; break;
   case HAL_I2C_STATE_ERROR: name="Err";break;
   }
   return name;
}

char* I2cMode2Str(uint8_t code){
    char* name="?";
    switch(code){
    case I2C_MODE_I2C: name="I2C";break;
    case I2C_MODE_SMBUS:name="SMBus"; break;
    }
    return name;
}

char* I2cBusRole2Str(uint8_t code ){
    char* name="?";
    switch(code){
    case I2C_BUS_ROLE_SLAVE: name="Slave";break;
    case I2C_BUS_ROLE_MASTER:name="Master"; break;
    }
    return name;
}

char* I2cBusState2Str(uint8_t code ){
    char* name="?";
    switch(code){
    case I2C_BUS_STATE_SPARE: name="Spare";break;
    case I2C_BUS_STATE_BUSY:name="Busy"; break;
    }
    return name;
}

char* I2cDir2Str(uint8_t code ){
    char* name="?";
    switch(code){
    case I2C_DIR_RX: name="Rx";break;
    case I2C_DIR_TX:name="Tx"; break;
    }
    return name;
}

