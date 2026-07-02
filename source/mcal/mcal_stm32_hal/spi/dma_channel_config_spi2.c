#include "dma_channel_config_spi2.h"

#include "data_utils.h"
#include "microcontroller_const.h"
#include "spi_mcal.h"
#include "spi_isr.h"

bool CallBackDoneSpi2Rx(void) {
    bool res = false;
    res = SpiCallBackRxCplt(2);
    return res;
}

bool CallBackDoneSpi2Tx(void) {
    bool res = false;
    res = SpiCallBackTxCplt(2);
    return res;
}

bool CallBackHalfSpi2Rx(void) {
    bool res = false;
    res= SpiCallBackRxHalfCplt(2);
    return res;
}

bool CallBackHalfSpi2Tx(void) {
    bool res = false;
    res=  SpiCallBackTxHalfCplt(2);
    return res;
}

bool CallBackErrorSpi2Rx(void) {
    bool res = false;
    res= SpiCallBackError(2);
    return res;
}

bool CallBackErrorSpi2Tx(void) {
    bool res = false;
    res= SpiCallBackError(2);
    return res;
}







