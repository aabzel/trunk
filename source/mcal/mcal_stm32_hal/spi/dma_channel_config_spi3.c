#include "dma_channel_config_spi3.h"

#include "data_utils.h"
#include "microcontroller_const.h"
#include "spi_mcal.h"
#include "spi_isr.h"

 bool CallBackDoneSpi3Rx(void) {
    bool res = false;
    res = SpiCallBackRxCplt(3);
    return res;
}

 bool CallBackDoneSpi3Tx(void) {
    bool res = false;
    res = SpiCallBackTxCplt(3);
    return res;
}

 bool CallBackHalfSpi3Rx(void) {
    bool res = false;
    res= SpiCallBackRxHalfCplt(3);
    return res;
}

 bool CallBackHalfSpi3Tx(void) {
    bool res = false;
    res=  SpiCallBackTxHalfCplt(3);
    return res;
}

 bool CallBackErrorSpi3Rx(void) {
    bool res = false;
    res= SpiCallBackError(3);
    return res;
}

 bool CallBackErrorSpi3Tx(void) {
    bool res = false;
    res= SpiCallBackError(3);
    return res;
}







