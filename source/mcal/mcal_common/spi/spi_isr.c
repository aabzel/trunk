#include "spi_isr.h"

#include <string.h>
bool SpiErrorCallBack(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->error_cnt++;
        Node->error_done = true;
        res = true;
    }
    return res;
}

/*tx*/
bool SpiTxHalfCpltCallBack(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->tx_half_cnt++;
        Node->tx_half_done = true;
        res = true;
    }
    return res;
}

bool SpiTxCpltCallBack(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->tx_cnt++;
        Node->tx_done = true;
        res = true;
    }
    return res;
}

/*Rx*/
bool SpiRxHalfCpltCallBack(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->rx_half_cnt++;
        Node->rx_half_done = true;
        res = true;
    }
    return res;
}

bool SpiRxCpltCallBack(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->rx_cnt++;
        Node->rx_done = true;
        res = true;
    }
    return res;
}

 

/*RxTx*/
bool SpiTxRxHalfCpltCallBack(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiTxHalfCpltCallBack(Node);
        SpiRxHalfCpltCallBack(Node);
        res = true;
    }
    return res;
}

bool SpiTxRxCpltCallBack(SpiHandle_t* const Node) {
    bool res = false;
    if(Node) {
        SpiTxCpltCallBack(Node);
        SpiRxCpltCallBack(Node);
        res = true;
    }
    return res;
}
