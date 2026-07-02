#include "dma_channel_config_spi1.h"

#include "data_utils.h"
#include "microcontroller_const.h"


#include "spi_mcal.h"
#include "spi_isr.h"
#include "module_driver_fcspi.h"


 bool CallBackDoneSpi1Rx(void) {
    bool res = false;
    SpiHandle_t* Spi = SpiGetNode(1);
    if(Spi) {
        FCSPIn_DmaDoneCallback_Rx(&Spi->Handle);
    }
    return res;
}

 bool CallBackDoneSpi1Tx(void){
    bool res = false;
    SpiHandle_t* Spi = SpiGetNode(1);
    if(Spi){
        FCSPIn_DmaDoneCallback_Tx(&Spi->Handle);
    }
    return res;
}

 bool CallBackHalfSpi1Rx(void) {
    bool res = false;
    res= SpiCallBackRxHalfCplt(1);
    return res;
}

 bool CallBackHalfSpi1Tx(void) {
    bool res = false;
    res=  SpiCallBackTxHalfCplt(1);
    return res;
}

 bool CallBackErrorSpi1Rx(void) {
    bool res = false;
    res= SpiCallBackError(1);
    return res;
}

 bool CallBackErrorSpi1Tx(void) {
    bool res = false;
    res= SpiCallBackError(1);
    return res;
}







