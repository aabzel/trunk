#include "i2s_custom_diag.h"

#include "stm32f4xx_hal.h"

#ifndef HAL_I2S_MODULE_ENABLED
#error "Add HAL_I2S_MODULE_ENABLED"
#endif /*HAL_I2S_MODULE_ENABLED*/

#ifndef HAS_I2S
#error "Add HAS_I2S"
#endif /*HAS_I2S*/

#include "i2s_custom_types.h"

const char* HalI2sState2Str(HAL_I2S_StateTypeDef state){
    const char* name="?";
    switch((uint32_t)state){
        case HAL_I2S_STATE_RESET:     name="Reset"; break;
        case HAL_I2S_STATE_READY:     name="Ready"; break;
        case HAL_I2S_STATE_BUSY:      name="Busy"; break;
        case HAL_I2S_STATE_BUSY_TX:   name="BusyTx"; break;
        case HAL_I2S_STATE_BUSY_RX:   name="BusyRx"; break;
        case HAL_I2S_STATE_BUSY_TX_RX:name="BusyTxRx"; break;
        case HAL_I2S_STATE_TIMEOUT:   name="TimeOut"; break;
        case HAL_I2S_STATE_ERROR:     name="Error";break;
        default : name="??"; break;
    }
    return name;
}
#if 0

const char* I2sStd2Str(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_STD_I2S_PHILIPS:   name="I2S"; break;
        case I2S_STD_MSB_JUSTIFIED: name="MSB"; break;
        case I2S_STD_LSB_JUSTIFIED: name="LSB"; break;
        case I2S_STD_PCM:   name="PCM"; break;

        default : name="??"; break;
    }
    return name;
}


const char* I2sBit2Str(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_DAT_LEN16_BIT:     name="16"; break;
        case I2S_DAT_LEN24_BIT:     name="24"; break;
        case I2S_DAT_LEN32_BIT:      name="32"; break;
        case I2S_DAT_NOT_ALLOWED:   name="?"; break;

        default : name="??"; break;
    }
    return name;
}

const char* I2sOdd2Str(uint8_t code){
    const char* name="?";
    switch(code){
        case 0:     name="I2SDIV*2"; break;
        case 1:     name="(I2SDIV*2)+1"; break;

        default : name="??"; break;
    }
    return name;
}


const char* I2sChlen2Str(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_CHLEN_16:   name="16"; break;
        case I2S_CHLEN_32:    name="32"; break;

        default : name="??"; break;
    }
    return name;
}

const char* SerialMode2Str(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_MODE_SPI:   name="SPI"; break;
        case I2S_MODE_I2S:    name="I2S"; break;
        default : name="??"; break;
    }
    return name;
}

#endif

const char* I2sRole2Str(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_ROLE_SLAVE_TRANSMIT:   name="SlaveTx"; break;
        case I2S_ROLE_SLAVE_RECEIVE:    name="SlaveRx"; break;
        case I2S_ROLE_MASTER_TRANSMIT:  name="MasterTx"; break;
        case I2S_ROLE_MASTER_RECEIVE:   name="MasterRx"; break;

        default : name="??"; break;
    }
    return name;
}

bool i2s_diag_one(uint8_t i2s_num){
	return false;
}
