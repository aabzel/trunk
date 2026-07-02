#include "dma_channel_config_uart1.h"

#include "data_utils.h"
#include "microcontroller_const.h"
#include "uart_mcal.h"
#include "uart_isr.h"

bool CallBackHalfUart1Rx(void) {
    bool res = false;
    res = UartDmaCallBackRxHalfCplt(1);
    return res;
}
bool CallBackDoneUart1Rx(void) {
    bool res = false;
    res = UartDmaCallBackRxDoneCplt(1);
    return res;
}

bool CallBackDoneUart1Tx(void) {
    bool res = false;
    res = UartDmaCallBackTxDoneCplt(1);
    return res;
}

bool CallBackHalfUart1Tx(void) {
    bool res = false;
    res = UartDmaCallBackTxHalfCplt(1);
    return res;
}

