#include "i2c_isr.h"

#include <stdbool.h>
#include <stdint.h>

#include "i2c_mcal.h"

bool I2cTxDoneIsr(uint8_t num) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->int_done = true;
        Node->it_cnt++;
        Node->tx_done = true;
        Node->tx_cnt++;
        res = true;
    }
    return res;
}

bool I2cRxDoneIsr(uint8_t num) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->int_done = true;
        Node->it_cnt++;
        Node->rx_done = true;
        Node->rx_cnt++;
        res = true;
    }
    return res;
}

bool I2cErrorIsr(uint8_t num) {
    bool res = false;
    I2cHandle_t* Node = I2cGetNode(num);
    if(Node) {
        Node->int_done = true;
        Node->it_cnt++;
        Node->err_done = true;
        Node->error_cnt++;
        res = true;
    }
    return res;
}
