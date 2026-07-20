#include "dma_channel_config_i2s4.h"

#include "data_utils.h"
#include "microcontroller_const.h"


#include "i2s_mcal.h"

#if 0
uint8_t I2s4toArray[I2S_DMA_MEMCPY_SIZE] = {0};
uint8_t I2s4fromArray[I2S_DMA_MEMCPY_SIZE] = {0};

 bool CallBackDoneI2s4Rx(void) {
    bool res = false;
    I2sHandle_t* I2s = I2sGetNode(1);
    if(I2s) {
    }
    return res;
}

 bool CallBackDoneI2s4Tx(void){
    bool res = false;
    I2sHandle_t* I2s = I2sGetNode(1);
    if(I2s){
    }
    return res;
}

 bool CallBackHalfI2s4Rx(void) {
    bool res = false;
    res= I2sRxHalfCallback(2);
    return res;
}

 bool CallBackHalfI2s4Tx(void) {
    bool res = false;
    res=  I2sDmaCallBackTxHalf(2);
    return res;
}

 bool CallBackErrorI2s4Rx(void) {
    bool res = false;
    res= I2sDmaCallBackRxHalf(2);
    return res;
}

 bool CallBackErrorI2s4Tx(void) {
    bool res = false;
   // res= I2sCallBackError(1);
    return res;
}

#endif






