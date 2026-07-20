#include "dma_channel_config_sdio.h"

#include "data_utils.h"
#include "microcontroller_const.h"


#include "spi_mcal.h"
#include "spi_isr.h"
#include "module_driver_fcspi.h"


 bool CallBackDoneSdio1Rx(void) {
    bool res = false;
    SdioHandle_t* Sdio = SdioGetNode(1);
    if(Sdio) {
        FCSPIn_DmaDoneCallback_Rx(&Sdio->Handle);
    }
    return res;
}

 bool CallBackDoneSdio1Tx(void){
    bool res = false;
    SdioHandle_t* Sdio = SdioGetNode(1);
    if(Sdio){
        FCSPIn_DmaDoneCallback_Tx(&Sdio->Handle);
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







