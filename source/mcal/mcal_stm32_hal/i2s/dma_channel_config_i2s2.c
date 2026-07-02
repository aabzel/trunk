#include "dma_channel_config_i2s2.h"

#include "data_utils.h"
#include "microcontroller_const.h"


#include "i2s_mcal.h"


uint8_t I2s2toArray[I2S_DMA_MEMCPY_SIZE] = {0};
uint8_t I2s2fromArray[I2S_DMA_MEMCPY_SIZE] = {0};

 bool CallBackDoneI2s2Rx(void) {
    bool res = false;
    I2sHandle_t* I2s = I2sGetNode(1);
    if(I2s) {
    }
    return res;
}

 bool CallBackDoneI2s2Tx(void){
    bool res = false;
    I2sHandle_t* I2s = I2sGetNode(1);
    if(I2s){
    }
    return res;
}

 bool CallBackHalfI2s2Rx(void) {
    bool res = false;
    res= I2sRxHalfCallback(2);
    return res;
}

 bool CallBackHalfI2s2Tx(void) {
    bool res = false;
    res=  I2sDmaCallBackTxHalf(2);
    return res;
}

 bool CallBackErrorI2s2Rx(void) {
    bool res = false;
    res= I2sDmaCallBackRxHalf(2);
    return res;
}

 bool CallBackErrorI2s2Tx(void) {
    bool res = false;
   // res= I2sCallBackError(1);
    return res;
}







