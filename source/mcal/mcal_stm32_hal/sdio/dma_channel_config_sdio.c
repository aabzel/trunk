#include "dma_channel_config_sdio.h"

#include "data_utils.h"
#include "microcontroller_const.h"

#include "sdio_mcal.h"
#include "sdio_isr.h"

uint8_t SdiotoArray[DMA_SDIO_MEMCPY_SIZE]={0};
uint8_t SdiofromArray[DMA_SDIO_MEMCPY_SIZE]={0};



 bool CallBackDoneSdio1Rx(void) {
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(1);
    if(Node) {
    }
    return res;
}

 bool CallBackDoneSdio1Tx(void){
    bool res = false;
    SdioHandle_t* Node = SdioGetNode(1);
    if(Node){
    }
    return res;
}

 bool CallBackHalfSdio1Rx(void) {
    bool res = false;
    res= SdioCallBackRxHalfCplt(1);
    return res;
}

 bool CallBackHalfSdio1Tx(void) {
    bool res = false;
    res=  SdioCallBackTxHalfCplt(1);
    return res;
}

 bool CallBackErrorSdio1Rx(void) {
    bool res = false;
    res= SdioCallBackError(1);
    return res;
}

 bool CallBackErrorSdio1Tx(void) {
    bool res = false;
    res= SdioCallBackError(1);
    return res;
}







